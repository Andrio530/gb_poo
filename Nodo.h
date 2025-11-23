#ifndef ESTRUTURAS_NODO_H
#define ESTRUTURAS_NODO_H

template<class T>
class Nodo {
public:
    Nodo(const T& valor);
    Nodo();
    ~Nodo() {};

    void setDado(const T& valor);
    T& getDado();

    void setProximo(Nodo<T>*);
    Nodo<T>* getProximo();

    void setAnterior(Nodo<T>*);
    Nodo<T>* getAnterior();

private:
    T dado;
    Nodo<T>* proximo = nullptr;
    Nodo<T>* anterior = nullptr;

    int tamanho = 0;
};

template<class T>
Nodo<T>::Nodo(const T& valor) {
    dado = valor;
}

template<class T>
void Nodo<T>::setDado(const T& valor) {
    dado = valor;
}

template<class T>
T& Nodo<T>::getDado() {
    return dado;
}


template<class T>
void Nodo<T>::setProximo(Nodo<T> * p) {
    proximo = p;
}

template<class T>
Nodo<T>* Nodo<T>::getProximo() {
    return proximo;
}

template<class T>
void Nodo<T>::setAnterior(Nodo<T> * a) {
    anterior = a;
}

template<class T>
Nodo<T>* Nodo<T>::getAnterior() {
    return anterior;
}


#endif //ESTRUTURAS_NODO_H