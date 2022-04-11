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


// simulator method computes the average waiting time for a given number of computers and a list of given requests.
void simulator( string fileName, int numberOfComputers, double& avgWaitingTime) {
    
    ifstream f;
    f.open((fileName).c_str());
    request* requests;
    int numberOfRequests;

    if(!f.is_open()) {
        cout<< "Cannot find the file." << endl;
        return;
    }

    f >> numberOfRequests;
    requests = new request[numberOfRequests];

    int currentRequest = 0;
    while( currentRequest < numberOfRequests) {
        int id, priority, sentTime, processTime;
        f >> id; f >> priority; f >> sentTime; f >> processTime;
        request newRequest( id, priority, sentTime, processTime);
        requests[currentRequest] = newRequest;
        currentRequest++;
    }

    computer* computers = new computer[numberOfComputers];
    for( int i = 0; i < numberOfComputers; i++) {
        computers[i].compNumber = i;
    }

    Heap heap;
    bool completed = false;
    int ms = 0;
    double average;
    int done = 0;
    
    while( !completed) {
        for( int i = 0; i < numberOfComputers; i++) {
            if( computers[i].processingTime != 0) {
                computers[i].processingTime--;
            }
        }
        for( int i = 0; i < numberOfRequests; i++) {
            if( requests[i].sentTime == ms) {
                heap.heapInsert( requests[i]);
            }
            if( requests[i].sentTime > ms) {
                break;
            }
        }
        for( int i = 0; i < numberOfComputers; i++) {
            if( computers[i].processingTime == 0) {
                computers[i].isWorking = false;
            }
            if(!heap.heapIsEmpty() && heap.items[0].sentTime <= ms && !computers[i].isWorking) {
                computers[i].processingTime = heap.items[0].processTime;
                computers[i].isWorking = true;

                average += (double) (ms - heap.items[0].sentTime);   // BE CAREFUL MIGHT NOT WORK!!!!!!!!!!!!
                heap.heapDelete(heap.items[0]);
                done++;
            }
        }
        if( done == numberOfRequests)
            completed = true;
        ms++;
    }
    avgWaitingTime = average/numberOfRequests;

    delete[] requests;
    delete[] computers;
}

void initialPrint( int numberOfComputers) {
    cout << "Minimum number of computers required: " << numberOfComputers << endl << endl;
    cout << "Simulation with " << numberOfComputers << " computers:" << endl << endl;
}

void show(string fileName, int numberOfComputers) {
    ifstream f;
    f.open((fileName).c_str());
    request* requests;
    int numberOfRequests;

    if(!f.is_open()) {
        cout<< "Cannot find the file." << endl;
        return;
    }

    f >> numberOfRequests;
    requests = new request[numberOfRequests];

    int currentRequest = 0;
    while( currentRequest < numberOfRequests) {
        int id, priority, sentTime, processTime;
        f >> id; f >> priority; f >> sentTime; f >> processTime;
        request newRequest( id, priority, sentTime, processTime);
        requests[currentRequest] = newRequest;

        //cout << "request id: " << requests[currentRequest].id << " request prio: " << requests[currentRequest].priority <<
        //" request sentTime " << requests[currentRequest].sentTime << " request processTime " << requests[currentRequest].processTime << endl; 

        currentRequest++;
    }

    Heap heap;
    bool completed = false;
    int ms = 0;
    double average = 0;
    int done = 0;
    int waitTime;
    computer* computers = new computer[ numberOfComputers];
    for( int i = 0; i < numberOfComputers; i++) {
        computers[i].compNumber = i;        
    }
    while( !completed) {
        for( int i = 0; i < numberOfComputers; i++) {
            if( computers[i].processingTime > 0) {  
                computers[i].processingTime--;
            }
        }
        for( int i = 0; i < numberOfRequests; i++) {
            if( requests[i].sentTime == ms) {
                heap.heapInsert( requests[i]);
            }
            if( requests[i].sentTime > ms) {
                break;
            }
        }
        for( int i = 0; i < numberOfComputers; i++) {
            if( computers[i].processingTime == 0) {
                computers[i].isWorking = false;
            }
            if(!heap.heapIsEmpty() && heap.items[0].sentTime <= ms && !computers[i].isWorking) {
                computers[i].processingTime = heap.items[0].processTime;
                computers[i].isWorking = true;
                waitTime = (ms - heap.items[0].sentTime);
                average += (double) waitTime;
                // BE CAREFUL MIGHT NOT WORK!!!!!!!!!!!!
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

int optimalNumber( string filename, double averageTime) { // BE CAREFUL MIGHT NOT WORK!!!!!!!!!!!!
    double testDuration;
    for( int i = 1; i < 999; i++) {
        simulator( filename, i, testDuration);
        if( testDuration <= averageTime) {
            initialPrint( i);
            show( filename, i);
            return i;
        }
    }
    return -1;
}

int stringToInt(const char *s) // BE CAREFUL MIGHT NOT WORK!!!!!!!!!!!!
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

int main( int arg, char* args[]) {
    double avgwaitingtime = stringToInt(args[2]);
	optimalNumber(args[1], avgwaitingtime);
}