/*Desarrollar una función que dada una pila y dos valores x e y, reemplace cada valor igual a y que se encuentre en la pila por el valor x, retornando la pila modificada. */

#include <iostream>

using namespace std;

struct Nodo
{
    int Info;
    Nodo*Sig;
};

void CargaDeDatos(Nodo*&Pila);
void Apilar(Nodo*&Pila,int Dato);
void Punto1(Nodo*&Pila,int x,int y);
void Desapilar(Nodo*&Pila,int &Dato);
void MostrarPilaActualizada(Nodo*&Pila);

int main()
{
    int x,y;
    Nodo*PilaDeNro = NULL;

    CargaDeDatos(PilaDeNro);

    cout << "---------------------------------" << endl;
    cout << "INGRESE el valor en ser reemplazado: ";
    cin >> y;

    cout << "---------------------------------" << endl;
    cout << "INGRESE el valor reemplazador: ";
    cin >> x;

    Punto1(PilaDeNro,x,y);

    return 0;
}

void CargaDeDatos(Nodo*&Pila)
{
    int Nro;

    cout << "INFORME el primer valor en ser apilado: ";
    cin >> Nro;

    while(Nro != 0)
    {
        Apilar(Pila,Nro);

        cout << "---------------------------------" << endl;
        cout << "INFORME el siguiente valor en ser apilado (0 para finalizar): ";
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

void Punto1(Nodo*&Pila,int x,int y)
{
    int Nro;
    bool Verificador = false;
    Nodo*PilaAux = NULL;

    if(Pila != NULL)
    {
        while(Pila != NULL)
        {
            Desapilar(Pila,Nro);

            if(Nro == y)
            {
                Apilar(PilaAux,x);

                Verificador = true;
            }
            else
            {
                Apilar(PilaAux,Nro);
            }
        }

        while(PilaAux != NULL)
        {
            Desapilar(PilaAux,Nro);
            Apilar(Pila,Nro);
        }

        if(Verificador)
        {
            cout << "Se pudo reemplazar todos elementos iguales a " << y << " por el valor igual a " << x << endl;
            cout << "---------------------------------" << endl;
            cout << "Pila actualizada:" << endl;

            MostrarPilaActualizada(Pila);

            cout << "---------------------------------" << endl;
        }
        else
        {
            cout << "No se puedo reemplazar ningun valor" << endl;
        }
    }
    else
    {
        cout << "---------------------------------" << endl;
        cout << "No se pudo seguir con la ejecucion del programa, porque la pila esta vacia" << endl;
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

void MostrarPilaActualizada(Nodo*&Pila)
{
    int Nro;

    while(Pila != NULL)
    {
        Desapilar(Pila,Nro);

        cout << Nro << endl;
    }
}
