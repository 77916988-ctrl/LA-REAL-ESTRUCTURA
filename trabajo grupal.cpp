#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Alumno {
    int id;
    string nombre;
    float c1, ep, c2, ef;
    float promedio;
    string estado;
};

struct NodoLista { Alumno info; NodoLista* siguiente; };
struct NodoCola  { Alumno info; NodoCola* siguiente; };
struct NodoPila  { string accion; NodoPila* siguiente; };

float calcularPromedio(float c1, float ep, float c2, float ef) {
    return (c1 * 0.20) + (ep * 0.25) + (c2 * 0.20) + (ef * 0.35);
}

void registrarAlumno(NodoLista*& lista, int id, string nom, float n1, float n2, float n3, float n4) {
    NodoLista* nuevo = new NodoLista();
    nuevo->info.id = id;
    nuevo->info.nombre = nom;
    nuevo->info.c1 = n1;
    nuevo->info.ep = n2;
    nuevo->info.c2 = n3;
    nuevo->info.ef = n4;
    nuevo->info.promedio = calcularPromedio(n1, n2, n3, n4);
    nuevo->info.estado = (nuevo->info.promedio >= 11) ? "Aprobado" : "Desaprobado";
    nuevo->siguiente = lista;
    lista = nuevo;
}

void mostrarRegistro(NodoLista* lista) {
    if (lista == NULL) { cout << "Registro vacio.\n"; return; }
    NodoLista* temp = lista;
    cout << "\nID\tNombre\tC1\tEP\tC2\tEF\tProm\tEstado\n";
    while (temp != NULL) {
        cout << temp->info.id << "\t" << temp->info.nombre << "\t" << temp->info.c1 << "\t"
             << temp->info.ep << "\t" << temp->info.c2 << "\t" << temp->info.ef << "\t"
             << fixed << setprecision(2) << temp->info.promedio << "\t" << temp->info.estado << endl;
        temp = temp->siguiente;
    }
}

void ordenarPorPromedio(NodoLista*& lista) {
    if (lista == NULL) return;
    for (NodoLista* i = lista; i != NULL; i = i->siguiente) {
        for (NodoLista* j = i->siguiente; j != NULL; j = j->siguiente) {
            if (i->info.promedio < j->info.promedio) {
                Alumno aux = i->info;
                i->info = j->info;
                j->info = aux;
            }
        }
    }
    cout << "-> Lista ordenada por promedio (Mayor a menor).\n";
}

int main() {
    return 0;
}
