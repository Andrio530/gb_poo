//
// Created by Lucca Jaroszeski Becker on 16/11/25.
//

#include "ComputingProcess.h"

ComputingProcess::ComputingProcess(const string &expression, int pid_override)
    : Process(pid_override), expr(expression) {}
void ComputingProcess::execute()
{
    cout << "[ComputingProcess] PID=" << pid << " executando: " << expr << " -> ";
    stringstream ss(expr);
    double a, b;
    char op;
    if (!(ss >> a >> op >> b))
    {
        cout << "Erro de sintaxe\n";
        return;
    }
    double res = 0;
    bool ok = true;
    switch (op)
    {
    case '+':
        res = a + b;
        break;
    case '-':
        res = a - b;
        break;
    case '*':
        res = a * b;
        break;
    case '/':
        if (b == 0)
        {
            ok = false;
            cout << "Div/0\n";
        }
        else
            res = a / b;
        break;
    default:
        ok = false;
        cout << "Operador invalido\n";
        break;
    }
    if (ok)
        cout << res << "\n";
}
string ComputingProcess::serialize() const { return "COMPUTE|" + to_string(pid) + "|" + expr; }
string ComputingProcess::typeName() const { return "ComputingProcess"; }
void ComputingProcess::printInfo() const { cout << "PID=" << pid << " - ComputingProcess expr='" << expr << "'\n"; }