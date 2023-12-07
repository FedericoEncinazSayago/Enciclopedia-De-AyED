/*
Una compañía que ofrece préstamos a sus clientes a pagar en 12 meses, desea obtener un listado con los códigos de clientes y los números de las cuotas adeudadas de aquellos clientes que adeuden cuotas, ordenado por código de cliente. 
Para ello cuenta con un archivo de cobranzas, sin ningún orden, con el siguiente diseño:   
Código de cliente (int) , Número de cuota (1 a 12)
*/

#include <iostream>
#include <stdio.h>

using namespace std;

struct CobranzasDelArchivo
{
    int CodDeCliente,NroDeCuota;
};

struct NodoCliente
{
    int Info;
    bool Cuotas[12];
    Nodo *Sgte;
};

void CargaDeDatos(FILE *ArchivoA,NodoCliente *&Lista);
void BuscarInsertar(NodoCliente *&Lista,int Dato,int NroDeCuota);
void MostrarListadoDeDeudores(NodoCliente *Lista);

int main()
{
    FILE *ArchivoA = fopen("Cobranzas.dat","rb");

    if(ArchivoA == NULL)
    {
        cout << "ERROR" << endl;
    }
    else
    {
        NodoCliente *Lista = NULL;

        CargaDeDatos(ArchivoA,Lista);

        cout << "Listado por codigo de cliente con aquellas cuotas que adeudan: " << endl;

        MostrarListadoDeDeudores(Lista);
    }

    return 0;
}

void CargaDeDatos(FILE *ArchivoA,NodoCliente *&Lista)
{
    CobranzasDelArchivo C;

    fread(&C,sizeof(CobranzasDelArchivo),1,ArchivoA);

    while(!feof(ArchivoA))
    {
        BuscarInsertar(Lista,C.CodDeCliente,C.NroDeCuota);
        fread(&C,sizeof(CobranzasDelArchivo),1,ArchivoA);
    }
}

void BuscarInsertar(NodoCliente *&Lista,int Dato,int NroDeCuota)
{
    NodoCliente *Aux,*Antecesor;
    Aux = Lista;

    while(Aux != NULL && Aux->Info < Dato)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    if(Aux != NULL && Dato == Aux->Info)
    {
        Aux->Cuotas[NroDeCuota - 1] = true;
    }
    else
    {
        NodoCliente *Nuevo = new NodoCliente;
        Nuevo->Info = Dato;
        Nuevo->Sgte = Aux;

        for(int i = 0; i < 11; i++)
        {
            if(NroDeCuota == i + 1)
            {
                Nuevo->Cuotas[i] = true;
            }
            else
            {
                Nuevo->Cuotas[i] = false;
            }
        }

        if(Aux != Lista)
        {
            Antecesor->Sgte = Nuevo;
        }
        else
        {
            Lista = Nuevo;
        }
    }
}

void MostrarListadoDeDeudores(NodoCliente *Lista)
{
    NodoCliente *Aux = Lista;

    while(Aux != NULL)
    {
        cout << "Codigo de cliente: " << Aux->Info << endl;

        for(int i = 0; i < 11; i++)
        {
            if(Aux->Cuotas[i] == false)
            {
                cout << "Nro de cuota: " << i + 1 << endl;
            }
        }

        cout << "---------------------------------" << endl;

        Aux = Aux->Sgte;
    }
}
