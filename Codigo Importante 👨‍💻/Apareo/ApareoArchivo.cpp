#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct Parcial {
    unsigned dni;
    char nom[21];
    unsigned nota;
};

string condicion(unsigned n1, unsigned n2);
void apareo(FILE* ap1, FILE* ap2);

int main() {
    FILE* p1 = fopen("Parcial1.dat", "rb");
    FILE* p2 = fopen("Parcial2.dat", "rb");

    if (p1 == nullptr || p2 == nullptr) {
        cerr << "Error al abrir alguno de los archivos." << endl;
        return 1;
    }

    cout << "\nApareo de parciales:\n";
    apareo(p1, p2);

    fclose(p1);
    fclose(p2);

    return 0;
}

string condicion(unsigned n1, unsigned n2) {
    if (n1 > 7 && n2 > 7)
        return " Prom";
    else if (n1 > 5 && n2 > 5)
        return " Final";
    else
        return " Recursa";
}

void apareo(FILE* a1, FILE* a2) {
    Parcial p1, p2;

    fread(&p1, sizeof(Parcial), 1, a1);
    fread(&p2, sizeof(Parcial), 1, a2);

    while (!feof(a1) && !feof(a2)) {
        if (p1.dni < p2.dni) {
            cout << p1.dni << " " << p1.nom << condicion(p1.nota, 0) << endl;
            fread(&p1, sizeof(Parcial), 1, a1);
        } else if (p1.dni == p2.dni) {
            cout << p1.dni << " " << p1.nom << condicion(p1.nota, p2.nota) << endl;
            fread(&p1, sizeof(Parcial), 1, a1);
            fread(&p2, sizeof(Parcial), 1, a2);
        } else {
            cout << p2.dni << " " << p2.nom << condicion(0, p2.nota) << endl;
            fread(&p2, sizeof(Parcial), 1, a2);
        }
    }

    while (!feof(a1)) {
        cout << p1.dni << " " << p1.nom << condicion(p1.nota, 0) << endl;
        fread(&p1, sizeof(Parcial), 1, a1);
    }

    while (!feof(a2)) {
        cout << p2.dni << " " << p2.nom << condicion(0, p2.nota) << endl;
        fread(&p2, sizeof(Parcial), 1, a2);
    }
}
