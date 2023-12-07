/*Dadas dos listas definidas como en el ejercicio 1, conteniendo la información de productos diferentes manufacturados en dos fábricas, se pide hacer una función que devuelva otra  lista ordenada por código de producto conteniendo la totalidad de la información.  */

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
void ApareoParaListas(Nodo*ListaPrincipal,Nodo*ListaSecundaria,Nodo*&ListaResultante);

int main()
{
    Nodo *ListaPrincipal = NULL;
    Nodo *ListaSecundaria = NULL;
    Nodo *ListaResultante = NULL;

    cout << "Carga de datos de Lista Principal:" << endl;

    CargaDeDatos(ListaPrincipal);

    cout << "---------------------------------" << endl;
    cout << "Carga de datos de Lista Secundaria:" << endl;

    CargaDeDatos(ListaSecundaria);

    cout << "---------------------------------" << endl;
    cout << "Lista resultante de comparar ambas listas:" < endl;

    ApareoParaListas(ListaPrincipal,ListaSecundaria,ListaResultante);

    MostrarLista(ListaResultante);

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

void ApareoParaListas(Nodo*ListaPrincipal,Nodo*ListaSecundaria,Nodo*&ListaResultante)
{
    Nodo *AuxPrincipal,*AuxSecundaria;
    AuxPrincipal = ListaPrincipal;
    AuxSecundaria = ListaSecundaria;

    while(AuxPrincipal != NULL && AuxSecundaria != NULL)
    {
        if(AuxPrincipal->Info.CodDeProducto < AuxSecundaria->Info.CodDeProducto)
        {
            Insertar(ListaResultante,AuxPrincipal->Info);

            AuxPrincipal = AuxPrincipal->Sgte;
        }
        else
        {
            if(AuxPrincipal->Info.CodDeProducto == AuxSecundaria->Info.CodDeProducto)
            {
                if(AuxPrincipal->Info.Descripcion == AuxSecundaria->Info.Descripcion)
                {
                    AuxPrincipal->Info.Stock = AuxPrincipal->Info.Stock + AuxSecundaria->Info.Stock;

                    Insertar(ListaResultante,AuxPrincipal->Info);
                }
                else
                {
                    Insertar(ListaResultante,AuxPrincipal->Info);
                    Insertar(ListaResultante,AuxSecundaria->Info);
                }

                AuxPrincipal = AuxPrincipal->Sgte
                AuxSecundaria = AuxSecundaria->Sgte;
            }
            else
            {
                Insertar(ListaResultante,AuxSecundaria->Info);

                AuxSecundaria = AuxSecundaria->Sgte;
            }
        }
    }

    while(AuxPrincipal != NULL)
    {
        Insertar(ListaResultante,AuxPrincipal->Info);

        AuxPrincipal = AuxPrincipal->Sgte;
    }

    while(AuxSecundaria != NULL)
    {
        Insertar(ListaResultante,AuxSecundaria->Sgte);

        AuxSecundaria = AuxSecundaria->Sgte;
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

