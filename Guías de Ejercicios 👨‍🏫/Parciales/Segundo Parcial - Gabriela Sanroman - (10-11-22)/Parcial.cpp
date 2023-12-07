#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct DatosDelArchivoA
{
    int CodDeCredito,CantMaxDeInscriptos;
    char Descripcion[30];
};

struct DatosDelArchivoB
{
    int Dni,CodDeCreditoSolicitado,IngresoMensual;
    char Apellido[30],Nombre[30];
};

struct Inscriptos
{
    int Dni,IngresoMensual;
    char Apellido[30],Nombre[30];
};

struct NodoInscriptos
{
    Inscriptos Info;
    NodoInscriptos *Sgte;
};

struct Credito
{
    int CodDeCredito,CantMaxDeInscriptos;
    NodoInscriptos *ListaPorInscriptos;
};

struct NodoCredito
{
    Credito Info;
    NodoCredito *Sgte;
};

void ArmaEstructuras(FILE *ArchivoA,FILE *ArchivoB);
void CargaDeCreditos(FILE *ArchivoA,NodoCredito *&ListaPorCredito);
void InsertarPorCreditos(NodoCredito *&ListaPorCredito,Credito Dato);
void CargaDeInscriptos(FILE *ArchivoB,NodoCredito *&ListaPorCredito);
void InsertarInscriptos(NodoInscriptos *&ListaPorInscriptos,Inscriptos Dato);
void MostrarListado(NodoCredito *ListaPorCredito);
NodoCredito *BusquedaDeCredito(NodoCredito *ListaPorCredito,int CodDeCreditoSolicitado);

int main()
{
    FILE *ArchivoA = fopen("Creditos.dat","rb");
    FILE *ArchivoB = fopen("Inscriptos.dat","rb");

    if(ArchivoA == NULL || ArchivoB == NULL)
    {
        cout << "ERROR" << endl;
    }
    else
    {
        ArmaEstructuras(ArchivoA,ArchivoB);
    }

    return 0;
}

void ArmaEstructuras(FILE *ArchivoA,FILE *ArchivoB)
{
    NodoCredito *ListaPorCredito = NULL;

    CargaDeCreditos(ArchivoA,ListaPorCredito);
    CargaDeInscriptos(ArchivoB,ListaPorCredito);
    MostrarListado(ListaPorCredito);
}

void CargaDeCreditos(FILE *ArchivoA,NodoCredito *&ListaPorCredito)
{
    DatosDelArchivoA D;
    Credito C;

    fread(&D,sizeof(DatosDelArchivoA),1,ArchivoA);

    while(!feof(ArchivoA))
    {
        C.CodDeCredito = D.CodDeCredito;
        C.CantMaxDeInscriptos = D.CantMaxDeInscriptos;
        C.ListaPorInscriptos = NULL;

        InsertarPorCreditos(ListaPorCredito,C);
    }
}

void InsertarPorCreditos(NodoCredito *&ListaPorCredito,Credito Dato)
{
    NodoCredito *Nuevo,*Antecesor,*Aux;
    Nuevo = new NodoCredito;
    Nuevo->Info = Dato;
    Aux = ListaPorCredito;

    while(Aux != NULL && Aux->Info.CodDeCredito < Dato.CodDeCredito)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    Nuevo->Sgte = Aux;

    if(Aux != ListaPorCredito)
    {
        Antecesor->Sgte = Nuevo;
    }
    else
    {
        ListaPorCredito = Nuevo;
    }
}

void CargaDeInscriptos(FILE *ArchivoB,NodoCredito *&ListaPorCredito)
{
    NodoCredito *Aux;
    DatosDelArchivoB D;
    Inscriptos I;

    fread(&D,sizeof(DatosDelArchivoB),1,ArchivoB);

    while(!feof(ArchivoB))
    {
        Aux = BusquedaDeCredito(ListaPorCredito,D.CodDeCreditoSolicitado);

        if(Aux != NULL)
        {
            I.IngresoMensual = D.IngresoMensual;
            I.Dni = D.Dni;

            strcpy(I.Apellido,D.Apellido);
            strcpy(I.Nombre,D.Nombre);
            InsertarInscriptos(Aux->Info.ListaPorInscriptos,I);
        }

        fread(&D,sizeof(DatosDelArchivoB),1,ArchivoB);
    }
}

void InsertarInscriptos(NodoInscriptos *&ListaPorInscriptos,Inscriptos Dato)
{
    NodoInscriptos *Nuevo,*Antecesor,*Aux;
    Nuevo = new NodoInscriptos;
    Nuevo->Info = Dato;
    Aux = ListaPorInscriptos;

    while(Aux != NULL && Aux->Info.IngresoMensual > Dato.IngresoMensual)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    Nuevo->Sgte = Aux;

    if(Aux != ListaPorInscriptos)
    {
        Antecesor->Sgte = Nuevo;
    }
    else
    {
        ListaPorInscriptos = Nuevo;
    }
}

void MostrarListado(NodoCredito *ListaPorCredito)
{
    int i = 0;
    NodoCredito *Aux = ListaPorCredito;
    NodoInscriptos *AuxInscriptos;

    while(Aux != NULL)
    {
        cout << "Codigo de credito: " << Aux->Info.CodDeCredito << endl;

        AuxInscriptos = Aux->Info.ListaPorInscriptos;

        if(AuxInscriptos == NULL)
        {
            cout << "NO HUBO NINGUN INSCRIPTO!" << endl;
        }
        else
        {
            while(AuxInscriptos != NULL && i < Aux->Info.CantMaxDeInscriptos)
            {
                cout << "Nombre del inscripto: " << AuxInscriptos->Info.Nombre << " - " << "Apellido del inscripto: " << AuxInscriptos->Info.Apellido << " - " << "Dni del inscripto: " << AuxInscriptos->Info.Dni << endl;

                i++;
                AuxInscriptos = AuxInscriptos->Sgte;
            }
        }

        cout << "---------------------------------" << endl;

        i = 0;
        Aux = Aux->Sgte;
    }
}

NodoCredito *BusquedaDeCredito(NodoCredito *ListaPorCredito,int CodDeCreditoSolicitado)
{
    NodoCredito *Aux;
    Aux = ListaPorCredito;

    while(Aux != NULL && Aux->Info.CodDeCredito < CodDeCreditoSolicitado)
    {
        Aux = Aux->Sgte;
    }

    if(Aux == NULL || Aux->Info.CodDeCredito != CodDeCreditoSolicitado)
    {
        return NULL;
    }
    else
    {
        return Aux;
    }
}

