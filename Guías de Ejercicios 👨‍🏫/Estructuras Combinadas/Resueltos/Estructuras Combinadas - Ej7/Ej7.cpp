/*
En una empresa se quiere hacer una reestructuración de sus departamentos administrativos, ofreciendo la posibilidad de cambios voluntarios de departamentos  a sus empleados.
Para ello cuenta con los siguientes archivos: 
“Empleados.dat”, con un registro por cada empleado de la empresa, ordenado por  número de legajo, según el siguiente diseño: Número de legajo (int) - Apellido y nombre - Dni - Código de departamento actual.
“Vacantes.dat”, con un registro por cada departamento en el que hay vacantes a  ofrecer a los empleados, sin orden, según el siguiente diseño: Código de departamento (1 a 50) -  Cantidad de vacantes.
“Postulantes.dat”, con un registro por cada postulación realizada, cada empleado solo se pudo postular a una vacante, ordenado según se han postulado, con el siguiente diseño: Número de legajo -  Código de departamento.

Se pide desarrollar la metodología necesaria para realizar un algoritmo que permita:
a) Hacer un listado, ordenado por código de departamento, con todos los empleados postulados al mismo por orden de llegada (número de legajo, dni y apellido y nombre). 
b) Asignar los postulantes a los departamentos según el orden de llegada y la cantidad de vacantes requeridas, actualizando el archivo “Empleados.dat”
*/

#include <iostream>
#include <stdio.h>

using namespace std;

struct EmpleadoDelArchivo
{
    int NroDeLegajo,Dni,CodDeDepartamentoActual;
    char Nombre[20];
};

struct PostulanteDelArchivo
{
    int NroDeLegajo,CodDeDepartamento;
};

struct VacantesDelArchivo
{
    int CodDeDepartamento,CantDeVacantes;
};

struct NodoColaDeEspera
{
    int Info;
    NodoColaDeEspera *Sgte;
};

struct ColaDeEspera
{
    int CantDeVacantes;
    NodoColaDeEspera *Primero;
    NodoColaDeEspera *Ultimo;
};

void InicializarCola(ColaDeEspera Departamento[]);
void CargaDeVacantes(FILE *ArchivoB,ColaDeEspera Departamento[]);
void CargaDePostulantes(FILE *ArchivoC,ColaDeEspera Departamento[]);
void InsertarPorOrdenDeLlegada(NodoColaDeEspera *&Primero,NodoColaDeEspera *&Ultimo,int Dato);
void MostrarListado(FILE *ArchivoA,ColaDeEspera Departamento[]);
void Desencolar(NodoColaDeEspera *&Primero,NodoColaDeEspera *&Ultimo,int &Dato);
int BusquedaSecuencial(FILE *ArchivoA,int NroDeLegajo,EmpleadoDelArchivo &E);

int main()
{
    FILE *ArchivoA = fopen("Empleados.dat","rb+");
    FILE *ArchivoB = fopen("Vacantes.dat","rb");
    FILE *ArchivoC = fopen("Postulantes.dat","rb");

    if(ArchivoA == NULL || ArchivoB == NULL || ArchivoC == NULL)
    {
        cout << "ERROR" << endl;
    }
    else
    {
        ColaDeEspera Departamento[50];

        InicializarCola(Departamento);
        CargaDeVacantes(ArchivoB,Departamento);
        CargaDePostulantes(ArchivoC,Departamento);

        cout << "Listado ordenado por codigo de departamento con todos los empleados postulados al mismo por orden de llegada:" << endl;

        MostrarListado(ArchivoA,Departamento);
    }

    return 0;
}

void InicializarCola(ColaDeEspera Departamento[])
{
    for(int i = 0; i < 50; i++)
    {
        Departamento[i].Primero = NULL;
        Departamento[i].Ultimo = NULL;
        Departamento[i].CantDeVacantes = 0;
    }
}

