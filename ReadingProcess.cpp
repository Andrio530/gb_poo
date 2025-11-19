//
// Created by Lucca Jaroszeski Becker on 16/11/25.
//

#include "ReadingProcess.h"

#include "ComputingProcess.h"
#include "ProcessQueue.h"

#include <iostream>
#include <fstream>
#include <string>

ReadingProcess::ReadingProcess(ProcessQueue *q, int pid_override)
    : Process(pid_override), queue(q) {}
void ReadingProcess::execute()
{
    ifstream ifs("computation.txt");
    if (!ifs)
    {
        cout << "Arquivo computation.txt inexistente\n";
        return;
    }
    string line;
    int added = 0;
    while (getline(ifs, line))
        if (!line.empty())
        {
            queue->push_back(new ComputingProcess(line));
            added++;
        }
    ofstream ofs("computation.txt", ios::trunc);
    ofs.close();
    cout << "[ReadingProcess] adicionou " << added << " ComputingProcess(es)\n";
}
string ReadingProcess::serialize() const { return "READ|" + to_string(pid); }
string ReadingProcess::typeName() const { return "ReadingProcess"; }
void ReadingProcess::printInfo() const { cout << "PID=" << pid << " - ReadingProcess\n"; }