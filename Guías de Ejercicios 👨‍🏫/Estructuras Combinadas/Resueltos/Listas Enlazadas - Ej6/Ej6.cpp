/*Dada la lista definida en el ejercicio 1 conteniendo productos repetidos, hacer una función que deje en la lista un solo nodo por producto con el stock sumado. */

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

void CargaDeDatos(Nodo*&Lista);
void Insertar(Nodo*&Lista,Productos Dato);
void CorteDeControlListas(Nodo*&Lista);
void MostrarLista(Nodo*Lista);

int main()
{
    Nodo *Lista = NULL;

    CargaDeDatos(Lista);

    CorteDeControlListas(Lista);

    cout << "Lista resultante:" << endl;

    MostrarLista(Lista);

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

void Insertar(Nodo*&Lista,Productos Dato)
{
    Nodo *Aux;
    Nodo *Nuevo = new Nodo;
    Nuevo->Info = Dato;
    Nuevo->Sgte = NULL;

    if(Lista != NULL)
    {
        Aux = Lista;

        while(Aux->Sgte != NULL)
        {
            Aux = Aux->Sgte;
        }

        Aux->Sgte = Nuevo;
    }
    else
    {
        Lista = Nuevo;
    }
}

void CorteDeControlListas(Nodo*&Lista)
{
    int Stock = 0,Repetedidos = 0;
    Nodo *Actual = Lista,*Siguiente,*Aux;

    while(Actual != NULL)
    {
        Siguiente = Actual;

        do
        {
            Stock = Stock + Siguiente->Info.Stock;
            Aux = Siguiente;
            Siguiente = Siguiente->Sgte;

            if(Repetedidos != 0)
            {
                delete Aux;
            }

            Repetedidos++;
        }
        while(Siguiente != NULL && Actual->Info.CodDeProducto == Siguiente->Info.CodDeProducto);

        Actual->Sgte = Siguiente;
        Actual->Info.Stock = Stock;
        Actual = Siguiente;
        Stock = 0;
        Repetedidos = 0;
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
