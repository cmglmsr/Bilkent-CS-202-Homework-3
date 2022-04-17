#include "computer.h"
#include "heap.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

/*
* Title: computer.cpp
* Author: Mustafa Cem Gülümser
* ID: 22003430
* Section: 2
* Assignment: 3
* Description: Computer class source code file
*/

/*
TO DO:
* Change convertChar
* Seperate the initialization of the file to another method
* Change if clauses, computer updates can be done in a single loop
* Add comments
*/

const int MAX_COMPUTERS = 999;

// converts a given char to an integer
int convertChar(const char *s) 
{
 int i;
    i = 0;
    while(*s >= '0' && *s <= '9')
    {
        i = i * 10 + (*s - '0');
        s++;
    }
    return i;
}

// readRequests method reads the requests from the file
void readRequests( string fileName, request*& requests, int& num) {
    ifstream f;
    f.open((fileName).c_str());
    
    if(!f.is_open()) {  // if the given file name does not exist
        cout<< "Cannot find the file." << endl;
        return;
    }
    
    f >> num;  // read the first number
    requests = new request[num];  // initialize the requests array

    int currentRequest = 0;
    while( currentRequest < num) {
        int id, priority, sentTime, processTime;
        f >> id; f >> priority; f >> sentTime; f >> processTime;
        request newRequest( id, priority, sentTime, processTime);
        requests[currentRequest] = newRequest;
        currentRequest++;
    }
}

// initializearrayOfComputers method constructs a computer array with the given number of computers
void initializearrayOfComputers( computer*& arrayOfComputers, int num) {
    arrayOfComputers = new computer[num];
    for( int i = 0; i < num; i++) {
        arrayOfComputers[i].compNumber = i;
    }
}

// simulator method computes the average waiting time for a given number of computers and a list of given requests.
void simulator( string fileName, int numberOfComputers, float& avgWaitingTime) {
    
    int numberOfRequests;
    request* requests;
    readRequests( fileName, requests, numberOfRequests);

    computer* computers;
    initializearrayOfComputers( computers, numberOfComputers);

    Heap heap;  // heap will store the requests
    bool completed = false;
    int ms = 0;  // ms is the current time in ms
    float sum;  // sum of the waiting times
    int done = 0;
    
    while( !completed) {

        // pass over each request in the requests array
        for( int i = 0; i < numberOfRequests; i++) {
            if( requests[i].sentTime == ms) { // insert the request into the heap if it was sent at the current time
                heap.heapInsert( requests[i]);
            }
            if( requests[i].sentTime > ms) {
                break;
            }
        }

        // pass over each computer in the arrayOfComputers array
        for( int i = 0; i < numberOfComputers; i++) {
            if( computers[i].isWorking) {  // decrement the processing time if the computer is working
                computers[i].processingTime--;
            } 
            if( computers[i].processingTime == 0) { // set the computer as not working if processing time is 0
                computers[i].isWorking = false;
            }
            if(!heap.heapIsEmpty() && heap.items[0].sentTime <= ms && !computers[i].isWorking) {
                sum = sum + (float) (ms - heap.items[0].sentTime); // add the waiting time to the sum
                computers[i].processingTime = heap.items[0].processTime; // assign the highest priority request to the computer
                computers[i].isWorking = true;
                done++;
                heap.heapDelete(heap.items[0]); // delete the assigned request from the heap
            }
        }
        if( done == numberOfRequests)
            completed = true;
        ms++;
    }
    avgWaitingTime = sum/numberOfRequests; // compute the average waiting time by dividing the sum to the number of requests

    delete[] requests;
    delete[] computers;
}

void show(string fileName, int numberOfComputers) {
    int numberOfRequests;
    request* requests;
    readRequests( fileName, requests, numberOfRequests);

    computer* computers;
    initializearrayOfComputers( computers, numberOfComputers);

    Heap heap;
    bool completed = false;
    int ms = 0;
    float average = 0;
    int done = 0;
    int waitTime;
    
    while( !completed) {
        for( int i = 0; i < numberOfRequests; i++) {
            if( requests[i].sentTime == ms) {
                heap.heapInsert( requests[i]);
            }
            if( requests[i].sentTime > ms) {
                break;
            }
        }
        for( int i = 0; i < numberOfComputers; i++) {
            if( computers[i].isWorking) {  
                computers[i].processingTime--;
            }
            if( computers[i].processingTime == 0) {
                computers[i].isWorking = false;
            }
            if(!heap.heapIsEmpty() && heap.items[0].sentTime <= ms && !computers[i].isWorking) {
                computers[i].processingTime = heap.items[0].processTime;
                computers[i].isWorking = true;
                waitTime = (ms - heap.items[0].sentTime);
                average += (float) waitTime;
                cout << "Computer " << computers[i].compNumber << " takes request " << heap.items[0].id << " at ms " << ms << " (wait: " << waitTime << " ms)" << endl;
                heap.heapDelete(heap.items[0]);
                done++;
            }
        }
        if( done == numberOfRequests)
            completed = true;
        ms++;
    }
    cout << endl << "Average waiting time: " <<  average/numberOfRequests << endl;

    delete[] requests;
}

void initialPrint( int numberOfComputers) {
    cout << endl;
    cout << "Minimum number of computers required: " << numberOfComputers << endl;
    cout << endl;
    cout << "Simulation with " << numberOfComputers << " computers:" << endl;
    cout << endl;
}

int optimalNumber( string filename, float averageTime) { // BE CAREFUL MIGHT NOT WORK!!!!!!!!!!!!
    float testDuration;
    if( averageTime <= 0) {
        cout << "Average time cannot be 0 or less, simulation will not proceed." << endl;
        return 0;
    }
    for( int i = 1; i < MAX_COMPUTERS; i++) {
        simulator( filename, i, testDuration);
        if( testDuration <= averageTime) {
            initialPrint( i);
            show( filename, i);
            return i;
        }
    }
    return 0;
}

int main( int arg, char* args[]) {
    float avgwaitingtime = convertChar(args[2]);
	optimalNumber(args[1], avgwaitingtime);
}