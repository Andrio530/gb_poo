//
// Created by Lucca Jaroszeski Becker on 16/11/25.
//

#include "PrintingProcess.h"

#include "ProcessQueue.h"

PrintingProcess::PrintingProcess(ProcessQueue *q, int pid_override) : Process(pid_override), queue(q) {}
void PrintingProcess::execute()
{
  cout << "[PrintingProcess] PID=" << pid << "\n";
  queue->printAll();
}
string PrintingProcess::serialize() const { return "PRINT|" + to_string(pid); }
string PrintingProcess::typeName() const { return "PrintingProcess"; }
void PrintingProcess::printInfo() const { cout << "PID=" << pid << " - PrintingProcess\n"; }
