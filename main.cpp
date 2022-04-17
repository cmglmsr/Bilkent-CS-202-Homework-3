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

const int MAX_COMPUTERS = 999;
const long int MAX_DURATION = 999999;

// converts a given char to an integer
int convertChar(char *word) 
{   
    long int returnInt = 0;

    if( word == NULL)
        return -1;

    for( ; *word >= '0' & *word <= '9'; word++){
        returnInt = (*word - '0') + returnInt * 10;
    }
    return returnInt;
}

// readRequests method reads the requests from the file
void readRequests( string fileName, request*& requests, int& num) {
    ifstream f;
    f.open((fileName).c_str());
    
    if(!f.is_open()) {  // if the given file name does not exist
        cout<< "The file does not exist." << endl;
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

    computer* computers;
    initializearrayOfComputers( computers, numberOfComputers);

    Heap heap;  // heap will store the requests
    bool completed = false;
    long int ms = 0;  // ms is the current time in ms (defined as long it because time can go on for long)
    float sum;  // sum of the waiting times
    int done = 0;
    int numberOfRequests;

    request* requests;
    readRequests( fileName, requests, numberOfRequests);
    
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

        // pass over each computer in the computers array
        for( int i = 0; i < numberOfComputers; i++) {
            if( computers[i].isWorking) {  // decrement the processing time if the computer is working
                computers[i].processingTime--;
            } 
            if( computers[i].processingTime == 0) { // set the computer as not working if processing time is 0
                computers[i].isWorking = false;
            }
            if( !heap.heapIsEmpty()) {
                if(!computers[i].isWorking & heap.items[0].sentTime <= ms) {
                    sum = sum + (float) (ms - heap.items[0].sentTime); // add the waiting time to the sum
                    computers[i].processingTime = heap.items[0].processTime; // assign the highest priority request to the computer
                    computers[i].isWorking = true;
                    done++;
                    heap.heapDelete(heap.items[0]); // delete the assigned request from the heap
                }
            }
        }

        // the loop is done if we have no more requests to process.
        if( done == numberOfRequests) {
            completed = true;
            break;
        }
            
        ms++;
    }
    avgWaitingTime = sum/numberOfRequests; // compute the average waiting time by dividing the sum to the number of requests

    delete[] requests;
    delete[] computers;
}

// show method runs the simulation and prints the necessary information
void show(string fileName, int numberOfComputers) {

    computer* computers;
    initializearrayOfComputers( computers, numberOfComputers);

    int numberOfRequests;
    Heap heap; // heap will store the requests
    bool completed = false;
    long int ms = 0; // ms is the current time in ms
    float sum = 0; // sum of the waiting times
    int done = 0;
    long int delay; // delay is the particular wait time for that request

    request* requests;
    readRequests( fileName, requests, numberOfRequests);
    
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
        // pass over each computer in the computers array
        for( int i = 0; i < numberOfComputers; i++) {
            if( computers[i].isWorking) {  
                computers[i].processingTime--; // decrement the processing time if the computer is working
            }
            if( computers[i].processingTime == 0) {  // set the computer as not working if processing time is 0
                computers[i].isWorking = false;
            }
            if( !heap.heapIsEmpty()) {
                if(!computers[i].isWorking & heap.items[0].sentTime <= ms) {
                    delay = (ms - heap.items[0].sentTime);
                    sum = sum + (float) (ms - heap.items[0].sentTime); // add the waiting time to the sum
                    computers[i].processingTime = heap.items[0].processTime; // assign the highest priority request to the computer
                    computers[i].isWorking = true;
                    // Print
                    cout << "Computer " 
                    << computers[i].compNumber 
                    << " takes request " 
                    << heap.items[0].id 
                    << " at ms " << ms 
                    << " (wait: " 
                    << delay 
                    << " ms)" 
                    << endl;
                    done++;
                    heap.heapDelete(heap.items[0]);
                }
            }
        }

        // the loop is done if we have no more requests to process.
        if( done == numberOfRequests) {
            completed = true;
            break;
        }
           
        ms++;
    }
    cout << endl << "Average waiting time: " <<  sum/numberOfRequests << endl;

    delete[] computers;
    delete[] requests;
}

// initialPrint prints the minimum number of computers
void initialPrint( int numberOfComputers) {
    cout << endl;
    cout << "Minimum number of computers required: " << numberOfComputers << endl;
    cout << endl;
    cout << "Simulation with " << numberOfComputers << " computers:" << endl;
    cout << endl;
}

// optimalNumber method finds the minimum number of computers for the given average time
int optimalNumber( string filename, float averageTime) {
    float testDuration = MAX_DURATION;
    if( averageTime <= 0) {
        cout << "Average time cannot be 0 or less, simulation will not proceed." << endl;
        return 0;
    }
    int computerCount = 1;
    while( testDuration > averageTime) {
        simulator( filename, computerCount, testDuration);
        computerCount++;
    }
    initialPrint( computerCount-1);
    show( filename, computerCount-1);
    return 0;
}

// main method
int main( int arg, char* args[]) {
    float avgwaitingtime = convertChar(args[2]);

    if( avgwaitingtime <= 0) {
        cout << "Average time cannot be 0 or less, simulation will not proceed." << endl;
        return 0;
    }

	optimalNumber(args[1], avgwaitingtime);
}