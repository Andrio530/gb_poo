# Trabalho Grau B - Sistema de Gerenciamento de Processos

## Descrição
Este projeto implementa um sistema de gerenciamento de processos em C++ sem o uso da biblioteca `std::list`.  
A estrutura de dados é baseada em uma **lista encadeada própria**, e o sistema permite criar, executar, salvar e carregar processos.

### Tipos de Processos
- **ComputingProcess:** Executa expressões matemáticas simples.
- **WritingProcess:** Grava expressões no arquivo `computation.txt`.
- **ReadingProcess:** Lê `computation.txt` e cria novos `ComputingProcess` para cada linha.
- **PrintingProcess:** Exibe todos os processos na fila.

## Estrutura
```
TrabalhoGrauB/
├── main.cpp
├── Process.h / Process.cpp
├── ProcessQueue.h / ProcessQueue.cpp
├── Sistema.h / Sistema.cpp
├── Makefile
└── README.md
```

## Compilação
```
make
```

## Execução
```
./TrabalhoGrauB
```

## Autor
Ândrio Gabriel Epping

Lucca Jaroszeski Becker
