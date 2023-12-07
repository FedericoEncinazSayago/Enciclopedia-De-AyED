/*Desarrollar una función que dada una cola de personas (de cada persona se tiene dni y nombre) y un dni, si esta persona está en la cola, la mueva al último lugar de la misma.*/ 

#include <iostream>
#include <string.h>

using namespace std;

struct Personas
{
    int Dni;
    string Nombre;
};

struct NodoCola
{
    Personas Info;
    NodoCola*Sig;
};

void CargaDeDatos(NodoCola*&Primero,NodoCola*&Ultimo);
void Encolar(NodoCola*&Primero,NodoCola*&Ultimo,Personas Dato);
bool Punto1(NodoCola*&Primero,NodoCola*&Ultimo,int Dni);
void Desencolar(NodoCola*&Primero,NodoCola*&Ultimo,Personas &Dato);

int main()
{
    int Dni;
    bool Verificador;
    Personas P;
    NodoCola*Primero = NULL;
    NodoCola*Ultimo = NULL;

    CargaDeDatos(Primero,Ultimo);

    cout << "---------------------------------" << endl;
    cout << "INFORME dni del pasajero a buscar: ";
    cin >> Dni;

    Verificador = Punto1(Primero,Ultimo,Dni);

    if(Verificador)
    {
        cout << "Se pudo encontrar a la persona con el respectivo dni dentro de la cola" << endl;
        cout << "---------------------------------" << endl;
        cout << "Cola actualizada:" << endl;

        while(Primero != NULL)
        {
            Desencolar(Primero,Ultimo,P);

            cout << "Dni: " << P.Dni << " - " << "Nombre: " << P.Nombre  << endl;
        }

        cout << "---------------------------------" << endl;
    }
    else
    {
        cout << "No se encontro a la persona con ese dni" << endl;
    }

    return 0;
}

void CargaDeDatos(NodoCola*&Primero,NodoCola*&Ultimo)
{
    Personas P;

    cout << "INFORME dni del pasajero: ";
    cin >> P.Dni;

    while(P.Dni != 0)
    {
        cout << "INFORME nombre del pasajero: ";
        cin >> P.Nombre;

        Encolar(Primero,Ultimo,P);

        cout << "---------------------------------" << endl;
        cout << "INFORME dni del siguiente pasajero (0 para finalizar): ";
        cin >> P.Dni;
    }
}

void Encolar(NodoCola*&Primero,NodoCola*&Ultimo,Personas Dato)
{
    NodoCola*Aux = new NodoCola;
    Aux->Sig = NULL;
    Aux->Info = Dato;

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

bool Punto1(NodoCola*&Primero,NodoCola*&Ultimo,int Dni)
{
    bool Verificador = false;
    Personas P;
    Personas PAux;
    NodoCola*AuxP = NULL;
    NodoCola*AuxU = NULL;

    while(Primero != NULL)
    {
        Desencolar(Primero,Ultimo,P);

        if(P.Dni == Dni)
        {
            PAux.Dni = Dni;
            PAux.Nombre = P.Nombre;
            Verificador = true;
        }
        else
        {
            Encolar(AuxP,AuxU,P);
        }
    }

    if(Verificador)
    {
        Encolar(AuxP,AuxU,PAux);

        while(AuxP != NULL)
        {
            Desencolar(AuxP,AuxU,P);
            Encolar(Primero,Ultimo,P);
        }
    }

    return Verificador;
}

void Desencolar(NodoCola*&Primero,NodoCola*&Ultimo,Personas &Dato)
{
    NodoCola*Aux;
    Aux = Primero;
    Dato = Aux->Info;
    Primero = Aux->Sig;

    delete Aux;

    if(Primero == NULL)
    {
        Ultimo = NULL;
    }
}

//Manera de hacer el "Punto 1" sin necesidad de una Cola-Aux:

/*bool Punto1(NodoCola*&Primero,NodoCola*&Ultimo,int Dni)
{
    int DniUlt;
    bool Verificador = false;
    Personas P;
    Personas PAux;

    Desencolar(Primero,Ultimo,P);
    Encolar(Primero,Ultimo,P);

    if(P.Dni != Dni)
    {
        DniUlt = Ultimo->Info.Dni;

        while(Primero->Info.Dni != DniUlt)
        {
            Desencolar(Primero,Ultimo,P);

            if(P.Dni == Dni)
            {
                PAux = P;
                Verificador = true;
            }
            else
            {
                Encolar(Primero,Ultimo,P);
            }
        }

        Encolar(Primero,Ultimo,PAux);
    }
    else
    {
        Verificador = true;
    }

    return Verificador;
}*/
