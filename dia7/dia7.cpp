#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct nodo {
    string valor;
    int fila;
    int posicion;
    nodo *sig;
} typedef *Lista;

Lista crearLista() {
    return NULL;
}

void insertarValor(Lista &L, char valor, int fila, int posicion) {
    nodo *nuevo = new nodo;
    nuevo->valor = valor;
    nuevo->fila = fila;
    nuevo->posicion = posicion;
    nuevo->sig = NULL;

    if (L == NULL)
        L = nuevo;
    else {
        nodo *aux = L;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
}

void guardarSalidaEnArchivo(Lista l, const string &nombreArchivo) {
    ofstream out(nombreArchivo);
    if (!out.is_open()) {
        cerr << "No se pudo abrir el archivo de salida." << endl;
        return;
    }

    int filaActual = 0;
    nodo *aux = l;

    while (aux != NULL) {
        if (aux->fila != filaActual) {
            out << "\n";
            filaActual = aux->fila;
        }
        out << aux->valor;
        aux = aux->sig;
    }

    out << "\n";
    out.close();
}

bool existePalo(Lista l, int fila, int posicion) {
    nodo *aux = l;
    while (aux != NULL) {
        if (aux->fila == fila &&
            aux->posicion == posicion &&
            (aux->valor == "|" || aux->valor == "S")) {
            return true;
        }
        aux = aux->sig;
    }
    return false;
}

bool esIzquierdaValida(nodo* dosAtras, nodo* actual) {
    if (!dosAtras) return false;
    if (!dosAtras->sig) return false;

    nodo* izquierda = dosAtras->sig;

    return izquierda->fila == actual->fila &&
           izquierda->posicion == actual->posicion - 1;
}

bool esDerechaValida(nodo* actual) {
    if (!actual || !actual->sig) return false;

    return actual->sig->fila == actual->fila &&
           actual->sig->posicion == actual->posicion + 1;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open())
        return 1;

    Lista l = crearLista();
    char c;
    int fila = 0;
    int posicion = 0;

    while (file.get(c)) {
        if (c == '\n') {
            posicion = 0;
            fila++;
            continue;
        }
        insertarValor(l, c, fila, posicion++);
    }

    nodo *actual = l;
    nodo *dosPasosAtras = nullptr;

    if (actual != nullptr) actual = actual->sig;
    if (actual != nullptr) actual = actual->sig;
    dosPasosAtras = l;

    int totalRes = 0;

    while (actual != nullptr) {
        // Si el nodo actual es ^ y viene un | desde arriba
        if (actual->valor == "^" && existePalo(l, actual->fila - 1, actual->posicion)) {
            if (esIzquierdaValida(dosPasosAtras, actual)) {
                dosPasosAtras->sig->valor = "|";
            }
            if (esDerechaValida(actual)) {
                actual->sig->valor = "|";
            }
            totalRes++;
            // El | no sigue bajando desde aca
        }
        // Si viene un | desde arriba y es un punto
        else if (actual->valor == "." &&
                 existePalo(l, actual->fila - 1, actual->posicion)) {
            actual->valor = "|";
        }

        actual = actual->sig;
        dosPasosAtras = dosPasosAtras->sig;
    }

    cout << "El total es: " << totalRes << endl;
    guardarSalidaEnArchivo(l, "output.txt");
    return 0;
}
