#include "Process.h"
#include "ProcessQueue.h"
int Process::next_pid = 1;

Process::Process(int pid_override) {
    if (pid_override >= 0) {
        pid = pid_override;
        if (pid_override >= next_pid) next_pid = pid_override + 1;
    } else pid = next_pid++;
}
int Process::getPid() const { return pid; }

ComputingProcess::ComputingProcess(const string &expression, int pid_override)
: Process(pid_override), expr(expression) {}
void ComputingProcess::execute() {
    cout << "[ComputingProcess] PID=" << pid << " executando: " << expr << " -> ";
    stringstream ss(expr);
    double a,b; char op;
    if (!(ss >> a >> op >> b)) { cout << "Erro de sintaxe\n"; return; }
    double res=0; bool ok=true;
    switch(op){
        case '+':res=a+b;break;
        case '-':res=a-b;break;
        case '*':res=a*b;break;
        case '/':if(b==0){ok=false;cout<<"Div/0\n";}else res=a/b;break;
        default:ok=false;cout<<"Operador invalido\n";break;
    }
    if(ok) cout << res << "\n";
}
string ComputingProcess::serialize() const {return "COMPUTE|"+to_string(pid)+"|"+expr;}
string ComputingProcess::typeName() const {return "ComputingProcess";}
void ComputingProcess::printInfo() const {cout<<"PID="<<pid<<" - ComputingProcess expr='"<<expr<<"'\n";}

WritingProcess::WritingProcess(const string &expression, int pid_override)
: Process(pid_override), expr(expression) {}
void WritingProcess::execute() {
    ofstream ofs("computation.txt", ios::app);
    if(!ofs){cout<<"Erro abrir computation.txt\n";return;}
    ofs<<expr<<"\n";ofs.close();
    cout<<"[WritingProcess] gravou '"<<expr<<"'\n";
}
string WritingProcess::serialize() const {return "WRITE|"+to_string(pid)+"|"+expr;}
string WritingProcess::typeName() const {return "WritingProcess";}
void WritingProcess::printInfo() const {cout<<"PID="<<pid<<" - WritingProcess expr='"<<expr<<"'\n";}

ReadingProcess::ReadingProcess(ProcessQueue *q, int pid_override)
: Process(pid_override), queue(q) {}
void ReadingProcess::execute() {
    ifstream ifs("computation.txt");
    if(!ifs){cout<<"Arquivo computation.txt inexistente\n";return;}
    string line;int added=0;
    while(getline(ifs,line)) if(!line.empty()){queue->push_back(new ComputingProcess(line));added++;}
    ofstream ofs("computation.txt",ios::trunc);ofs.close();
    cout<<"[ReadingProcess] adicionou "<<added<<" ComputingProcess(es)\n";
}
string ReadingProcess::serialize() const {return "READ|"+to_string(pid);}
string ReadingProcess::typeName() const {return "ReadingProcess";}
void ReadingProcess::printInfo() const {cout<<"PID="<<pid<<" - ReadingProcess\n";}

PrintingProcess::PrintingProcess(ProcessQueue *q, int pid_override):Process(pid_override),queue(q){}
void PrintingProcess::execute(){cout<<"[PrintingProcess] PID="<<pid<<"\n";queue->printAll();}
string PrintingProcess::serialize() const{return "PRINT|"+to_string(pid);}
string PrintingProcess::typeName() const{return "PrintingProcess";}
void PrintingProcess::printInfo() const{cout<<"PID="<<pid<<" - PrintingProcess\n";}
