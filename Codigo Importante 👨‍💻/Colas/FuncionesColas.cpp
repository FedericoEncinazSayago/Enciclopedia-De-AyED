#include <iostream>
using namespace std;

struct NodoCola
{
    int info;
    NodoCola*sig;
};

int main()
{
    NodoCola *primero = NULL;
    NodoCola *ultimo = NULL;


    return 0;
}

void encolar(NodoCola *&pri, NodoCola *&ult, int dato)
{
    NodoCola *nuevo = new NodoCola;
    nuevo->info = dato;
    nuevo->sig = NULL;

    if (ult != NULL)
    {
        ult->sig = nuevo;
    }
    else
    {
        pri = nuevo;
    }

    ult = nuevo;
}

int desencolar(NodoCola *&pri, NodoCola *&ult)
{
    int dato;
    NodoCola *aux = pri;
    pri = pri->sig;
    dato = aux->info;
    
    delete aux;

    if (pri == NULL)
    {
        ult = NULL;
    }

    return dato;
}