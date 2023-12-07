/*
Una biblioteca necesita un programa que efectúe las altas en el archivo maestro de libros. 
Para ello cuenta con: a) LIBROS.dat, archivo maestro de libros ordenado por código de libro, con  un registro por cada libro, con el siguiente diseño:
Código de libro (int)  Título del libro (30 caracteres)  Apellido del autor (15 caracteres)  Nacionalidad (int)  Cantidad de ejemplares   

b) NOVEDADES.dat, archivo con los libros a dar de alta  sin ningún orden, con el mismo diseño del archivo maestro.  

Se pide realizar la metodología necesaria para que el programa:  
1) Genere un nuevo archivo LIBROSACT.dat, con el mismo diseño y orden que el maestro y con las altas incorporadas.  
2) Emitir el siguiente listado, agrupado por nacionalidad y ordenado ascendente por cantidad total de autores:                 
Nacionalidad................................... Cantidad Total de autores: 999  
Apellido del Autor:           
Cantidad total de títulos.......................99 
*/

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct Libros
{
    int CodDeLibro,Nacionalidad,CantDeEjemplares;
    char TituloDelLibro[30],ApellidoDelAutor[30];
};

struct NodoLibro
{
    Libros Info;
    NodoLibro *Sgte;
};

struct Autor
{
    int CantTotalDeTitulos;
    char ApellidoDelAutor[30];
};

struct NodoAutor
{
    Autor Info;
    NodoAutor *Sgte;
};

struct Nacionalidad
{
    int NroDeNacionalidad,CantTotalDeAutores;
    NodoAutor *ListaDeAutores;
};

struct NodoNacionalidad
{
    Nacionalidad Info;
    NodoNacionalidad *Sgte;
};

void CargaDeEjemplares(FILE *ArchivoB,NodoLibro *&Lista);
void InsertarLibro(NodoLibro *&Lista,Libros Dato);
void Apareo(FILE *ArchivoA,FILE *ArchivoC,NodoLibro *ListaDelibros,NodoNacionalidad *&ListaPorNacionalidad);
void BuscarInsertarAutor(NodoNacionalidad *&ListaPorNacionalidad,NodoAutor *&ListaDeAutores,Autor Dato);
void OrdenarPorCantDeAutores(NodoNacionalidad *&ListaPorNacionalidad);
void InsertarLogico(NodoNacionalidad *&ListaOrdenada,NodoNacionalidad *Nuevo);
void MostrarListado(NodoNacionalidad *ListaPorNacionalidad);
NodoNacionalidad *BuscarInsertarNacionalidad(NodoNacionalidad *&ListaPorNacionalidad,Nacionalidad Dato);

int main()
{
    FILE *ArchivoA = fopen("Libros.dat","rb");
    FILE *ArchivoB = fopen("Novedades.dat","rb");

    if(ArchivoA == NULL || ArchivoB == NULL)
    {
        cout << "ERROR" << endl;
    }
    else
    {
        FILE *ArchivoC = fopen("LibrosAct.dat","wb");

        if(ArchivoC != NULL)
        {
            NodoLibro *Lista = NULL;
            NodoNacionalidad *ListaPorNacionalidad = NULL;

            CargaDeEjemplares(ArchivoB,Lista);
            Apareo(ArchivoA,ArchivoC,Lista,ListaPorNacionalidad);
            OrdenarPorCantDeAutores(ListaPorNacionalidad);
            MostrarListado(ListaPorNacionalidad);
        }
    }

    return 0;
}

void CargaDeEjemplares(FILE *ArchivoB,NodoLibro *&Lista)
{
    Libros L;

    fread(&L,sizeof(Libros),1,ArchivoB);

    while(!feof(ArchivoB))
    {
        InsertarLibro(Lista,L);
        fread(&L,sizeof(Libros),1,ArchivoB);
    }

    fclose(ArchivoB);
}

