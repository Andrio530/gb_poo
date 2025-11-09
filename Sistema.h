#ifndef SISTEMA_H
#define SISTEMA_H
#include "ProcessQueue.h"
class Sistema {
private:
    ProcessQueue queue;
public:
    void run();
private:
    void criarProcesso();
    void executarProximo();
    void executarEspecifico();
    void salvarFila();
    void carregarFila();
};
#endif
