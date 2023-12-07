/*Desarrollar una función que dada una cola elimine 4 nodos de la misma, y devuelva un valor true si ello fue posible, de lo contrario un valor falso.*/

#include <iostream>

using namespace std;

struct Alumnos
{
    int Legajo,Nota;
    string Nombre;
};

struct NodoCola
{
    Alumnos Info;
    NodoCola*Sig;
};

void CargaDeDatos(NodoCola*&Primero,NodoCola*&Ultimo);
void Encolar(NodoCola*&Primero,NodoCola*&Ultimo,Alumnos Dato);
bool Punto1(NodoCola*&Primero,NodoCola*&Ultimo);
void Desencolar(NodoCola*&Primero,NodoCola*&Ultimo,Alumnos &Dato);

int main()
{
    bool Verificador;
    NodoCola*Primero = NULL;
    NodoCola*Ultimo = NULL;

    CargaDeDatos(Primero,Ultimo);

    Verificador = Punto1(Primero,Ultimo);

    if(Verificador)
    {
        cout << "Se pudo desencolar 4 elementos de la cola" << endl;

    }
    else
    {
        cout << "---------------------------------" << endl;
        cout << "No se pudo realizar la funcion del programa, porque la pila esta vacia o la cantidad de elementos no fue la indicada" << endl;
    }

    return 0;
}

void CargaDeDatos(NodoCola*&Primero,NodoCola*&Ultimo)
{
    Alumnos A;

    cout << "INFORME legajo del alumno: ";
    cin >> A.Legajo;

    while(A.Legajo != 0)
    {
        cout << "INFORME nombre del alumno: ";
        cin >> A.Nombre;

        cout << "INFORME nota del alumno: ";
        cin >> A.Nota;

        Encolar(Primero,Ultimo,A);

        cout << "---------------------------------" << endl;
        cout << "INFORME legajo del siguiente alumno: ";
        cin >> A.Legajo;
    }
}

void Encolar(NodoCola*&Primero,NodoCola*&Ultimo,Alumnos Dato)
{
    NodoCola*Aux = new NodoCola;
    Aux->Info = Dato;
    Aux->Sig = NULL;

    if(Ultimo != NULL)
    {
        Ultimo->Sig = Aux;
    }
    else
    {
        Primero = Aux;
    }

    Ultimo = Aux;
}

bool Punto1(NodoCola*&Primero,NodoCola*&Ultimo)
{
    Alumnos A;
    int i = 0;

    while(Primero != NULL && i <= 4)
    {
        Desencolar(Primero,Ultimo,A);

        i++;
    }

    return i == 4;
}

void Desencolar(NodoCola*&Primero,NodoCola*&Ultimo,Alumnos &Dato)
{
    NodoCola*Aux = Primero;
    Dato = Aux->Info;
    Primero = Aux->Sig;

    delete Aux;

    if(Primero == NULL)
    {
        Ultimo = NULL;
    }
}