void CargaDeVacantes(FILE *ArchivoB,ColaDeEspera Departamento[])
{
    VacantesDelArchivo V;

    fread(&V,sizeof(VacantesDelArchivo),1,ArchivoB);

    while(!feof(ArchivoB))
    {
        Departamento[V.CodDeDepartamento - 1].CantDeVacantes = V.CantDeVacantes;

        fread(&V,sizeof(VacantesDelArchivo),1,ArchivoB);
    }

    fclose(ArchivoB);
}

void CargaDePostulantes(FILE *ArchivoC,ColaDeEspera Departamento[])
{
    PostulanteDelArchivo P;

    fread(&P,sizeof(PostulanteDelArchivo),1,ArchivoC);

    while(!feof(ArchivoC))
    {
        InsertarPorOrdenDeLlegada(Departamento[P.CodDeDepartamento - 1].Primero,Departamento[P.CodDeDepartamento - 1].Ultimo,P.NroDeLegajo);
        fread(&P,sizeof(PostulanteDelArchivo),1,ArchivoC);
    }

    fclose(ArchivoC);
}

void InsertarPorOrdenDeLlegada(NodoColaDeEspera *&Primero,NodoColaDeEspera *&Ultimo,int Dato)
{
    NodoColaDeEspera *Aux = new NodoColaDeEspera;
    Aux->Info = Dato;
    Aux->Sgte = NULL;

    if(Ultimo != NULL)
    {
        Ultimo->Sgte = Aux;
    }
    else
    {
        Primero = Aux;
    }

    Ultimo = Aux;
}

void MostrarListado(FILE *ArchivoA,ColaDeEspera Departamento[])
{
    int NroDeLegajo,Pos;
    EmpleadoDelArchivo E;

    for(int i = 0; i < 50; i++)
    {
        cout << "Codigo de departamento: " << i + 1 << endl;

        if(Departamento[i].Primero == NULL)
        {
            cout << "NO HUBO NINGUN POSTULANTE!" << endl;
        }
        else
        {
              while(Departamento[i].Primero != NULL)
            {
                Desencolar(Departamento[i].Primero,Departamento[i].Ultimo,NroDeLegajo);

                Pos = BusquedaSecuencial(ArchivoA,NroDeLegajo,E);
                
                if(Pos != -1)
                {
                    cout << "Nro de legado del empleado: " << NroDeLegajo << " - " << "Nombre del empleado: " << E.Nombre << " - " << "Dni del empleado: " << E.Dni << endl;

                    if(Departamento[i].CantDeVacantes > 0)
                    {
                        fseek(ArchivoA,Pos*sizeof(EmpleadoDelArchivo),SEEK_SET);

                        E.CodDeDepartamentoActual = i + 1;
                        Departamento[i].CantDeVacantes--;

                        fwrite(&E,sizeof(EmpleadoDelArchivo),1,ArchivoA);
                    }
                }

                fseek(ArchivoA,0,SEEK_SET);
            }
        }
        cout << "---------------------------------" << endl;
    }
    fclose(ArchivoA);
}

void Desencolar(NodoColaDeEspera *&Primero,NodoColaDeEspera *&Ultimo,int &Dato)
{
    NodoColaDeEspera *Aux = Primero;
    Dato = Aux->Info;
    Primero = Aux->Sgte;
    delete Aux;
    if(Primero == NULL)
    {
        Ultimo = NULL;
    }
}

int BusquedaSecuencial(FILE *ArchivoA,int NroDeLegajo,EmpleadoDelArchivo &E)
{
    int i = 0;
    fread(&E,sizeof(EmpleadoDelArchivo),1,ArchivoA);
    while(!feof(ArchivoA) && E.NroDeLegajo != NroDeLegajo)
    {
        i++;

        fread(&E,sizeof(EmpleadoDelArchivo),1,ArchivoA);
    }
    if(feof(ArchivoA))
    {
        return -1;
    }
    else
    {
        return i;
    }
}
