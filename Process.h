#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Process
{
protected:
    int pid;
    static int next_pid;

public:
    Process(int pid_override = -1);
    virtual ~Process() {}
    int getPid() const;
    virtual void execute() = 0;
    virtual string serialize() const = 0;
    virtual string typeName() const = 0;
    virtual void printInfo() const = 0;
};

#endif
