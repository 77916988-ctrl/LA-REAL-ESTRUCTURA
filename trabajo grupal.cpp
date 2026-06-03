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

bool existeID(NodoLista* lista, int id) {
    while (lista != NULL) {
        if (lista->info.id == id)
            return true;
        lista = lista->siguiente;
    }
    return false;
}

void validarID(NodoLista* lista, int& id) {
    while (true) {
        cout << "ID: ";

        if (!(cin >> id)) {
            cout << "Error... Debe ingresar un numero.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (existeID(lista, id)) {
            cout << "Error... El ID ya existe.\n";
            continue;
        }

        break;
    }
}

void validarNotas(float& n1, float& n2, float& n3, float& n4) {
    while (true) {

        cout << "Notas (C1 EP C2 EF): ";

        if (!(cin >> n1 >> n2 >> n3 >> n4)) {
            cout << "Error: Solo se permiten numeros.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (n1 < 0 || n1 > 20 ||
            n2 < 0 || n2 > 20 ||
            n3 < 0 || n3 > 20 ||
            n4 < 0 || n4 > 20) {

            cout << "Error: Las notas deben estar entre 0 y 20.\n";
            continue;
        }

        break;
    }
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
            float n1, n2, n3, n4;
            validarNotas(n1, n2, n3, n4);
            temp->info.c1 = n1;
            temp->info.ep = n2;
            temp->info.c2 = n3;
            temp->info.ef = n4;
            temp->info.promedio =
                calcularPromedio(n1, n2, n3, n4);
            temp->info.estado =
                (temp->info.promedio >= 11)
                ? "Aprobado"
                : "Desaprobado";
            cout << "Notas actualizadas.\n";
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

void registrarCambio(NodoPila*& cima, string msg) {
    NodoPila* nuevo = new NodoPila();
    nuevo->accion = msg;
    nuevo->siguiente = cima;
    cima = nuevo;
}

void verUltimoCambio(NodoPila* cima) {
    if (cima == NULL) cout << "Sin historial de cambios.\n";
    else cout << "ULTIMA ACCION: " << cima->accion << endl;
}

void desapilarCambio(NodoPila*& cima) {
    if (cima == NULL) { cout << "Historial vacio.\n"; return; }
    cout << "Eliminado: " << cima->accion << endl;
    NodoPila* aux = cima;
    cima = cima->siguiente;
    delete aux;
}

void guardarDatos(NodoLista* lista) {
    ofstream archivo("notas_alumnos.txt");
    NodoLista* temp = lista;
    while (temp != NULL) {
        archivo << temp->info.id << " " << temp->info.c1 << " " << temp->info.ep << " "
                << temp->info.c2 << " " << temp->info.ef << " " << temp->info.nombre << endl;
        temp = temp->siguiente;
    }
    archivo.close();
    cout << "-> Datos guardados en notas_alumnos.txt\n";
}

void cargarDatos(NodoLista*& lista) {
    ifstream archivo("notas_alumnos.txt");
    if (!archivo) { cout << "No se encontro el archivo.\n"; return; }
    int id;
    float n1, n2, n3, n4;
    string nom;
    int n = 0;
    while (archivo >> id >> n1 >> n2 >> n3 >> n4 >> nom) {
        registrarAlumno(lista, id, nom, n1, n2, n3, n4);
        n++;
    }
    archivo.close();
    cout << "-> Se cargaron " << n << " alumno(s).\n";
}

int main() {
    NodoLista* registro = NULL;
    NodoCola *frenteR = NULL, *finalR = NULL;
    NodoPila* historial = NULL;
    int op, id, sub;
    string nom;
    float n1, n2, n3, n4;

    do {
        cout << "\n===========================================" << endl;
        cout << "  SISTEMA DE GESTION ACADEMICA (U.C.)     " << endl;
        cout << "===========================================" << endl;
        cout << " 1. Registrar Alumno\n 2. Ver Registro\n 3. Ordenar por Promedio\n 4. Buscar Alumno" << endl;
        cout << " 5. Encolar Reclamo por ID\n 6. Atender Reclamo\n 7. Historial (Ver/Desapilar)" << endl;
        cout << " 8. Guardar Datos\n 9. Cargar Datos\n10. Modificar Notas\n11. Eliminar Alumno\n12. Salir" << endl;
        cout << " Seleccione: ";
        cin >> op;

        switch (op) {
            case 1:
			    validarID(registro, id);
			    cout << "Nombre: ";
			    cin.ignore();
			    getline(cin, nom);
			    validarNotas(n1, n2, n3, n4);
			    registrarAlumno(registro, id, nom, n1, n2, n3, n4);
			    registrarCambio(historial, "Registro de alumno");
			
			    break;
            case 2:
                mostrarRegistro(registro);
                break;
            case 3:
                ordenarPorPromedio(registro);
                break;
            case 4:
                cout << "ID a buscar: "; cin >> id;
                buscarAlumno(registro, id);
                break;
            case 5: {
                cout << "ID a encolar: "; cin >> id;
                NodoLista* t = registro;
                bool ok = false;
                while (t != NULL) {
                    if (t->info.id == id) {
                        encolarReclamo(frenteR, finalR, t->info);
                        ok = true;
                        break;
                    }
                    t = t->siguiente;
                }
                if (!ok) cout << "Alumno no encontrado.\n";
                break;
            }
            case 6:
                atenderReclamo(frenteR, finalR);
                break;
            case 7:
                cout << "1. Ver ultimo  2. Desapilar: "; cin >> sub;
                if (sub == 1) verUltimoCambio(historial);
                else if (sub == 2) desapilarCambio(historial);
                else cout << "Opcion no valida.\n";
                break;
            case 8:
                guardarDatos(registro);
                break;
            case 9:
                cargarDatos(registro);
                break;
            case 10:
                cout << "ID a modificar: "; cin >> id;
                modificarNotas(registro, id);
                registrarCambio(historial, "Modificacion de notas");
                break;
            case 11:
                cout << "ID a eliminar: "; cin >> id;
                eliminarAlumno(registro, id);
                break;
            case 12:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (op != 12);

    return 0;
}
