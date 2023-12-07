/*Dada una lista doblemente encadenada de números eliminar los últimos n nodos*/

#include <iostream>

using namespace std;

struct Nodo
{
    int Info;
    Nodo *Ant,*Sgte;
};

void CargaDeDatos(Nodo*&Primero,Nodo*&Ultimo);
void EliminarNodos(Nodo*&Ultimo,int Nro);
void InsertarAdelante(Nodo*&Primero,Nodo*&Ultimo,int Nro);
void MostrarLista(Nodo*Primero);

int main()
{
    int Nro;
    Nodo *Primero = NULL,*Ultimo = NULL;

    CargaDeDatos(Primero,Ultimo);

    cout << "---------------------------------" << endl;
    cout << "INFORME cantidad de nodos a eliminar: ";
    cin >>  Nro;

    EliminarNodos(Ultimo,Nro);

    cout << "---------------------------------" << endl;
    cout << "Lista actualizada: " << endl;

    MostrarLista(Primero);

    cout << "---------------------------------" << endl;

    return 0;
}

void CargaDeDatos(Nodo*&Primero,Nodo*&Ultimo)
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
    Nodo *Antecesor;
    Nodo *Nuevo = new Nodo;
    Nuevo->Info = Nro;
    Nuevo->Sgte = Primero;
    Nuevo->Ant = NULL;

    if(Primero == NULL)
    {
        Ultimo = Nuevo;
    }
    else
    {
        Primero->Ant = Nuevo;
    }

    Primero = Nuevo;
}

void EliminarNodos(Nodo*&Primero,Nodo*&Ultimo,int Nro)
{
    int i = 0;
    Nodo *Aux;

    while(Ultimo != NULL && i < Nro)
    {
        Aux = Ultimo;
        Ultimo = Ultimo->Ant;

        delete Aux;

        i++;
    }

    if(Ultimo == NULL)
    {
        Primero = NULL;
    }
    else
    {
        Ultimo->Sgte = NULL;
    }
}

void MostrarLista(Nodo*Primero)
{
    Nodo *Aux = Primero;

    while(Aux != NULL)
    {
        cout << "Numero: " << Aux->Info << endl;

        Aux = Aux->Sgte;
    }
}

//Funciones a necesitar:
/*void EliminarNodo(Nodo*&Primero,Nodo*&Ultimo,int Nro)
{
    Nodo *Siguiente,*Antecesor,*Aux;
    Aux = Primero;

    while(Aux != NULL)
    {
        if(Aux->Info == Nro)
        {
            if(Aux == Primero)
            {
                Primero = Aux->Sgte;
                Primero->Ant = NULL;
            }
            else
            {
                if(Aux == Ultimo)
                {
                    Ultimo = Aux->Ant;
                    Ultimo->Sgte = NULL;
                }
                else
                {
                    Antecesor = Aux->Ant;
                    Siguiente = Aux->Sgte;
                    Siguiente->Ant = Antecesor;
                    Antecesor->Sgte = Siguiente;
                }
            }

            delete Aux;
        }

        Aux = Aux->Sgte;
    }
}*/
