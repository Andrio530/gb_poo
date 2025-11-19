#include "Sistema.h"

#include "ComputingProcess.h"
#include "WritingProcess.h"
#include "ReadingProcess.h"
#include "PrintingProcess.h"

void Sistema::run()
{
    while (true)
    {
        cout << "\n1) Criar\n2) Exec proximo\n"
                "3) Exec PID\n"
                "4) Salvar\n"
                "5) Carregar\n"
                "6) Print\n"
                "0) Sair\nEscolha: ";
        string s;
        if (!getline(cin, s))
            break;
        if (s.empty())
            continue;
        int op = stoi(s);
        if (op == 0)
            break;
        switch (op)
        {
        case 1:
            criarProcesso();
            break;
        case 2:
            executarProximo();
            break;
        case 3:
            executarEspecifico();
            break;
        case 4:
            salvarFila();
            break;
        case 5:
            carregarFila();
            break;
        case 6:
            queue.printAll();
            break;
        default:
            cout << "Opcao invalida\n";
        }
    }
}
void Sistema::criarProcesso()
{
    cout << "1) Computing\n"
            "2) Writing\n"
            "3) Reading\n"
            "4) Printing\n"
            "Tipo: ";
    string s;
    getline(cin, s);
    int t = stoi(s);
    if (t == 1)
    {
        string e;
        cout << "Expr: ";
        getline(cin, e);
        queue.push_back(new ComputingProcess(e));
    }
    else if (t == 2)
    {
        string e;
        cout << "Expr p/gravar: ";
        getline(cin, e);
        queue.push_back(new WritingProcess(e));
    }
    else if (t == 3)
    {
        queue.push_back(new ReadingProcess(&queue));
    }
    else if (t == 4)
    {
        queue.push_back(new PrintingProcess(&queue));
    }
    else
        cout << "Tipo invalido\n";
}
void Sistema::executarProximo()
{
    if (queue.empty())
    {
        cout << "Fila vazia\n";
        return;
    }
    Process *p = queue.pop_front();
    p->execute();
    delete p;
}
void Sistema::executarEspecifico()
{
    cout << "PID: ";
    string s;
    getline(cin, s);
    int pid = stoi(s);
    Process *p = queue.remove_by_pid(pid);
    if (!p)
    {
        cout << "Nao encontrado\n";
        return;
    }
    p->execute();
    delete p;
}
void Sistema::salvarFila()
{
    cout << "Arquivo (def:fila_processos.txt): ";
    string fn;
    getline(cin, fn);
    if (fn.empty())
        fn = "fila_processos.txt";
    if (queue.saveToFile(fn))
        cout << "Salvo em '" << fn << "'\n";
    else
        cout << "Erro salvar\n";
}
void Sistema::carregarFila()
{
    cout << "Arquivo (def:fila_processos.txt): ";
    string fn;
    getline(cin, fn);
    if (fn.empty())
        fn = "fila_processos.txt";
    if (queue.loadFromFile(fn))
        cout << "Carregado de '" << fn << "'\n";
    else
        cout << "Erro carregar\n";
}
