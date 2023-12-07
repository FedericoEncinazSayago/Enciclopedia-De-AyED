/*Dada una lista doblemente encadenada de números enganchada solo por el puntero al siguiente y con todos los punteros al anterior en NULL, se pide hacer una rutina que la recorra y complete los punteros convenientemente incluyendo el puntero externo para recorrerla de atrás hacia adelante.*/

#include <iostream>

using namespace std;

struct Nodo
{
    int Info;
    Nodo *Ant,*Sgte;
};

void CargaDeDatos(Nodo*&Primero,Nodo*&Ultimo);
void InsertarAdelante(Nodo*&Primero,Nodo*&Ultimo,int Nro);
void UnirEnlances(Nodo*Primero);
void MostrarListaInversa(Nodo*Ultimo);

int main()
{
    Nodo *Primero = NULL,*Ultimo = NULL;

    CargaDeDatos(Primero,Ultimo);

    UnirEnlances(Primero);

    cout << "---------------------------------" << endl;
    cout << "Lista en manera inversa: " << endl;

    MostrarListaInversa(Ultimo);

    cout << "---------------------------------" << endl;

    return 0;
}

void CargaDeDatos(Nodo*&Lista,Nodo*&Ultimo)
{
    int Nro;

    cout << "INFORME numero a enlazar: ";
    cin >> Nro;

    while(Nro != 0)
    {
        InsertarAdelante(Primero,Ultimo,Nro);

        cout << "---------------------------------" << endl;
        cout << "INFORME el siguiente numero a enlazar (0 para finalizar): ";
        cin >> Nro;
    }
}

void InsertarAdelante(Nodo*&Primero,Nodo*&Ultimo,int Nro)
{
    Nodo *Nuevo = new Nodo;
    Nuevo->Info = Nro;
    Nuevo->Ant = NULL;
    Nuevo->Sgte = Primero;

    if(Primero == NULL)
    {
        Ultimo = Nuevo;
    }

    Primero = Nuevo;
}

void UnirEnlances(Nodo*Primero)
{
    Nodo *Aux,*Antecesor;
    Aux = Primero;
    Antecesor = NULL;

    while(Aux != NULL)
    {
        Aux->Ant = Antecesor;
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }
}

void MostrarListaInversa(Nodo*Ultimo)
{
    Nodo *Aux = Ultimo;

    while(Aux != NULL)
    {
        cout << "Numero: " << Aux->Info << endl;

        Aux = Aux->Ant;
    }
}

//Funciones a necesitar:

/*void Insertar(Nodo*&Primero,Nodo*&Ultimo,int Nro)
{
    Nodo *Nuevo,*Antecesor,*Aux;
    Nuevo = new Nodo;
    Nuevo->Info = Nro;
    Aux = Primero;

    while(Aux != NULL && Aux->Info < Nro)
    {
        Aux = Aux->Sgte;
    }

    Nuevo->Sgte = Aux;

    if(Aux != Primero)
    {
        if(Aux != NULL)
        {
            Antecesor = Aux->Ant;
            Antecesor->Sgte = Nuevo;
            Aux->Ant = Nuevo;
        }
        else
        {
            Ultimo->Sgte = Nuevo;
            Nuevo->Ant = Ultimo;
            Ultimo = Nuevo;
        }
    }
    else
    {
        if(Primero != NULL)
        {
            Primero->Ant = Nuevo;
        }
        else
        {
            Ultimo = Nuevo;
        }

        Nuevo->Ant = NULL;
        Primero = Nuevo;
    }
}*/
