/*Se tiene lista enlazada donde cada nodo contiene nombre y número de documento de las personas inscriptas en un curso, ordenada por número de documento.
Hacer funciones para:
a. agregar un inscripto al curso, considerar que puede estar la lista vacía o ya contener información.
b. dar de baja una persona  que no concurrirá al curso. 
c. imprimir la lista completa.
d. Imprimir la lista en orden inverso (ordenada por documento de mayor a menor)*/


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
    Nodo*Sig;
};

void Punto1(Nodo*&Lista);
void Punto2(Nodo*&Lista,int DNI);
void Punto3(Nodo*&Lista);
void Punto4(Nodo*Lista);
void Insertar(Nodo*&Lista,Inscriptos Dato);
void Apilar(Nodo*&Pila,Inscriptos Dato);
void Desapilar(Nodo*&Pila,Inscriptos &Dato);

int main()
{
    int DNI;
    Nodo *Lista = NULL;

    Punto1(Lista);

    cout << "---------------------------------" << endl;
    cout << "INFORME dni de la persona que no asistira al curso: ";
    cin >> DNI;

    Punto2(Lista,DNI);

    cout << "---------------------------------" << endl;
    cout << "Lista actualizada: " << endl;

    Punto3(Lista);

    cout << "---------------------------------" << endl;
    cout << "Lista en orden inverso: " << endl;

    Punto4(Lista);

    cout << "---------------------------------" << endl;

    return 0;
}

void Punto1(Nodo*&Lista)
{
    Inscriptos I;

    cout << "INFORME dni del alumno: ";
    cin >> I.DNI;

    while(I.DNI != 0)
    {
        cout << "INFORME nombre del alumno: ";
        cin >> I.Nombre;

        Insertar(Lista,I);

        cout << "---------------------------------" << endl;
        cout << "INFORME dni del siguiente alumno (0 para finalizar): ";
        cin >> I.DNI;
    }
}


void Punto2(Nodo*&Lista,int DNI)
{
    Nodo *Aux;
    Nodo *Aux2;
    Aux = Lista;

    while(Aux != NULL)
    {
        if(Aux->Info.DNI == DNI)
        {
            if(Aux == Lista)
            {
                Lista = Aux->Sig;
            }
            else
            {
                Aux2->Sig = Aux->Sig;
            }

            delete Aux;
        }

        Aux2 = Aux;
        Aux = Aux->Sig;
    }
}

void Punto3(Nodo*&Lista)
{
    Nodo *Aux;
    Aux = Lista;

    while(Aux != NULL)
    {
        cout << "DNI del alumno: " << Aux->Info.DNI << " - " << "Nombre del alumno: " << Aux->Info.Nombre << endl;

        Aux = Aux->Sig;
    }
}

void Punto4(Nodo*Lista)
{
    Inscriptos I;
    Nodo *Aux = Lista;
    Nodo *PilaAux = NULL;

    while(Aux != NULL)
    {
        Apilar(PilaAux,Aux->Info);

        Aux = Aux->Sig;
    }

    while(PilaAux != NULL)
    {
        Desapilar(PilaAux,I);

        cout << "DNI del alumno: " << I.DNI << " - " << "Nombre del alumno: " << I.Nombre << endl;
    }
}

void Insertar(Nodo*&Lista,Inscriptos Dato)//Inserta elementos a la lista conservando el orden
{
    Nodo *Nuevo,*Antecesor,*Aux;
    Nuevo = new Nodo;
    Nuevo->Info = Dato;
    Aux = Lista;

    while(Aux != NULL && Aux->Info.DNI < Dato.DNI)
    {
        Antecesor = Aux;
        Aux = Aux->Sig;
    }

    Nuevo->Sig = Aux;

    if(Aux != Lista)
    {
        Antecesor->Sig = Nuevo;
    }
    else
    {
        Lista = Nuevo;
    }

}

void Apilar(Nodo*&Pila,Inscriptos Dato)
{
    Nodo *Aux = new Nodo;
    Aux->Info = Dato;
    Aux->Sig = Pila;
    Pila = Aux;
}

void Desapilar(Nodo*&Pila,Inscriptos &Dato)
{
    Nodo *Aux;
    Aux = Pila;
    Dato = Aux->Info;
    Pila = Aux->Sig;

    delete Aux;
}
