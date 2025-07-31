#include <iostream>
using namespace std;

struct Empleado {
    unsigned nroLegajo;
    int sucursal;
};

Empleado ingresarEmpleado();
void ingresarEmpleados(Empleado empleados[], int cantidad);
void mostrarEmpleados(const Empleado empleados[], int cantidad);
void ordenarPorLegajo(Empleado empleados[], int cantidad);
void mostrarCantidadSucursalesPorEmpleado(const Empleado empleados[], int cantidad);

int main() {
    const int CANTIDAD_EMPLEADOS = 10;
    Empleado empleados[CANTIDAD_EMPLEADOS];

    ingresarEmpleados(empleados, CANTIDAD_EMPLEADOS);

    ordenarPorLegajo(empleados, CANTIDAD_EMPLEADOS);

    cout << "\nEmpleados ordenados por legajo:\n";
    mostrarEmpleados(empleados, CANTIDAD_EMPLEADOS);

    cout << "\nCantidad de sucursales donde trabajó cada empleado:\n";
    mostrarCantidadSucursalesPorEmpleado(empleados, CANTIDAD_EMPLEADOS);

    return 0;
}

Empleado ingresarEmpleado() {
    Empleado empleado;
    cout << "Ingresar nro de legajo: ";
    cin >> empleado.nroLegajo;
    cout << "Ingresar número de sucursal: ";
    cin >> empleado.sucursal;
    return empleado;
}

void ingresarEmpleados(Empleado empleados[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        cout << "\nEmpleado " << i + 1 << ":\n";
        empleados[i] = ingresarEmpleado();
    }
}

void ordenarPorLegajo(Empleado empleados[], int cantidad) {
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - i - 1; j++) {
            if (empleados[j].nroLegajo > empleados[j + 1].nroLegajo) {
                swap(empleados[j], empleados[j + 1]);
            }
        }
    }
}

void mostrarEmpleados(const Empleado empleados[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        cout << "Legajo: " << empleados[i].nroLegajo
             << " | Sucursal: " << empleados[i].sucursal << endl;
    }
}

void mostrarCantidadSucursalesPorEmpleado(const Empleado empleados[], int cantidad) {
    int i = 0;
    while (i < cantidad) {
        int legajoActual = empleados[i].nroLegajo;
        int cantidadSucursales = 0;

        while (i < cantidad && empleados[i].nroLegajo == legajoActual) {
            cantidadSucursales++;
            i++;
        }

        cout << "Legajo " << legajoActual << " trabajó en "
             << cantidadSucursales << " sucursal(es)\n";
    }
}
