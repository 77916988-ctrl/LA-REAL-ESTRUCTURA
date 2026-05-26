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
int main() {

    return 0;
}
