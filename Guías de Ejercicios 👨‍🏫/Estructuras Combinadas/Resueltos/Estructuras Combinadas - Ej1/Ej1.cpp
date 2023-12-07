/*En una empresa de construcción se quiere almacenar en un archivo los importes y fechas de los materiales comprados para cada una de las obras que está construcción.
Para ello se ingresa por teclado, por cada compra de materiales realizada: el código de la obra, la fecha y el importe de la compra.
Los datos son ingresados sin orden. Para cada obra se puede haber comprado materiales varias veces. Se pide generar un archivo secuencial con código de obra, fecha e importe, ordenado por código de obra y por fecha, con los datos ingresados por teclado.*/

#include <iostream>
#include <stdio.h>

using namespace std;

struct CompraDeMateriales
{
    int Fecha,Importe;
};

struct NodoSub
{
    CompraDeMateriales Info;
    NodoSub *Sgte;
};

struct Materiales
{
    int CodDeObra;
    NodoSub *SubLista;
};

struct Nodo
{
    Materiales Info;
    Nodo *Sgte;
};

struct MaterialesPorObra
{
    int Fecha,Importe,CodDeObra;
};

void CargaDeDatos(Nodo*&Lista);
void InsertaSubLista(NodoSub*&SubLista,CompraDeMateriales Dato);
void CargarArchivoA(FILE *ArchivoA,Nodo *Lista);
Nodo *BuscarInsertar(Nodo*&Lista,Materiales Dato);

int main()
{
    Nodo *Lista = NULL;
    FILE *ArchivoA = fopen("MaterialesPorObra.dat","wb");

    if(ArchivoA == NULL)
    {
        cout << "ERROR" << endl;
    }
    else
    {
        CargaDeDatos(Lista);

        CargarArchivoA(ArchivoA,Lista);

        fclose(ArchivoA);
    }

    return 0;
}

void CargaDeDatos(Nodo*&Lista)
{
    Nodo *Aux;
    Materiales M;
    CompraDeMateriales C;

    cout << "INFORME codigo de obra: ";
    cin >> M.CodDeObra;

    while(M.CodDeObra != 0)
    {
        M.SubLista = NULL;
        Aux = BuscarInsertar(Lista,M);

        cout << "INFORME fecha de compra del material (aaaa/mm/dd): ";
        cin >> C.Fecha;

        cout << "INFORME importe de la compra: ";
        cin >> C.Importe;

        InsertaSubLista(Aux->Info.SubLista,C);

        cout << "---------------------------------" << endl;
        cout << "INFORME siguiente codigo de obra (0 para finalizar): ";
        cin >> M.CodDeObra;
    }

}

void InsertaSubLista(NodoSub*&SubLista,CompraDeMateriales Dato)
{
    NodoSub *Nuevo,*Antecesor,*Aux;
    Nuevo = new NodoSub;
    Nuevo->Info = Dato;
    Aux = SubLista;

    while(Aux != NULL && Aux->Info.Fecha < Dato.Fecha)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    Nuevo->Sgte = Aux;

    if(Aux != SubLista)
    {
        Antecesor->Sgte = Nuevo;
    }
    else
    {
        SubLista = Nuevo;
    }
}

void CargarArchivoA(FILE *ArchivoA,Nodo *Lista)
{
    MaterialesPorObra M;
    Nodo *Aux = Lista;
    NodoSub *AuxSub;

    while(Aux != NULL)
    {
        AuxSub = Aux->Info.SubLista;

        while(AuxSub != NULL)
        {
            M.CodDeObra = Aux->Info.CodDeObra;
            M.Fecha = AuxSub->Info.Fecha;
            M.Importe = AuxSub->Info.Importe;

            fwrite(&M,sizeof(MaterialesPorObra),1,ArchivoA);

            AuxSub = AuxSub->Sgte;
        }

        Aux = Aux->Sgte;
    }
}

Nodo *BuscarInsertar(Nodo*&Lista,Materiales Dato)
{
    Nodo *Aux,*Antecesor;
    Aux = Lista;

    while(Aux != NULL && Aux->Info.CodDeObra < Dato.CodDeObra)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    if(Aux != NULL && Dato.CodDeObra == Aux->Info.CodDeObra)
    {
        return Aux;
    }
    else
    {
        Nodo *Nuevo = new Nodo;
        Nuevo->Info = Dato;
        Nuevo->Sgte = Aux;

        if(Aux != Lista)
        {
            Antecesor->Sgte = Nuevo;
        }
        else
        {
            Lista = Nuevo;
        }

        return Nuevo;
    }
}
