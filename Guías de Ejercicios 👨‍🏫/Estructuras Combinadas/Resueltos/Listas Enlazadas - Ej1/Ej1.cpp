/*Se tiene ordenada por código de producto una lista simplemente enlazada donde cada nodo contiene: código, descripción, importe y stock. 
Hacer funciones para: 
a. dado un entero K, imprimir el k-ésimo elemento.
b. incrementar en un 10% el importe de un producto dado su código.
c. devolver el stock de un producto dado ó cero si no se lo encuentra.*/


#include <iostream>

using namespace std;

struct Productos
{
    int CodDeProducto,Importe,Stock;
    string Descripcion;
};

struct NodoLista
{
    Productos Info;
    NodoLista*Sig;
};

void CargaDeDatos(NodoLista*&Primero);
void Punto1(NodoLista*&Primero,Productos &Dato,int Nro,bool &Verificador);
void Punto2(NodoLista*&Primero,int CodDeProducto);
void Punto3(NodoLista*&Primero,int CodDeProducto);
void Insertar(NodoLista*&Primero,Productos Dato);
NodoLista *BusquedaSecuencialOrdenada(NodoLista*Primero,int CodDeProducto);


int main()
{
    int Nro,Stock;
    Productos P;
    bool Verificador = false;
    NodoLista *PrimeroProd = NULL;

    CargaDeDatos(PrimeroProd);

    cout << "---------------------------------" << endl;
    cout << "INFORME posicion del elemento a buscar: ";
    cin >> Nro;

    Punto1(PrimeroProd,P,Nro,Verificador);

    if(Verificador)
    {
        cout << "Codigo del producto: " << P.CodDeProducto << " - " << "Descripcion del producto: " << P.Descripcion << " - " << "Stock del producto: " << P.Stock << " (Unidades)" << " - " << "Importe del producto: " << "$" << P.Importe << endl;
    }
    else
    {
        cout << "No se pudo encontrar al elemento" << endl;
    }

    cout << "---------------------------------" << endl;
    cout << "INFORME codigo del producto al cual se incrementa un 10% a su importe: ";
    cin >> Nro;

    Punto2(PrimeroProd,Nro);

    cout << "---------------------------------" << endl;
    cout << "INFORME codigo del producto: ";
    cin >> Nro;

    Punto3(PrimeroProd,Nro);

    cout << "---------------------------------" << endl;

    return 0;
}

void CargaDeDatos(NodoLista*&Primero)
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

        Insertar(Primero,P);

        cout << "---------------------------------" << endl;
        cout << "INFORME codigo del siguiente producto (0 para finalizar): ";
        cin >> P.CodDeProducto;
    }

}

void Punto1(NodoLista*&Primero,Productos &Dato,int Nro,bool &Verificador)
{
    int i = 1;
    NodoLista*Aux;
    Aux = Primero;

    while(Aux != NULL && i <= Nro)
    {
        if(i == Nro)
        {
            Dato = Aux->Info;
            Verificador = true;
        }

        Aux = Aux->Sig;
        i++;
    }
}

void Punto2(NodoLista*&Primero,int CodDeProducto)
{
    int Aumento,Importe;
    NodoLista *Aux = BusquedaSecuencialOrdenada(Primero,CodDeProducto);

    if(Aux == NULL)
    {
        cout << "No fue posible encontrar al producto" << endl;
    }
    else
    {
        Importe = Aux->Info.Importe;
        Aumento= (Importe*10)/100 + Importe;
        Aux->Info.Importe = Aumento;

        cout << "Producto actualizado: " <<endl;
        cout << "Codigo del producto: " << Aux->Info.CodDeProducto << " - " << "Descripcion del producto: " << Aux->Info.Descripcion << " - " << "Stock del producto: " << Aux->Info.Stock << " (Unidades)" << " - " << "Importe del producto: " << "$" << Aux->Info.Importe << endl;
    }
}

void Punto3(NodoLista*&Primero,int CodDeProducto)
{
    int Stock = 0;
    NodoLista *Aux = BusquedaSecuencialOrdenada(Primero,CodDeProducto);

    if(Aux == NULL)
    {
        cout << "Codigo de producto: " << CodDeProducto << " - " << "Stock: " << Stock << endl;
    }
    else
    {
        Stock = Aux->Info.Stock;

        cout << "Codigo de producto: " << CodDeProducto << " - " << "Stock: " << Stock << endl;
    }
}

void Insertar(NodoLista*&Primero,Productos Dato)//Inserta elementos a la lista conservando el orden
{
    NodoLista *Nuevo,*Antecesor,*Aux;
    Nuevo = new NodoLista;
    Nuevo->Info = Dato;
    Aux = Primero;

    while(Aux != NULL && Aux->Info.CodDeProducto < Dato.CodDeProducto)
    {
        Antecesor = Aux;
        Aux = Aux->Sig;
    }

    Nuevo->Sig = Aux;

    if(Aux != Primero)
    {
        Antecesor->Sig = Nuevo;
    }
    else
    {
        Primero = Nuevo;
    }

}

NodoLista *BusquedaSecuencialOrdenada(NodoLista*Primero,int CodDeProducto)//Devuele una variable puntero del producto con codigo xxx. Hay que tenerla en cuenta cuando la lista este ordenada
{
    NodoLista *Aux;
    Aux = Primero;

    while(Aux != NULL && Aux->Info.CodDeProducto < CodDeProducto)
    {
        Aux = Aux->Sig;
    }

    if(Aux == NULL || Aux->Info.CodDeProducto != CodDeProducto)
    {
        return NULL;
    }
    else
    {
        return Aux;
    }

}

