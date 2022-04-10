#include "computer.h"
#include "heap.h"
#include "request.h"
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
void simulator( string fileName, int numberOfComputers, int& avgWaitingTime) {
    
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

    int currentRequest = 1;
    while( currentRequest <= numberOfRequests) {
        int id, priority, sentTime, processTime;
        f >> id; f >> priority; f >> sentTime; f >> processTime;
        request newRequest( id, priority, sentTime, processTime);
        requests[currentRequest] = newRequest;
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
            if( computers[i].isWorking) {
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
    }
    avgWaitingTime = average/numberOfRequests;

    delete[] requests;
}



int main( int arg, char* args[]) {

}