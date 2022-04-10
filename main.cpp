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

void simulator( string fileName, int avgWaitingTime) {
    
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


    delete[] requests;
}

int main( int arg, char* args[]) {

}