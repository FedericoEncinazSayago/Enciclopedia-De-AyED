/*

Generar una lista de alumnos con sublista de examenes rendidos por alumno en un mes de examen.
Se ingresa examen por examen, sin orden.
Por cada examen se ingresa dni y nombre del alumno, fecha, c�digo de materia y nota del examen

*/

#include <iostream>
#include <stdio.h>

using namespace std;

struct Examen
{
    int dia;
    int codDeMateria;
    int nota;
};

struct NodoSub
{
    Examen info;
    NodoSub* siguiente;
};

struct Alumno
{
    int dni;
    string nombre;
    NodoSub *listaDeExamenes;
};

struct Nodo
{
    Alumno info;
    Nodo* siguiente;
};

void cargaDeDatos(Nodo *&lista);
void insertarEnSubLista(NodoSub *&listaDeExamenes, Examen dato);
Nodo* buscarInsertar(Nodo *&lista, Alumno dato);


int main()
{
    Nodo *listaAlumnos = NULL;

    cargaDeDatos(listaAlumnos);

    return 0;
}

void cargaDeDatos(Nodo *&lista)
{
    int dniDelAlumno, fechaDelExamen, codMateria, notaObtenida;
    string nombreDelAlumno;
    Alumno alu;
    Examen exa;
    Nodo *aux;

    cout << "Ingrese DNI del alumno: ";
    cin >> dniDelAlumno;

    while(dniDelAlumno != 0)  //ingresa datos del examen
    {
        cout << "Ingrese nombre del alumno: ";
        cin >> dniDelAlumno;

        cout << "Ingrese fecha del examen: ";
        cin >> fechaDelExamen;

        cout << "Ingrese codigo de materia rendida: ";
        cin >> codMateria;

        cout << "Ingrese nota del examen: ";
        cin >> notaObtenida;

        alu.dni = dniDelAlumno;
        alu.nombre = nombreDelAlumno;
        alu.listaDeExamenes = NULL;

        aux = buscarInsertar(lista, alu);

        exa.dia = fechaDelExamen;
        exa.codDeMateria = codMateria;
        exa.nota = notaObtenida;

        insertarEnSubLista(aux->info.listaDeExamenes, exa);

        cout << "Ingrese DNI de otro alumno (finaliza el proceso con 0): ";
        cin >> dniDelAlumno;
    }
}

void insertarEnSubLista(NodoSub *&listaDeExamenes, Examen dato)
{
    NodoSub *nuevo, *antecesor, *aux;
    nuevo = new NodoSub;
    nuevo->info = dato;
    aux = listaDeExamenes;

    while (aux != NULL && aux->info.dia < dato.dia)
    {
        antecesor = aux;
        aux = aux->siguiente;
    }

    nuevo->siguiente = aux;

    if (aux != listaDeExamenes)
    {
        antecesor->siguiente = nuevo;
    }
    else
    {
        listaDeExamenes = nuevo;
    }
}

Nodo* buscarInsertar(Nodo *&lista,Alumno dato)
{
    Nodo *aux = lista, *antecesor;

    while (aux != NULL && aux->info.dni < dato.dni)
    {
        antecesor = aux;
        aux = aux->siguiente;
    }

    if (aux != NULL && aux->info.dni == dato.dni)
    {
        return aux;
    }
    else
    {
        Nodo *nuevo = new Nodo;
        nuevo->info = dato;
        nuevo->siguiente = aux;

        if (aux != lista)
        {
            antecesor->siguiente = nuevo;
        }
        else
        {
            lista = nuevo;
        }

        return nuevo;
    }
}
