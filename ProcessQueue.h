#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H
#include "Process.h"
struct Node {
    Process *proc;
    Node *next;
    Node(Process *p):proc(p),next(nullptr){}
    ~Node(){delete proc;}
};
class ProcessQueue {
private:
    Node *head,*tail;int count;
public:
    ProcessQueue();~ProcessQueue();
    void push_back(Process *p);
    Process* pop_front();
    Process* find_by_pid(int pid) const;
    Process* remove_by_pid(int pid);
    bool empty() const;int size() const;
    void printAll() const;void clear();
    bool saveToFile(const string &filename) const;
    bool loadFromFile(const string &filename);
};
#endif
