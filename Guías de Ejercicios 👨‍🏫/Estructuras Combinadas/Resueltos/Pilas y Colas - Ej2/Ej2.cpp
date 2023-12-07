/*Desarrollar una función que dada una pila y un valor, inserte ese valor como tercer elemento de la pila.*/

#include <iostream>

using namespace std;

struct Nodo
{
    int Info;
    Nodo*Sig;
};

void CargaDeDatos(Nodo*&Pila);
void Apilar(Nodo*&Pila,int Dato);
void Punto1(Nodo*&Pila,int Nro);
void Desapilar(Nodo*&Pila,int &Dato);
void MostrarPilaDesapilada(Nodo*&Pila);

int main()
{
    int Nro;
    Nodo*PilaDeNumeros = NULL;

    CargaDeDatos(PilaDeNumeros);

    cout << "---------------------------------" << endl;
    cout << "Ingrese valor a reemplazar en la tercera posicion: ";
    cin >> Nro;

    Punto1(PilaDeNumeros,Nro);

    return 0;
}

void CargaDeDatos(Nodo*&Pila)
{
    int Nro;

    cout << "INFORME primer valor apilado: ";
    cin >> Nro;

    while(Nro != 0)
    {
        Apilar(Pila,Nro);

        cout << "---------------------------------" << endl;
        cout << "INFORME el siguiente valor apilado (0 para finalizar): ";
        cin >> Nro;
    }
}

void Apilar(Nodo*&Pila,int Dato)
{
    Nodo*Aux = new Nodo;
    Aux->Info = Dato;
    Aux->Sig = Pila;
    Pila = Aux;
}

void Punto1(Nodo*&Pila,int Nro)
{
    int i = 0,j = 1,Dato;
    Nodo*PilaAux = NULL;

    while(Pila != NULL)
    {
        Desapilar(Pila,Dato);
        Apilar(PilaAux,Dato);

        i++;
    }

    if(i > 2)
    {
        while(PilaAux != NULL && j < i)
        {
            Desapilar(PilaAux,Dato);
            Apilar(Pila,Dato);

            if(j == 2)
            {
                Desapilar(PilaAux,Dato);
                Apilar(Pila,Nro);
            }

            j++;
        }

        cout << "Se pudo reemplazar el elemento dado en la tercera posicion" << endl;
        cout << "---------------------------------" << endl;
        cout << "Listado de la pila actualizada: " << endl;

        MostrarPilaDesapilada(Pila);

        cout << "---------------------------------" << endl;
    }
    else
    {
        cout << "---------------------------------" << endl;
        cout << "No se pudo seguir con la ejecucion del programa, porque la pila esta vacia o bien la cantidad de elementos no es la indicada" << endl;
    }

}

void Desapilar(Nodo*&Pila,int &Dato)
{
    Nodo*Aux;
    Aux = Pila;
    Dato = Aux->Info;
    Pila = Aux->Sig;

    delete Aux;
}

void MostrarPilaDesapilada(Nodo*&Pila)
{
    int Dato;

    while(Pila != NULL)
    {
        Desapilar(Pila,Dato);

        cout << Dato << endl;
    }
}


