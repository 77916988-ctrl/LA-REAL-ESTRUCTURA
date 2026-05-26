#include<iostream>
#include <string>
#include <fstream>
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
    return (c1 * 0.20) + (ep * 0.25) + (c2 + 0.20) + (ef * 0.35);
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

int main() {

    return 0;
}