void InsertarLibro(NodoLibro *&Lista,Libros Dato)
{
    NodoLibro *Nuevo,*Antecesor,*Aux;
    Nuevo = new NodoLibro;
    Nuevo->Info = Dato;
    Aux = Lista;

    while(Aux != NULL && Aux->Info.CodDeLibro < Dato.CodDeLibro)
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

void Apareo(FILE *ArchivoA,FILE *ArchivoC,NodoLibro *ListaDelibros,NodoNacionalidad *&ListaPorNacionalidad)
{
    NodoLibro *Aux = ListaDelibros;
    NodoNacionalidad *AuxN;
    Libros L;
    Nacionalidad N;
    Autor A;

    fread(&L,sizeof(Libros),1,ArchivoA);

    while(!feof(ArchivoA) && Aux != NULL)
    {
        if(L.CodDeLibro < Aux->Info.CodDeLibro)
        {
            N.NroDeNacionalidad = L.Nacionalidad;

            strcpy(A.ApellidoDelAutor,L.ApellidoDelAutor);
            fwrite(&L,sizeof(Libros),1,ArchivoC);
            fread(&L,sizeof(Libros),1,ArchivoA);
        }
        else
        {
            if(L.CodDeLibro == Aux->Info.CodDeLibro)
            {
                N.NroDeNacionalidad = L.Nacionalidad;
                Aux->Info.CantDeEjemplares += L.CantDeEjemplares;

                strcpy(A.ApellidoDelAutor,Aux->Info.ApellidoDelAutor);
                fwrite(&Aux->Info,sizeof(Libros),1,ArchivoC);
                fread(&L,sizeof(Libros),1,ArchivoA);

                Aux = Aux->Sgte;
            }
            else
            {
                N.NroDeNacionalidad = Aux->Info.Nacionalidad;

                strcpy(A.ApellidoDelAutor,Aux->Info.ApellidoDelAutor);
                fwrite(&Aux->Info,sizeof(Libros),1,ArchivoC);

                Aux = Aux->Sgte;
            }
        }

        N.ListaDeAutores = NULL;
        AuxN = BuscarInsertarNacionalidad(ListaPorNacionalidad,N);

        BuscarInsertarAutor(AuxN,AuxN->Info.ListaDeAutores,A);
    }

    while(!feof(ArchivoA))
    {

        N.NroDeNacionalidad = L.Nacionalidad;
        N.ListaDeAutores = NULL;

        strcpy(A.ApellidoDelAutor,L.ApellidoDelAutor);

        AuxN = BuscarInsertarNacionalidad(ListaPorNacionalidad,N);

        BuscarInsertarAutor(AuxN,AuxN->Info.ListaDeAutores,A);
        fwrite(&L,sizeof(Libros),1,ArchivoC);
        fread(&L,sizeof(Libros),1,ArchivoA);
    }

    fclose(ArchivoA);

    while(Aux != NULL)
    {
        N.NroDeNacionalidad = Aux->Info.Nacionalidad;
        N.ListaDeAutores = NULL;

        strcpy(A.ApellidoDelAutor,Aux->Info.ApellidoDelAutor);

        AuxN = BuscarInsertarNacionalidad(ListaPorNacionalidad,N);

        BuscarInsertarAutor(AuxN,AuxN->Info.ListaDeAutores,A);
        fwrite(&Aux->Info,sizeof(Libros),1,ArchivoC);

        Aux = Aux->Sgte;
    }

    fclose(ArchivoC);
}


void BuscarInsertarAutor(NodoNacionalidad *&ListaPorNacionalidad,NodoAutor *&ListaDeAutores,Autor Dato)
{
    NodoAutor *Aux,*Antecesor;
    Aux = ListaDeAutores;

    while(Aux != NULL && strcmpi(Aux->Info.ApellidoDelAutor,Dato.ApellidoDelAutor) < 0)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    if(Aux != NULL && strcmpi(Aux->Info.ApellidoDelAutor,Dato.ApellidoDelAutor) == 0)
    {
        Aux->Info.CantTotalDeTitulos++;
    }
    else
    {
        NodoAutor *Nuevo = new NodoAutor;
        ListaPorNacionalidad->Info.CantTotalDeAutores += 1;
        Dato.CantTotalDeTitulos = 1;
        Nuevo->Info = Dato;
        Nuevo->Sgte = Aux;

        if(Aux != ListaDeAutores)
        {
            Antecesor->Sgte = Nuevo;
        }
        else
        {
            ListaDeAutores = Nuevo;
        }
    }
}

void OrdenarPorCantDeAutores(NodoNacionalidad *&ListaPorNacionalidad)
{
    NodoNacionalidad *ListaOrdenada = NULL;
    NodoNacionalidad *Aux;

    while(ListaPorNacionalidad != NULL)
    {
        Aux = ListaPorNacionalidad;
        ListaPorNacionalidad = ListaPorNacionalidad->Sgte;

        InsertarLogico(ListaOrdenada,Aux);
    }

    ListaPorNacionalidad = ListaOrdenada;
}

void InsertarLogico(NodoNacionalidad *&ListaOrdenada,NodoNacionalidad *Nuevo)
{
    NodoNacionalidad *Aux,*Antecesor;
    Aux = ListaOrdenada;

    while(ListaOrdenada != NULL && Aux->Info.CantTotalDeAutores < Aux->Info.CantTotalDeAutores)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    Nuevo->Sgte = Aux;

    if(Aux != ListaOrdenada)
    {
        Antecesor->Sgte = Nuevo;
    }
    else
    {
        ListaOrdenada = Nuevo;
    }
}

void MostrarListado(NodoNacionalidad *ListaPorNacionalidad)
{
    NodoNacionalidad *Aux = ListaPorNacionalidad;
    NodoAutor *AuxAutor;

    while(Aux != NULL)
    {
        cout << "Nro de nacionalidad: " << Aux->Info.NroDeNacionalidad << " - " <<"Cantidad total de autores: " << Aux->Info.CantTotalDeAutores << endl;

        AuxAutor = Aux->Info.ListaDeAutores;

        if(AuxAutor == NULL)
        {
            cout << "SIN AUTORES!" << endl;
        }
        else
        {
            while(AuxAutor != NULL)
            {
                cout << "Apellido del Autor: " << AuxAutor->Info.ApellidoDelAutor << " - " << "Cantidad de total de titulos: " << AuxAutor->Info.CantTotalDeTitulos << endl;

                AuxAutor = AuxAutor->Sgte;
            }
        }

        cout << "---------------------------------" << endl;

        Aux = Aux->Sgte;
    }
}

NodoNacionalidad *BuscarInsertarNacionalidad(NodoNacionalidad *&ListaPorNacionalidad,Nacionalidad Dato)
{
    NodoNacionalidad *Aux,*Antecesor;
    Aux = ListaPorNacionalidad;

    while(Aux != NULL && Aux->Info.NroDeNacionalidad < Dato.NroDeNacionalidad)
    {
        Antecesor = Aux;
        Aux = Aux->Sgte;
    }

    if(Aux != NULL && Dato.NroDeNacionalidad == Aux->Info.NroDeNacionalidad)
    {
        return Aux;
    }
    else
    {
        NodoNacionalidad *Nuevo = new NodoNacionalidad;
        Dato.CantTotalDeAutores = 0;
        Nuevo->Info = Dato;
        Nuevo->Sgte = Aux;

        if(Aux != ListaPorNacionalidad)
        {
            Antecesor->Sgte = Nuevo;
        }
        else
        {
            ListaPorNacionalidad = Nuevo;
        }

        return Nuevo;
    }
}
