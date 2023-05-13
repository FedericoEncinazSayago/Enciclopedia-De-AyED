#include <iostream>

#define cantDeNumeros 10

using namespace std;

struct Nodo
{
    int dato;
    Nodo *siguiente;
};

void cargarPrograma(Nodo *&punteroLista);
void mostrarListado(Nodo *punteroLista);

int main()
{
    Nodo *punteroLista = NULL;

    cargarPrograma(punteroLista);
    mostrarListado(punteroLista);

    return 0;
}

void cargarPrograma(Nodo *&punteroLista)
{
    int nro;

    for (int i = 0; i < cantDeNumeros; i++)
    {
        cout << "Ingrese un numero: ";
        cin >> nro;

        insertarEnLista(punteroLista, nro);
    }
}

void insertarEnLista(Nodo *&punteroLista, int nro)
{
    Nodo *nuevo, *antecesor, *aux;
    nuevo = new Nodo;
    nuevo->dato = nro;
    aux = punteroLista;

    while (aux != NULL && aux->dato < nro)
    {
        antecesor = aux;
        aux = aux->siguiente;
    }

    nuevo->siguiente = aux;

    if (aux != punteroLista)
    {
        antecesor->siguiente = nuevo;
    }
    else
    {
        punteroLista = nuevo;
    }
}

void mostrarListado(Nodo *punteroLista)
{
    Nodo *aux = punteroLista;

    while (aux != NULL)
    {
        cout << aux->dato << endl;
        aux = aux->siguiente;
    }
}

// Funciones que pueden ser utiles:

Nodo *buscar(Nodo *lista, int dato)
{
    Nodo *aux = lista;
    
    while (aux != NULL && aux->dato != dato)
    {
        aux = aux->siguiente;
    }

    return aux;
}

Nodo *buscarMejor(Nodo *lista, int dato)
{
    Nodo *aux = lista;

    while (aux != NULL && aux->dato < dato)
    {
        aux = aux->siguiente;
    }

    return aux;
}

bool eliminar(Nodo *&lista, int dato)
{
    Nodo *aux, *antecesor;
    aux = lista;

    while (aux != NULL && aux->dato != dato)
    {
        antecesor = aux;
        aux = aux->siguiente;
    }

    if (aux != NULL)
    {
        if (aux == lista)
        {
            lista = aux->siguiente;
        }
        else
        {
            antecesor->siguiente = aux->siguiente;
        }

        delete aux;
        return true;
    }
    else
    {
        return false;
    }
}

Nodo* buscarInsertar(Nodo *&lista,int dato)
{
    Nodo *aux = lista, *antecesor;

    while (aux != NULL && aux->dato < dato)
    {
        antecesor = aux;
        aux = aux->siguiente;
    }

    if (aux != NULL && aux->dato == dato)
    {
        return aux;
    }
    else
    {
        Nodo *nuevo = new Nodo;
        nuevo->dato = dato;
        nuevo->siguiente = aux;

        if (aux != lista)
        {
            antecesor->siguiente = nuevo;
        }
        else
        {
            lista = nuevo;
        }

        return nuevo;
    }
}
