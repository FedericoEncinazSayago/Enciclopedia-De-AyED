/*Desarrollar una función que dada una pila y un valor, inserte ese valor como tercer elemento de la pila. */

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Nodo
{
    char Info;
    Nodo*Sig;
};


bool ExistenciaDeCapicua(char v[],int Nro);
void Apilar(Nodo*&Pila,char Dato);
void Desapilar(Nodo*&Pila,char &Dato);

int main()
{
    int CantDeCaracteres;
    string Palabra;

    cout << "INFORME palabra a analizar: ";
    cin >> Palabra;

    CantDeCaracteres = strlen(Palabra.c_str());

    char PalabraPorCaracteres[CantDeCaracteres];

    strcpy(PalabraPorCaracteres,Palabra.c_str());

    if(ExistenciaDeCapicua(PalabraPorCaracteres,CantDeCaracteres))
    {
        cout << "---------------------------------" << endl;
        cout << "La palabra es CAPICUA" <<endl;
    }
    else
    {
        cout << "---------------------------------" << endl;
        cout << "La palabra no es CAPICUA" << endl;
    }

    return 0;
}

bool ExistenciaDeCapicua(char v[],int Nro)
{
    int Volumen = 0,Verificador = 1,j = 0;
    char Caracter;
    Nodo*PilaAux = NULL;

    for(int i = 0;i < Nro;i++)
    {
        Apilar(PilaAux,v[i]);

        Volumen++;
    }

    Desapilar(PilaAux,Caracter);

    while(PilaAux != NULL && v[j] == Caracter)
    {
        Desapilar(PilaAux,Caracter);

        Verificador++;
        j++;
    }

    return Volumen == Verificador;
}

void Apilar(Nodo*&Pila,char Dato)
{
    Nodo*Aux = new Nodo;
    Aux->Sig = Pila;
    Aux->Info = Dato;
    Pila = Aux;
}


void Desapilar(Nodo*&Pila,char &Dato)
{
    Nodo*Aux;
    Aux = Pila;
    Dato = Aux->Info;
    Pila = Aux->Sig;

    delete Aux;
}


