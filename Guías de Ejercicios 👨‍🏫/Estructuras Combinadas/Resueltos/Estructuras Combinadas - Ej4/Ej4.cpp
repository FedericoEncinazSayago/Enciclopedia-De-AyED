/*
En un club deportivo barrial se quiere hacer un programa para obtener datos estadísticos de los atletas que compitieron en el año 2019 en las 15 actividades deportivas que se practican en el mismo. 
Se tiene el archivo “Competidores.dat”, con cada una de las participaciones de los atletas competencias, sin orden, donde cada registro tiene el siguiente formato:  Código de actividad (1..15) , Número de socio del atleta , Fecha de la competencia (struct dia, mes, anio) , Resultado (int)

Se pide: 
a) Informar por cada actividad, por cada mes, cada uno de los atletas que compitieron y el resultado obtenido, ordenado por código de actividad, por mes y por número de socio.
b) Informar por cada mes del año el total de atletas que compitieron en cada actividad.
c) Informar en qué actividad deportiva hubo más de un primer puesto.
*/

#include <iostream>
#include <stdio.h>

using namespace std;

struct FechaDeCompetencia
{
    int Dia,Mes,Anio;
};

struct Competidores
{
    int CodDeActividad,NroDeSocio,Resultado;
    FechaDeCompetencia Info;
};

struct Socios
{
    int NroDeSocio,Resultado;
};

struct NodoTer
{
    Socios Info;
    NodoTer *Sgte;
};

struct Meses
{
    int Mes;
    NodoTer *ListaDeSocios;
};

struct NodoSub
{
    Meses Info;
    NodoSub *Sgte;
};

struct Actividades
{
    int CodDeActividad;
    NodoSub *ListaDeMeses;
};

struct Nodo
{
    Actividades Info;
    Nodo *Sgte;
};

void InicializarMatriz(int ActividadesPorMeses[][12]);
void InicializarVector(int PrimerPuesto[]);
void CargaDeDatos(FILE*ArchivoA,Nodo*&Lista,int ActividadesPorMeses[][12],int PrimerPuesto[]);
void InsertarSocios(NodoTer*&ListaDeSocios,Socios Dato);
void MostrarListado(Nodo*Lista);
void MostrarCantDeParticipantes(int ActividadesPorMeses[][12]);
void MostrarMayor(int PrimerPuesto[]);
Nodo *BuscarInsertar(Nodo*&Lista,Actividades Dato);
NodoSub *BuscarInsertarMeses(NodoSub*&ListaDeMeses,Meses Dato);

int main()
{
    int ActividadesPorMeses[15][12];
    int PrimerPuesto[15];
    Nodo *Lista = NULL;
    FILE *ArchivoA = fopen("Competidores.dat","rb");

    if(ArchivoA == NULL)
    {
        cout << "ERROR" << endl;
    }
    else
    {
        InicializarMatriz(ActividadesPorMeses);

        InicializarVector(PrimerPuesto);

        CargaDeDatos(ArchivoA,Lista,ActividadesPorMeses,PrimerPuesto);

        fclose(ArchivoA);

        cout << "Listado por actividad, ordenado por mes y numero de socio: " << endl;

        MostrarListado(Lista);

        cout << "---------------------------------" << endl;
        cout << "Listado por actividad que informa la cantidad el total de atletas que compitieron en cada actividad: " << endl;

        MostrarCantDeParticipantes(ActividadesPorMeses);

        cout << "Listado que informa en que actividad hubo mas de un primer puesto: " << endl;

        MostrarMayorCantDePrimerPuesto(PrimerPuesto);

        cout << "---------------------------------" << endl;
    }

    return 0;
}

void InicializarMatriz(int ActividadesPorMeses[][12])
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            ActividadesPorMeses[i][j] = 0;
        }
    }
}

void InicializarVector(int PrimerPuesto[])
{
    for(int i = 0;i < 15; i++)
    {
        PrimerPuesto[i] = 0;
    }
}

