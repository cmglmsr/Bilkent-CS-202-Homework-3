#include "request.h"

/*
* Title: request.h
* Author: Mustafa Cem Gülümser
* ID: 22003430
* Section: 2
* Assignment: 3
* Description: Request class header file. Requests have priorities as key values
*/

request::request( int tid, int tpriority, int tsentTime, int tprocessTime) {
    id = tid; priority = tpriority; sentTime = tsentTime; processTime = tprocessTime;
}

int request::getKey() {
    return priority;
}