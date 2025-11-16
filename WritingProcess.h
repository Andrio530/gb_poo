//
// Created by Lucca Jaroszeski Becker on 16/11/25.
//

#ifndef GB_POO_WRITINGPROCESS_H
#define GB_POO_WRITINGPROCESS_H
#include "Process.h"

using namespace std;

class WritingProcess : public Process
{
private:
    string expr;

public:
    WritingProcess(const string &expression, int pid_override = -1);
    void execute() override;
    string serialize() const override;
    string typeName() const override;
    void printInfo() const override;
};

#endif // GB_POO_WRITINGPROCESS_H