void CargaDeDatos(FILE*ArchivoA,Nodo*&Lista,int ActividadesPorMeses[][12],int PrimerPuesto[])
{
    Nodo *Aux;
    NodoSub *AuxSub;
    Actividades A;
    Competidores C;
    Meses M;
    Socios S;

    fread(&C,sizeof(Competidores),1,ArchivoA);

    while(!feof(ArchivoA))
    {

        A.CodDeActividad = C.CodDeActividad;
        A.ListaDeMeses = NULL;
        M.Mes = C.Info.Mes;
        M.ListaDeSocios = NULL;
        S.NroDeSocio = C.NroDeSocio;
        S.Resultado = C.Resultado;

        Aux = BuscarInsertar(Lista,A);

        AuxSub = BuscarInsertarMeses(Aux->Info.ListaDeMeses,M);

        InsertarSocios(AuxSub->Info.ListaDeSocios,S);

        ActividadesPorMeses[C.CodDeActividad - 1][C.Info.Mes - 1] = ActividadesPorMeses[C.CodDeActividad - 1][C.Info.Mes - 1] + 1;

        if(C.Resultado == 1)
        {
            PrimerPuesto[C.CodDeActividad - 1] = PrimerPuesto[C.CodDeActividad - 1] + 1;
        }

        fread(&C,sizeof(Competidores),1,ArchivoA);
    }
}

void InsertarSocios(NodoTer*&ListaDeSocios,Socios Dato)
{
    NodoTer *Nuevo,*Antecesor,*Aux;
    Nuevo = new NodoTer;
    Nuevo->Info = Dato;
    Aux = ListaDeSocios;

    while(Aux != NULL && Aux->Info.NroDeSocio < Dato.NroDeSocio)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    Nuevo->Sgte = Aux;

    if(Aux != ListaDeSocios)
    {
        Antecesor->Sgte = Nuevo;
    }
    else
    {
        ListaDeSocios = Nuevo;
    }
}

void MostrarListado(Nodo*Lista)
{
    Nodo *Aux = Lista;
    NodoSub *AuxSub;
    NodoTer *AuxTer;

    while(Aux != NULL)
    {
        cout << "Codigo de actividad: " << Aux->Info.CodDeActividad << endl;

        AuxSub = Aux->Info.ListaDeMeses;

        while(AuxSub != NULL)
        {

            cout << "Mes: " << AuxSub->Info.Mes << endl;

            AuxTer = AuxSub->Info.ListaDeSocios;

            while(AuxTer != NULL)
            {
                cout << "Nro de socio: " << AuxTer->Info.NroDeSocio << " - " << "Resultado: " << AuxTer->Info.Resultado << endl;

                AuxTer = AuxTer->Sgte;
            }

            AuxSub = AuxSub->Sgte;
        }

        cout << "---------------------------------" << endl;

        Aux = Aux->Sgte;
    }
}

void MostrarCantDeParticipantes(int ActividadesPorMeses[][12])
{
    for(int i = 0; i < 15; i++)
    {
        cout << "Actividad " << i + 1 << endl;

        for(int j = 0; j < 12; j++)
        {
            cout << "Mes: " << j + 1 << " - "  << "Cantidad de participantes: " << ActividadesPorMeses[i][j] << endl;
        }

        cout << "---------------------------------" << endl;
    }
}

void MostrarMayor(int PrimerPuesto[])
{
    int Mayor,Actividad;

    for(int i = 0; i < 15; i++)
    {
        if(i == 0 || PrimerPuesto[i] > Mayor)
        {
            Mayor = PrimerPuesto[i];
            Actividad = i;
        }
    }

    cout << "Actividad: " << Actividad + 1 << " - " << "Cant de participantes: " << Mayor << endl;
}

Nodo *BuscarInsertar(Nodo*&Lista,Actividades Dato)
{
    Nodo *Aux,*Antecesor;
    Aux = Lista;

    while(Aux != NULL && Aux->Info.CodDeActividad < Dato.CodDeActividad)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    if(Aux != NULL && Dato.CodDeActividad == Aux->Info.CodDeActividad)
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

NodoSub *BuscarInsertarMeses(NodoSub*&ListaDeMeses,Meses Dato)
{
    NodoSub *Aux,*Antecesor;
    Aux = ListaDeMeses;

    while(Aux != NULL && Aux->Info.Mes < Dato.Mes)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    if(Aux != NULL && Dato.Mes == Aux->Info.Mes)
    {
        return Aux;
    }
    else
    {
        NodoSub *Nuevo = new NodoSub;
        Nuevo->Info = Dato;
        Nuevo->Sgte = Aux;

        if(Aux != ListaDeMeses)
        {
            Antecesor->Sgte = Nuevo;
        }
        else
        {
            ListaDeMeses = Nuevo;
        }

        return Nuevo;
    }
}

