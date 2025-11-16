//
// Created by Lucca Jaroszeski Becker on 16/11/25.
//

#ifndef GB_POO_PRINTINGPROCESS_H
#define GB_POO_PRINTINGPROCESS_H
#include "Process.h"

class PrintingProcess : public Process
{
private:
    ProcessQueue *queue;

public:
    PrintingProcess(ProcessQueue *q, int pid_override = -1);
    void execute() override;
    string serialize() const override;
    string typeName() const override;
    void printInfo() const override;
};

#endif // GB_POO_PRINTINGPROCESS_H