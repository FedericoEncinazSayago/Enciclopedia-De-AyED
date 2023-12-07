/*Dada una  pila sacar los dos elementos del tope y reemplazarlos por uno dado (agregar) */

#include <iostream>

using namespace std;

struct Libros
{
    string Titulo,Materia;
};

struct Nodo
{
    Libros Info;
    Nodo*Sig;
};

void CargarDatos(Nodo*&Pila,int Nro);
void Apilar(Nodo*&Pila,Libros Dato);
void Desapilar(Nodo*&Pila,Libros &Dato);

int main()
{
    int Nro,i = 1;
    Libros Aux;
    Nodo*PilaDeLibros = NULL;

    cout << "INFORME la cantidad de elementos original de su pila: ";
    cin >> Nro;

    cout << "---------------------------------" << endl;

    if(Nro != 0)
    {

        CargarDatos(PilaDeLibros,Nro);

        cout << "Cuanto elementos quiere desapilar?: ";
        cin >> Nro;

        while(PilaDeLibros != NULL && i <= Nro)
        {

            Desapilar(PilaDeLibros,Aux);

            cout << "Titulo del libro desapilado: " << Aux.Titulo << " - " << "Materia del titulo desapilado: " << Aux.Materia << endl;
            cout << "---------------------------------" << endl;

            i++;

        }
    }
    else
    {
        cout << "La pila esta vacia, no se puede desapilar ningun elemento" << endl;
    }

    cout << "Cuanto nuevos elementos quiere agregar?: ";
    cin >> Nro;

    CargarDatos(PilaDeLibros,Nro);

    cout << "Muestra de la Pila: " << endl;

    while(PilaDeLibros != NULL)
    {

        Desapilar(PilaDeLibros,Aux);

        cout << "Titulo del libro desapilado: " << Aux.Titulo << " - " << "Materia del titulo desapilado: " << Aux.Materia << endl;
        cout << "---------------------------------" << endl;
    }

    return 0;
}

void CargarDatos(Nodo*&Pila,int Nro)
{
    Libros L;

    for(int i = 1;i <= Nro;i++)
    {
        cout << "INFORME el titulo del libro: " ;
        cin >> L.Titulo;

        cout << "INFORME materia correspondiente al libro: ";
        cin >> L.Materia;

        Apilar(Pila,L);

        cout << "---------------------------------" << endl;
    }
}

void Apilar(Nodo*&Pila,Libros Dato)
{
    Nodo*P = new Nodo;
    P->Info = Dato;
    P->Sig = Pila;
    Pila = P;
}

void Desapilar(Nodo*&Pila,Libros &Dato)
{
    Nodo*P;
    P = Pila;
    Dato = P->Info;
    Pila = P->Sig;

    delete P;
}

