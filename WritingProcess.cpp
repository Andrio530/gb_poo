//
// Created by Lucca Jaroszeski Becker on 16/11/25.
//

#include "WritingProcess.h"

WritingProcess::WritingProcess(const string &expression, int pid_override)
    : Process(pid_override), expr(expression) {}
void WritingProcess::execute()
{
    ofstream ofs("computation.txt", ios::app);
    if (!ofs)
    {
        cout << "Erro abrir computation.txt\n";
        return;
    }
    ofs << expr << "\n";
    ofs.close();
    cout << "[WritingProcess] gravou '" << expr << "'\n";
}
string WritingProcess::serialize() const { return "WRITE|" + to_string(pid) + "|" + expr; }
string WritingProcess::typeName() const { return "WritingProcess"; }
void WritingProcess::printInfo() const { cout << "PID=" << pid << " - WritingProcess expr='" << expr << "'\n"; }