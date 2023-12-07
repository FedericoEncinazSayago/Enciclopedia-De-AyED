#include <iostream>

using namespace std;

struct Medico
{
    int NroDeEspecialidad,Matricula,CantDeConsultas;
    string Nombre;
};

void InicializarMatriz(int MatrizPorEspacialidad[20][30]);
void CargaDeMedicos(Medico VectorDeMedicos[]);
void CargaDeInscriptos(int MatrizPorEspacialidad[20][30],Medico VectorDeMedicos[]);
void MostrarListadoDeEspecialidades(int MatrizPorEspacialidad[20][30]);
void MostrarListadoPorMedico(Medico VectorDeMedicos[]);
int BusquedaSecuencial(Medico VectorDeMedicos[],unsigned Dimension,int Dato);

int main()
{
    int MatrizPorEspacialidad[20][30];
    Medico VectorDeMedicos[175];

    InicializarMatriz(MatrizPorEspacialidad);
    CargaDeMedicos(VectorDeMedicos);
    CargaDeInscriptos(MatrizPorEspacialidad,VectorDeMedicos);
    
    cout << "Listado ordenado por especialidad con la cantidad de consultas: " << endl;
    
    MostrarListadoDeEspecialidades(MatrizPorEspacialidad);

    cout << "Listado por medico: " << endl;

    MostrarListadoPorMedico(VectorDeMedicos);

    return 0;
}

void InicializarMatriz(int MatrizPorEspacialidad[20][30])
{
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            MatrizPorEspacialidad[i][j] = 0;
        }
    }
}

void CargaDeMedicos(Medico VectorDeMedicos[])
{
    for(int i = 0; i < 175; i++)
    {
        cout << "INGRESE nro de matricula: " << endl;
        cin >> VectorDeMedicos[i].Matricula;

        cout << "INGRESE codigo de especialidad: " << endl;
        cin >> VectorDeMedicos[i].NroDeEspecialidad;

        cout << "INGRESE nombre del medico: " << endl;
        cin >> VectorDeMedicos[i].Nombre;

        VectorDeMedicos[i].CantDeConsultas = 0;

        cout << "---------------------------------" << endl;
    }
}

void CargaDeInscriptos(int MatrizPorEspacialidad[20][30],Medico VectorDeMedicos[])
{
    int NroDeClinica,NroDeMatriculaDelMedico,NroDeEspecialidad,DiaDeLaConsulta,Pos;

    cout << "INFORME nro de historia clinica: " << endl;
    cin >> NroDeClinica;

    while(NroDeClinica != 0)
    {
        cout << "INFORME nro de matricula del medico: " << endl:
        cin >> NroDeMatriculaDelMedico;

        Pos = BusquedaSecuencial(VectorDeMedicos,175,NroDeMatriculaDelMedico);

        if(Pos != -1)
        {
            cout << "INFORME dia de la consulta" << endl;
            cin >> DiaDeLaConsulta;

            NroDeEspecialidad = VectorDeMedicos[Pos].NroDeEspecialidad;
            MatrizPorEspacialidad[NroDeEspecialidad - 1][DiaDeLaConsulta - 1]++;
            VectorDeMedicos[Pos].CantDeConsultas++;
        }
        else
        {
            cout << "NO SE ENCONTRO AL MEDICO!" << endl;
        }

        cout << "INFORME el siguiente nro de historia clinica (0 para finalizar): " << endl;
        cin >> NroDeClinica;
    }
}

void MostrarListadoDeEspecialidades(int MatrizPorEspacialidad[20][30])
{
    int Menor,Dia,CantTotalDeConsultas = 0;

    for(int i = 0; i < 20; i++)
    {
        cout << "Especialidad " << i + 1 << endl;

        for(int j = 0; j < 30; j++)
        {
            cout << "Dia" << j + 1 << " - " << "Cantidad de consultas: " << MatrizPorEspacialidad[i][j] << endl;
        }

        cout << "---------------------------------" << endl;
    }

    for(int j = 0; j < 30; j++)
    {
        for(int i = 0; i < 20; i++)
        {
            CantTotalDeConsultas += MatrizPorEspacialidad[i][j];
        }

        if(j == 0 || Menor > CantTotalDeConsultas)
        {
            Menor = CantDeConsultas;
            Dia = j;
        }
    }

    cout << "Dia del mes en el que hubo la menor cantidad de consultas en total: " << Dia + 1 << endl;
}

void MostrarListadoPorMedico(Medico VectorDeMedicos[])
{
    for(int i = 0; i < 175; i++)
    {
        cout << "Nro de matricula: " << VectorDeMedicos[i].Matricula << " - " << "Nombre del medico: " << VectorDeMedicos[i].Nombre << " - " << "Cantidad total de consultas: " << VectorDeMedicos[i].CantDeConsultas << endl;
        cout << "---------------------------------" << endl;
    }
}

int BusquedaSecuencial(Medico VectorDeMedicos[],unsigned Dimension,int Dato)
{
    unsigned i = 0;

    while(i < Dimension && VectorDeMedicos[i].Matricula != Dato)
    {
        i++;
    }

    if(i == Dimension)
    {
        return -1
    }
    else
    {
        return i;
    }
}