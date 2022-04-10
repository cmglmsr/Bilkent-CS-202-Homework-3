

/*
* Title: Heap.h
* Author: Mustafa Cem Gülümser
* ID: 22003430
* Section: 2
* Assignment: 3
* Description: Heap class header file
*/
class request {

    public:
    request();
    request( int tid, int tpriority, int tsentTime, int tprocessTime);
    int getKey();

    private:
    int id;
    int priority;
    int sentTime;
    int processTime;
};