/*
La ciudad de Buenos Aires requiere un estudio estadístico de infracciones realizadas por los vehículos en sus calles. 
Para ello cuenta con un archivo de infracciones “Infracciones.dat”, ordenado por fecha de la infracción creciente, con el siguiente diseño:  
    Patente (7 caracteres) , Fecha de Infracción (int, aammdd) , Código de infracción (int, 1 a 100)   
Se desea obtener un listado ordenado por código de infracción decreciente con las  patentes que cometieron más de una vez la misma infracción.
*/

#include <iostream>
#include <stdio.h>

using namespace std;

struct InfraccionesDelArchivo
{
    int Patente,FechaDeInfraccion,CodDeInfraccion;
};

struct Vehiculo
{
    int Patente,CantDeInfracciones;
};

struct Nodo
{
    Vehiculo Info;
    Nodo *Sgte;
};

void InicializarVectorDeInfracciones(Nodo *Infracciones[]);
void CargaDeDatos(FILE *ArchivoA,Nodo *Infracciones[]);
void BuscarInsertar(Nodo *&ListaDePatentes,Vehiculo Dato);
void MostrarListado(Nodo *Infracciones[]);

int main()
{
    FILE *ArchivoA = fopen("Infracciones.dat","rb");

    if(ArchivoA == NULL)
    {
        cout << "ERROR" << endl;
    }
    else
    {
        Nodo *Infracciones[100];

        InicializarVectorDeInfracciones(Infracciones);
        CargaDeDatos(ArchivoA,Infracciones);

        cout << "Listado ordenado por codigo de infraccion con las patentes que cometieron mas de una vez la misma infraccion: " << endl;

        MostrarListado(Infracciones);
    }

    return 0;
}

void InicializarVectorDeInfracciones(Nodo *Infracciones[])
{
    for(int i = 0; i < 100; i++)
    {
        Infracciones[i] = NULL;
    }
}

void CargaDeDatos(FILE *ArchivoA,Nodo *Infracciones[])
{
    InfraccionesDelArchivo I;
    Vehiculo V;

    fread(&I,sizeof(InfraccionesDelArchivo),1,ArchivoA);

    while(!feof(ArchivoA))
    {
        V.Patente = I.Patente;
        V.CantDeInfracciones = 1;

        BuscarInsertar(Infracciones[I.CodDeInfraccion - 1],V);
        fread(&I,sizeof(InfraccionesDelArchivo),1,ArchivoA);
    }
}

void BuscarInsertar(Nodo *&ListaDePatentes,Vehiculo Dato)
{
    Nodo *Aux,*Antecesor;
    Aux = ListaDePatentes;

    while(Aux != NULL && Aux->Info.Patente < Dato.Patente)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    if(Aux != NULL && Dato.Patente == Aux->Info.Patente)
    {
        Aux->Info.CantDeInfracciones++;
    }
    else
    {
        Nodo *Nuevo = new Nodo;
        Nuevo->Info = Dato;
        Nuevo->Sgte = Aux;

        if(Aux != ListaDePatentes)
        {
            Antecesor->Sgte = Nuevo;
        }
        else
        {
            ListaDePatentes = Nuevo;
        }
    }
}

void MostrarListado(Nodo *Infracciones[])
{
    Nodo *Aux;

    for(int i = 100; i > 0; i--)
    {
        cout << "Codigo de infraccion: " << i << endl;

        Aux = Infracciones[i - 1];

        if(Aux == NULL)
        {
            cout << "LISTADO VACIO!" << endl;
        }
        else
        {
            while(Aux != NULL)
            {
                if(Aux->Info.CantDeInfracciones >= 2)
                {
                    cout << "Nro de patente: " << Aux->Info.Patente << endl;
                }

                Aux = Aux->Sgte;
            }
        }

        cout << "---------------------------------" << endl;
    }
}
