#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Parcial {
    unsigned dni;
    char nombre[21];
    unsigned nota;
};

void corteControl(FILE* archivo);

int main() {
    FILE* archivoExamenes = fopen("Examenes.dat", "rb");
    if (archivoExamenes == nullptr) {
        cerr << "Error al abrir el archivo 'Examenes.dat'" << endl;
        return 1;
    }

    cout << "=== Corte de Control por Alumno ===" << endl;
    corteControl(archivoExamenes);
    fclose(archivoExamenes);

    return 0;
}

void corteControl(FILE* archivo) {
    Parcial parcial;
    int sumaNotas, contadorNotas;
    unsigned dniActual;

    fread(&parcial, sizeof(Parcial), 1, archivo);

    while (!feof(archivo)) {
        dniActual = parcial.dni;
        sumaNotas = 0;
        contadorNotas = 0;

        do {
            sumaNotas += parcial.nota;
            contadorNotas++;
            fread(&parcial, sizeof(Parcial), 1, archivo);
        } while (!feof(archivo) && parcial.dni == dniActual);

        cout << dniActual << " promedio: " << sumaNotas / contadorNotas << endl;
    }
}
