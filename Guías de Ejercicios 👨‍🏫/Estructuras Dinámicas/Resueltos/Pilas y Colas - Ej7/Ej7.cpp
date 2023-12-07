/*En una oficina de Aeroparque una secretaria atiende las colas de espera para Montevideo, Punta del Este y Mar del Plata. Tiene una cola de espera para cada localidad, y en ella registra nombre y apellido del pasajero y número de documento. 
- Desarrolle una función que, dados los datos del pasajero y el lugar de destino, lo incluya en la cola de espera correspondiente.
- Desarrolle una función que, dado el destino y la cantidad de asientos libres de un avión, retire de la cola de espera a aquellas personas que ahora pueden viajar, e informe los datos. */

#include <iostream>
#include <string.h>

using namespace std;

struct Pasajeros
{
    int DNI;
    string Nombre;
};

struct NodoCola
{
    Pasajeros Info;
    NodoCola*Sig;
};

void CargaDeDatos(NodoCola*&PrimeroMar,NodoCola*&UltimoMar,NodoCola*&PrimeroPunta,NodoCola*&UltimoPunta,NodoCola*&PrimeroMonte,NodoCola*&UltimoMonte);
void Encolar(NodoCola*&Primero,NodoCola*&Ultimo,Pasajeros Dato);
void AsientoLibresPorDestino (NodoCola*&PrimeroMar,NodoCola*&UltimoMar,NodoCola*&PrimeroPunta,NodoCola*&UltimoPunta,NodoCola*&PrimeroMonte,NodoCola*&UltimoMonte,string Destino,int Nro);
void Desencolar(NodoCola*&Primero,NodoCola*&Ultimo,Pasajeros &Dato);

int main()
{
    int Nro;
    string Destino;
    NodoCola*PrimeroMar = NULL,NodoCola*UltimoMar = NULL;
    NodoCola*PrimeroPunta = NULL,NodoCola*UltimoPunta = NULL;
    NodoCola*PrimerMonte = NULL,NodoCola*UltimoMonte = NULL;

    CargaDeDatos(PrimeroMar,UltimoMar,PrimeroPunta,UltimoPunta,PrimerMonte,UltimoMonte);

    cout << "---------------------------------" << endl;
    cout << "Seleccione un destino (MarDelPlata,PuntaDelEste,Montevideo): ";
    cin >> Destino;

    cout << "INFORME cantidad de asientos libres para el destino: ";
    cin >>  Nro;

    cout << "---------------------------------" << endl;
    cout << "Listado de los pasajeros que viajaran: " << endl;

    AsientoLibresPorDestino(PrimeroMar,UltimoMar,PrimeroPunta,UltimoPunta,PrimerMonte,UltimoMonte,Destino,Nro);

    cout << "---------------------------------" << endl;

    return 0;
}

void CargaDeDatos(NodoCola*&PrimeroMar,NodoCola*&UltimoMar,NodoCola*&PrimeroPunta,NodoCola*&UltimoPunta,NodoCola*&PrimeroMonte,NodoCola*&UltimoMonte)
{
    string Destino;
    Pasajeros P;

    cout << "INFORME dni del pasajero: ";
    cin >> P.DNI;

    while(P.DNI != 0)
    {
        cout << "INFORME nombre del pasajero: ";
        cin >> P.Nombre;

        cout << "INFORME lugar de destino (MarDelPlata, PuntaDelEste, Montevideo): ";
        cin >> Destino;

        if(Destino == "MarDelPlata")
        {
            Encolar(PrimeroMar,UltimoMar,P);
        }
        else
        {
            if(Destino == "PuntaDelEste")
            {
                Encolar(PrimeroPunta,UltimoPunta,P);
            }
            else
            {
                if(Destino == "Montevideo")
                {
                    Encolar(PrimeroMonte,UltimoMonte,P);
                }
                else
                {
                    cout << "Destino no encontrado" << endl;
                }
            }
        }

        cout << "---------------------------------" << endl;
        cout << "INFORME dni del siguiente pasajero: ";
        cin >> P.DNI;
    }
}

void Encolar(NodoCola*&Primero,NodoCola*&Ultimo,Pasajeros Dato)
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

void AsientoLibresPorDestino(NodoCola*&PrimeroMar,NodoCola*&UltimoMar,NodoCola*&PrimeroPunta,NodoCola*&UltimoPunta,NodoCola*&PrimeroMonte,NodoCola*&UltimoMonte,string Destino,int Nro)
{
    int i = 0;
    Pasajeros P;

    if(Destino == "MarDelPlata")
    {
        while(PrimeroMar != NULL && i < Nro)
        {
            Desencolar(PrimeroMar,UltimoMar,P);

            cout << "Nro de dni: " << P.DNI << " - " << "Nombre del pasajero: " << P.Nombre << " - " << "Destino del pasajero: " << Destino << endl;

            i++;
        }
    }
    else
    {
        if(Destino == "PuntaDelEste")
        {
            while(PrimeroPunta != NULL && i < Nro)
            {
                Desencolar(PrimeroPunta,UltimoPunta,P);

                cout << "Nro de dni: " << P.DNI << " - " << "Nombre del pasajero: " << P.Nombre << " - " << "Destino del pasajero: " << Destino << endl;

                i++;
            }
        }
        else
        {
            if(Destino == "Montevideo")
            {
                while(PrimeroMonte != NULL && i < Nro)
                {
                    Desencolar(PrimeroMonte,UltimoMonte,P);

                    cout << "Nro de dni: " << P.DNI << " - " << "Nombre del pasajero: " << P.Nombre << " - " << "Destino del pasajero: " << Destino << endl;

                    i++;
                }
            }
            else
            {
                cout << "Destino no encontrado" << endl;
            }
        }
    }
}

void Desencolar(NodoCola*&Primero,NodoCola*&Ultimo,Pasajeros &Dato)
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

