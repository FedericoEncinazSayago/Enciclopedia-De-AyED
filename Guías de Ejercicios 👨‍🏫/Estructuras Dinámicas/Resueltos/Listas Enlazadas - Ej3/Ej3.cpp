/*Hacer una función que devuelva la lista del ejercicio 2 ordenada alfabéticamente.*/

#include <iostream>

using namespace std;

struct Inscriptos
{
    int DNI;
    string Nombre;
};

struct Nodo
{
    Inscriptos Info;
    Nodo *Sgte;
};

void CargaDeDatos(Nodo*&Lista);
void InsertarAdelante(Nodo*&Lista,Inscriptos Dato);
void OrdenarLista(Nodo*&Lista);
void InsertarLogico(Nodo*&Lista,Nodo*Nuevo);
void MostrarLista(Nodo*Lista);

int main()
{
    Nodo *Lista = NULL;

    CargaDeDatos(Lista);

    OrdenarLista(Lista);

    cout << "Lista actualizada:" << endl;

    MostrarLista(Lista);

    cout << "---------------------------------" << endl;

    return 0;
}

void CargaDeDatos(Nodo*&Lista)
{
    Inscriptos I;

    cout << "INFORME dni del alumno: ";
    cin >> I.DNI;

    while(I.DNI != 0)
    {
        cout << "INFORME nombre del alumno: ";
        cin >> I.Nombre;

        InsertarAdelante(Lista,I);

        cout << "---------------------------------" << endl;
        cout << "INFORME dni del Sgteuiente alumno (0 para finalizar): ";
        cin >> I.DNI;
    }
}

void InsertarAdelante(Nodo*&Lista,Inscriptos dato)//Mucho más eficiente que ir agredando de atras. Toma la logica de los punteros de las pilas!
{
    Nodo *Nuevo = new Nodo;
    Nuevo->Info = Dato;
    Nuevo->Sgte = lista;
    Lista = Nuevo;
}

void OrdenarLista(Nodo*&Lista)
{
    Nodo *ListaOrd = NULL;
    Nodo *Nuevo;

    while(Lista!=NULL)
    {
        Nuevo = Lista;
        Lista = Lista->Sgte;

        InsertarLogico(ListaOrd,Aux);
    }

    Lista = ListaOrd;
}

void InsertarLogico(Nodo*&Lista,Nodo*Nuevo)//Inserta elementos a la lista conservando el orden
{
    Nodo *Aux,*Antecesor;
    Aux = Lista;

    while(Aux != NULL && Aux->Info.Nombre < Nuevo->Info.Nombre)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    Nuevo->Sgte = Aux;

    if(Aux != Lista)
    {
        Antecesor->Sgte = Nuevo;
    }
    else
    {
        Lista = Nuevo;
    }
}

void MostrarLista(Nodo*Lista)
{
    Nodo *Aux = Lista;

    while(Aux != NULL)
    {
        cout << "DNI del alumno: " << Aux->Info.DNI << " - " << "Nombre del alumno: " << Aux->Info.Nombre << endl;

        Aux = Aux->Sgte;
    }
}
