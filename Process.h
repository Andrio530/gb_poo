#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Process {
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

class ProcessQueue;

class ComputingProcess : public Process {
private:
    string expr;
public:
    ComputingProcess(const string &expression, int pid_override = -1);
    void execute() override;
    string serialize() const override;
    string typeName() const override;
    void printInfo() const override;
};

class WritingProcess : public Process {
private:
    string expr;
public:
    WritingProcess(const string &expression, int pid_override = -1);
    void execute() override;
    string serialize() const override;
    string typeName() const override;
    void printInfo() const override;
};

class ReadingProcess : public Process {
private:
    ProcessQueue *queue;
public:
    ReadingProcess(ProcessQueue *q, int pid_override = -1);
    void execute() override;
    string serialize() const override;
    string typeName() const override;
    void printInfo() const override;
};

class PrintingProcess : public Process {
private:
    ProcessQueue *queue;
public:
    PrintingProcess(ProcessQueue *q, int pid_override = -1);
    void execute() override;
    string serialize() const override;
    string typeName() const override;
    void printInfo() const override;
};
#endif
