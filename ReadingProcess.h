//
// Created by Lucca Jaroszeski Becker on 16/11/25.
//

#ifndef GB_POO_READINGPROCESS_H
#define GB_POO_READINGPROCESS_H
#include "Process.h"

class ProcessQueue;

class ReadingProcess : public Process
{
private:
    ProcessQueue *queue;

public:
    ReadingProcess(ProcessQueue *q, int pid_override = -1);
    void execute() override;
    string serialize() const override;
    string typeName() const override;
    void printInfo() const override;
};

#endif // GB_POO_READINGPROCESS_H