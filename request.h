/*
* Title: Heap.h
* Author: Mustafa Cem Gülümser
* ID: 22003430
* Section: 2
* Assignment: 3
* Description: Heap class header file
*/
struct request {
    public:
    request();
    request( int tid, int tpriority, int tsentTime, int tprocessTime);
    int getKey();
    int id;
    int priority;
    int sentTime;
    int processTime;
};