#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> //Para darle formato a los numeros decimales

using namespace std;

struct Alumno {  //implementamos la estructura principal
    int id;
    string nombre;
    float c1, ep, c2, ef;
    float promedio;
    string estado;
};

struct NodoLista { Alumno info; NodoLista* siguiente; };  //los nodos aqui son como ladrillos oara construir por ejemplo aqui contiene el formulario alumno y
struct NodoCola  { Alumno info; NodoCola* siguiente; };    // NodoLista*  un puntero que apunta al siguiente ladrillo o nodo 
struct NodoPila  { string accion; NodoPila* siguiente; };   // nodo lista imaginemos qeue es un tre con bagones Nodo cola es como la fila de un banco NodoPila como si estuviesemos poniendo platos
//pues asi cada uno recorre como debe ya sea cola FIFO o pila LIFO 

float calcularPromedio(float c1, float ep, float c2, float ef) {   //esta es el calculo que se usara para sacar el promedio del alumno 
    return (c1 * 0.20) + (ep * 0.25) + (c2 * 0.20) + (ef * 0.35);
}

void registrarAlumno(NodoLista*& lista, int id, string nom, float n1, float n2, float n3, float n4) { //aqui creamos pero creamos alumno nuevo  y lo agrega al inicio de la lista 
  
    NodoLista* nuevo = new NodoLista(); //Crea un nuevo ladrillo (nodo) vacio en la memoria.
    nuevo->info.id = id; //Llena todos los campos del alumno dentro del nuevo 
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
    
    if (lista == NULL) { cout << "Registro vacio.\n"; return; } //Si la lista esta vacia (no hay ningun alumno), muestra un mensaje
    NodoLista* temp = lista;        // Crea un puntero auxiliar "temp" que empieza apuntando al primer alumno. Usamos "temp" para no perder la referencia original "lista".
    cout << "\nID\tNombre\tC1\tEP\tC2\tEF\tProm\tEstado\n"; // es el encabezado
    while (temp != NULL) {
        cout << temp->info.id << "\t" << temp->info.nombre << "\t" << temp->info.c1 << "\t"
             << temp->info.ep << "\t" << temp->info.c2 << "\t" << temp->info.ef << "\t"
             << fixed << setprecision(2) << temp->info.promedio << "\t" << temp->info.estado << endl;
        temp = temp->siguiente;
    }
}

void ordenarPorPromedio(NodoLista*& lista) { //Muestra en pantalla TODOS los alumnos registrados con todos sus datos
   
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

void buscarAlumno(NodoLista* lista, int idB) {
    NodoLista* temp = lista;
    while (temp != NULL) {
        if (temp->info.id == idB) {
            cout << "ENCONTRADO: " << temp->info.nombre << " | Promedio: " << temp->info.promedio << endl;
            return;
        }
        temp = temp->siguiente;
    }
    cout << "Alumno no encontrado.\n";
}

void modificarNotas(NodoLista* lista, int id) {
    NodoLista* temp = lista;
    while (temp != NULL) {
        if (temp->info.id == id) {
            cout << "Nuevas notas (C1 EP C2 EF): ";
            cin >> temp->info.c1 >> temp->info.ep >> temp->info.c2 >> temp->info.ef;
            temp->info.promedio = calcularPromedio(temp->info.c1, temp->info.ep, temp->info.c2, temp->info.ef);
            temp->info.estado = (temp->info.promedio >= 11) ? "Aprobado" : "Desaprobado";
            cout << "Notas actualizadas. Promedio: " << temp->info.promedio << endl;
            return;
        }
        temp = temp->siguiente;
    }
    cout << "Alumno no encontrado.\n";
}

void eliminarAlumno(NodoLista*& lista, int id) {
    NodoLista* temp = lista;
    NodoLista* ant = NULL;
    while (temp != NULL) {
        if (temp->info.id == id) {
            if (ant == NULL) lista = temp->siguiente;
            else ant->siguiente = temp->siguiente;
            cout << "Alumno eliminado.\n";
            delete temp;
            return;
        }
        ant = temp;
        temp = temp->siguiente;
    }
    cout << "Alumno no encontrado.\n";
}

void encolarReclamo(NodoCola*& frente, NodoCola*& final, Alumno a) {
    NodoCola* nuevo = new NodoCola();
    nuevo->info = a;
    nuevo->siguiente = NULL;
    if (frente == NULL) frente = nuevo;
    else final->siguiente = nuevo;
    final = nuevo;
    cout << "-> Alumno " << a.nombre << " en fila de atencion.\n";
}

void atenderReclamo(NodoCola*& frente, NodoCola*& final) {
    if (frente == NULL) { cout << "No hay reclamos pendientes.\n"; return; }
    NodoCola* aux = frente;
    cout << "ATENDIENDO A: " << aux->info.nombre << " (ID: " << aux->info.id << ")\n";
    frente = frente->siguiente;
    delete aux;
    if (frente == NULL) final = NULL;
}

int main() {
    return 0;
}
