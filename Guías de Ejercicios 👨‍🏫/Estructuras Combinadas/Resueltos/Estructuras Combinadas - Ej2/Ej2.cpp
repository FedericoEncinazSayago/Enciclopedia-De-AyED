/*Dado el archivo VENTAS.DAT, ordenado por número de factura,  con la siguiente estructura de registro:  Número de factura (int) , Código de vendedor (int) , Importe (float) 
a) Imprima un listado ordenado por código de vendedor, con código de vendedor y el detalle de cada venta, ordenadas de mayor a menor por importe. 
b) Genere el archivo “VentasVendedor.dat” ordenado por código de vendedor, con código de vendedor y el importe total de ventas*/

#include <iostream>
#include <stdio.h>

using namespace std;

struct VentasDelArchivo
{
    int NroDeFactura,CodDeVendedor;
    float Importe;
};

struct Importes
{
    int NroDeFactura,Importe;
};

struct NodoSub
{
    Importes Info;
    NodoSub *Sgte;
};

struct Ventas
{
    int CodDeVendedor;
    NodoSub *SubLista;
};

struct Nodo
{
    Ventas Info;
    Nodo *Sgte;
};

struct VentasPorVendedor
{
    int CodDeVendedor,ImporteTotal;
};

void CargaDeDatos(FILE *ArchivoA,Nodo *&Lista);
void InsertaSubLista(NodoSub*&SubLista,Importes Dato);
void MostrarListado(FILE *ArchivoB,Nodo *Lista);
Nodo *BuscarInsertar(Nodo*&Lista,Ventas Dato);

int main()
{
    Nodo *Lista = NULL;
    FILE *ArchivoA = fopen("Ventas.dat","rb");
    FILE *ArchivoB = fopen("VentasVendedor.dat","wb");

    if(ArchivoA == NULL || ArchivoB == NULL)
    {
        cout << "ERROR" << endl;
    }
    else
    {
        CargaDeDatos(ArchivoA,Lista);

        cout << "Listado ordenado por codigo de vendedor y detalle de cada venta:" << endl;

        MostrarListado(ArchivoB,Lista);

        cout << "---------------------------------" << endl;
    }
    return 0;
}

void CargaDeDatos(FILE *ArchivoA,Nodo *&Lista)
{
    Nodo *Aux;
    Ventas AuxV;
    Importes I;
    VentasDelArchivo V;

    fread(&V,sizeof(VentasDelArchivo),1,ArchivoA);

    while(!feof(ArchivoA))
    {
        AuxV.CodDeVendedor = V.CodDeVendedor;
        I.NroDeFactura = V.NroDeFactura;
        I.Importe = V.Importe;
        AuxV.SubLista = NULL;
        Aux = BuscarInsertar(Lista,AuxV);

        InsertaSubLista(Aux->Info.SubLista,I);

        fread(&V,sizeof(VentasDelArchivo),1,ArchivoA);
    }
}

void InsertaSubLista(NodoSub*&SubLista,Importes Dato)
{
    NodoSub *Nuevo,*Antecesor,*Aux;
    Nuevo = new NodoSub;
    Nuevo->Info = Dato;
    Aux = SubLista;

    while(Aux != NULL && Aux->Info.Importe > Dato.Importe)
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

void MostrarListado(FILE *ArchivoB,Nodo *Lista)
{
    int ImporteTotal = 0;
    Nodo *Aux = Lista;
    NodoSub *AuxSub;
    VentasDelArchivo V;
    VentasPorVendedor AuxV;

    while(Aux != NULL)
    {
        AuxSub = Aux->Info.SubLista;

        while(AuxSub != NULL)
        {
            cout << "Codigo de vendedor: " << Aux->Info.CodDeVendedor << " - " << "Nro de factura: " <<AuxSub->Info.NroDeFactura << " - " << "Importe: " << "$" << AuxSub->Info.Importe << endl;

            ImporteTotal = ImporteTotal + AuxSub->Info.Importe;
            AuxSub = AuxSub->Sgte;
        }

        AuxV.CodDeVendedor = Aux->Info.CodDeVendedor;
        AuxV.ImporteTotal = ImporteTotal;

        fwrite(&AuxV,sizeof(VentasPorVendedor),1,ArchivoB);

        ImporteTotal = 0;
        Aux = Aux->Sgte;
    }
}

Nodo *BuscarInsertar(Nodo*&Lista,Ventas Dato)
{
    Nodo *Aux,*Antecesor;
    Aux = Lista;

    while(Aux != NULL && Aux->Info.CodDeVendedor < Dato.CodDeVendedor)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    if(Aux != NULL && Dato.CodDeVendedor == Aux->Info.CodDeVendedor)
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
