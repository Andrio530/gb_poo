#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H
#include "Nodo.h"
#include "Process.h"

class ProcessQueue
{
private:
    Nodo<Process *> *head, *tail;
    int count;

public:
    ProcessQueue();
    ~ProcessQueue();
    void push_back(Process *p);
    Process *pop_front();
    Process *find_by_pid(int pid) const;
    Process *remove_by_pid(int pid);
    bool empty() const;
    int size() const;
    void printAll() const;
    void clear();
    bool saveToFile(const string &filename) const;
    bool loadFromFile(const string &filename);
};
#endif
