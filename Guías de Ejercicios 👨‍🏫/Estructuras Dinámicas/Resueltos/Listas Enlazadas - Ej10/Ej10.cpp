/* Dada una lista simple de alumnos (n° de documento y nombre) ordenada por documento.
De cada alumno depende una sublista de exámenes rendidos (fecha, código y nota).
Hacer una función que dada la estructura informe número de documento, nombre y promedio de cada alumno*/

#include <iostream>

using namespace std;

struct Alumnos
{
    int DNI;
    string Nombre;
};

struct Notas
{
    int Fecha,CodDeExamen,Nota;
};

struct NodoSub
{
    Notas Info;
    NodoSub *Sgte;
};

struct Nodo
{
    Alumnos Info;
    NodoSub *SubLista;
    Nodo *Sgte;
};

void CargaDeDatos(Nodo*&Lista);
void Insertar(Nodo*&Lista,Alumnos Dato);
void CargaDeNotas(Nodo*Lista);
void InsertarNotas(NodoSub*&Lista,Notas Dato);
void CalcularPromedio(Nodo*Lista);
Nodo *BusquedaMejorada(Nodo*Lista,int DNI);

int main()
{
    Nodo *Lista = NULL;

    cout << "Comienzo de la carga de datos de los alumnos" << endl;

    CargaDeDatos(Lista);

    cout << "---------------------------------" << endl;
    cout << "Comienzo de carga de datos de examenes" << endl;

    CargaDeNotas(Lista);

    cout << "---------------------------------" << endl;
    cout << "Listado de los alumnos con su respectivo promedio: " << endl;

    CalcularPromedio(Lista);

    cout << "---------------------------------" << endl;

    return 0;
}

void CargaDeDatos(Nodo*&Lista)
{
    Alumnos A;

    cout << "INFORME dni el alumno: ";
    cin >> A.DNI;

    while(A.DNI != 0)
    {
        cout << "INFORME nombre del alumno: ";
        cin >> A.Nombre;

        Insertar(Lista,A);

        cout << "---------------------------------" << endl;
        cout << "INFORME dni del siguiente alumno (0 para finalizar): ";
        cin >> A.DNI;
    }
}

void Insertar(Nodo*&Lista,Alumnos Dato)
{
    Nodo *Nuevo,*Antecesor,*Aux;
    Nuevo = new Nodo;
    Nuevo->Info = Dato;
    Nuevo->SubLista = NULL;
    Aux = Lista;

    while(Aux != NULL && Aux->Info.DNI < Dato.DNI)
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

void CargaDeNotas(Nodo*Lista)
{
    int DNI;
    Notas N;
    Nodo *Aux;

    cout << "INFORME dni del alumno a buscar: ";
    cin >> DNI;

    while (DNI != 0)
    {
        Aux = BusquedaMejorada(Lista,DNI);

        if(Aux != NULL)
        {

            cout << "INFORME codigo de examen: ";
            cin >> N.CodDeExamen;

            while(N.CodDeExamen != 0)
            {
                cout << "INFORME fecha del examen (aaaa/mm/dd): ";
                cin >> N.Fecha;

                cout << "INFORME nota del examen: ";
                cin >> N.Nota;

                InsertarNotas(Aux->SubLista,N);

                cout << "---------------------------------" << endl;
                cout << "INFORME el siguiente codigo de examen: ";
                cin >> N.CodDeExamen;
            }

            cout << "Finalizacion de la carga de notas del alumno con DNI: " << Aux->Info.DNI << endl;
        }
        else
        {
            cout << "No se pudo encontrar al alumno con dni " << DNI << endl;
        }

        cout << "---------------------------------" << endl;
        cout << "INFORME el siguiente dni del alumno a buscar (0 para finalizar): ";
        cin >> DNI;
    }

}

void InsertarNotas(NodoSub*&Lista,Notas Dato)
{
    NodoSub *Nuevo = new NodoSub;
    Nuevo->Info = Dato;
    Nuevo->Sgte = Lista;
    Lista = Nuevo;
}

void CalcularPromedio(Nodo*Lista)
{
    float SumaDeNotas = 0,CantDeNotas = 0;
    Nodo *Aux;
    NodoSub *AuxDeNotas;
    Aux = Lista;

    while(Aux !=NULL)
    {
        AuxDeNotas = Aux->SubLista;

        while(AuxDeNotas != NULL)
        {
            SumaDeNotas = SumaDeNotas + AuxDeNotas->Info.Nota;
            CantDeNotas++;

            AuxDeNotas = AuxDeNotas->Sgte;
        }

        if(CantDeNotas != 0)
        {
            cout << "Nombre del alumno: " << Aux->Info.Nombre << " - " << "DNI del alumno : " << Aux->Info.DNI << " - " << "Promedio del alumno: " << SumaDeNotas/CantDeNotas << endl;
        }
        
        SumaDeNotas = 0;
        CantDeNotas = 0;
        Aux = Aux->Sgte;
    }
}

Nodo *BusquedaMejorada(Nodo*Lista,int DNI)
{
    Nodo *Aux;
    Aux = Lista;

    while(Aux != NULL && Aux->Info.DNI < DNI)
    {
        Aux = Aux->Sgte;
    }

    if(Aux == NULL || Aux->Info.DNI != DNI)
    {
        return NULL;
    }
    else
    {
        return Aux;
    }
}

