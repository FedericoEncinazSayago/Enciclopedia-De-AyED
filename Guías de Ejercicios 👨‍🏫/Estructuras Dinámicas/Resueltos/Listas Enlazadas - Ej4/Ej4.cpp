/*Dada la lista del ejercicio 1, hacer una función que devuelva dos listas una con los productos cuyo stock sea inferior a 50 unidades y otra con los restantes*/

#include <iostream>

using namespace std;

struct Productos
{
    int CodDeProducto,Importe,Stock;
    string Descripcion;
};

struct Nodo
{
    Productos Info;
    Nodo *Sgte;
};

void Punto1(Nodo*Lista,Nodo*&ListaStock,Nodo*ListaRestante);
void CargaDeDatos(Nodo*&Lista);
void Insertar(Nodo*&Lista,Productos Dato);
void MostrarLista(Nodo*Lista);


int main()
{
    Nodo *ListaPrincipal = NULL,*ListaStock = NULL,*ListaRestante = NULL;

    CargaDeDatos(ListaPrincipal);

    Punto1(ListaPrincipal,ListaStock,ListaRestante);

    cout << "---------------------------------" << endl;
    cout << "Lista de productos cuyo stock es inferior a 50 unidades:" << endl;

    MostrarLista(ListaStock);

    cout << "---------------------------------" << endl;
    cout << "Lista de productos restantes:" << endl;

    MostrarLista(ListaRestante);

    cout << "---------------------------------" << endl;

    return 0;
}

void CargaDeDatos(Nodo*&Lista)
{
    Productos P;

    cout << "INFORME codigo del producto: ";
    cin >> P.CodDeProducto;

    while(P.CodDeProducto != 0)
    {
        cout << "INFORME descripcion del producto: ";
        cin >> P.Descripcion;

        cout << "INFORME importe del producto: ";
        cin >> P.Importe;

        cout << "INFORME stock del producto: ";
        cin >> P.Stock;

        Insertar(Lista,P);

        cout << "---------------------------------" << endl;
        cout << "INFORME codigo del siguiente producto (0 para finalizar): ";
        cin >> P.CodDeProducto;
    }

}

void Punto1(Nodo*Lista,Nodo*&ListaStock,Nodo*ListaRestante)
{
    Nodo *Aux = Lista;

    while(Aux != NULL)
    {
        if(Aux->Info.Stock > 50)
        {
            Insertar(ListaRestante,Aux->Info);
        }
        else
        {
            Insertar(ListaStock,Aux->Info);
        }

        Aux = Aux->Sgte;
    }
}


void Insertar(Nodo*&Lista,Productos Dato)//Inserta elementos a la lista conservando el orden
{
    Nodo *Nuevo,*Antecesor,*Aux;
    Nuevo = new Nodo;
    Nuevo->Info = Dato;
    Aux = Lista;

    while(Aux != NULL && Aux->Info.CodDeProducto < Dato.CodDeProducto)
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

void MostrarLista(Nodo*Lista)
{
    Nodo *Aux = Lista;

    while(Aux != NULL)
    {
        cout << "Codigo del producto: " << Aux->Info.CodDeProducto << " - " << "Descripcion del producto: " << Aux->Info.Descripcion << " - " << "Stock del producto: " << Aux->Info.Stock << " (Unidades)" << " - " << "Importe del producto: " << "$" << Aux->Info.Importe << endl;

        Aux = Aux->Sgte;
    }
}

