#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
struct nodo
{
    int valor;
    nodo *sig;
    nodo *ant;
} typedef *nodoLista;

struct l
{
    int posicion;
    int total;
    nodoLista lista;
} typedef *Lista;

Lista crearLista()
{
    Lista L = new l;
    L->total = 0;
    L->lista = NULL;
    return L;
}

struct filaNodo {
    Lista fila;
    filaNodo *sig;
    filaNodo *ant;
} typedef *ListaFilas;

void insertarFinal(Lista L, char c)
{
    nodoLista nuevo = new nodo;
    nuevo->valor = c;
    nuevo->sig = NULL;
    nuevo->ant = NULL;

    if (L->lista == NULL)
    {
        L->lista = nuevo;
    }
    else
    {
        nodoLista aux = L->lista;
        while (aux->sig != NULL)
            aux = aux->sig;

        aux->sig = nuevo;
        nuevo->ant = aux;
    }
    L->total++;
}

nodoLista getNodo(Lista L, int index)
{
    if (index < 0 || index >= L->total)
        return NULL;

    nodoLista aux = L->lista;
    for (int i = 0; i < index; i++)
        aux = aux->sig;

    return aux;
}
// int contarVecinos(Lista prev, Lista cur, Lista next, int col)
// {
//     int total = 0;

//     // listas disponibles: prev, cur, next
//     // cada una puede ser NULL (bordes)

//     Lista filas[3] = {prev, cur, next};
//     int filasIndex[3] = {-1, 0, 1}; // -1 fila arriba, 0 actual, +1 abajo

//     for (int f = 0; f < 3; f++)
//     {
//         if (filas[f] == NULL)
//             continue;

//         for (int dc = -1; dc <= 1; dc++)
//         {

//             if (filasIndex[f] == 0 && dc == 0)
//                 continue; // no contar a sí mismo

//             nodoLista nodoV = getNodo(filas[f], col + dc);

//             if (nodoV != NULL && nodoV->valor == '@')
//                 total++;
//         }
//     }

//     return total;
// }

int contarVecinos(Lista prev, Lista cur, Lista next, int col) {
    int total = 0;
    Lista filas[3] = {prev, cur, next};

    for (int f = 0; f < 3; f++) {
        if (filas[f] == NULL)
            continue;

        for (int dc = -1; dc <= 1; dc++) {
            if (f == 1 && dc == 0)
                continue;

            nodoLista nodoV = getNodo(filas[f], col + dc);
            if (nodoV != NULL && nodoV->valor == '@')
                total++;
        }
    }

    return total;
}
Lista leerLinea(ifstream &file)
{
    string s;
    if (!getline(file, s))
        return NULL; // EOF

    Lista L = crearLista();
    for (char c : s)
        insertarFinal(L, c);

    return L;
}
Lista copiarLista(Lista original) {
    Lista nueva = crearLista();
    nodoLista aux = original->lista;
    while (aux != NULL) {
        insertarFinal(nueva, aux->valor);
        aux = aux->sig;
    }
    return nueva;
}

ListaFilas copiarFilas(ListaFilas original) {
    ListaFilas nuevaCabeza = NULL, anterior = NULL;

    while (original != NULL) {
        Lista nuevaFila = copiarLista(original->fila);
        ListaFilas nuevoNodo = new filaNodo;
        nuevoNodo->fila = nuevaFila;
        nuevoNodo->sig = NULL;
        nuevoNodo->ant = anterior;

        if (anterior != NULL)
            anterior->sig = nuevoNodo;
        else
            nuevaCabeza = nuevoNodo;

        anterior = nuevoNodo;
        original = original->sig;
    }

    return nuevaCabeza;
}
// int main()
// {
//     ifstream file("input.txt");

//     // Mantener 3 punteros:
//     Lista prev = NULL;            // fila anterior
//     Lista cur = leerLinea(file);  // fila actual
//     Lista next = leerLinea(file); // fila siguiente
//     int total = 0;
//     while (cur != NULL)
//     {

//         Lista resultado = crearLista();

//         for (int col = 0; col < cur->total; col++)
//         {

//             nodoLista nodoActual = getNodo(cur, col);

//             if (nodoActual->valor == '@')
//             {
//                 int vecinos = contarVecinos(prev, cur, next, col);

//                 if (vecinos < 4)
//                 {

//                     insertarFinal(resultado, 'x');
//                     total++;
//                 }

//                 else
//                     insertarFinal(resultado, '@');
//             }
//             else
//             {
//                 insertarFinal(resultado, nodoActual->valor); // .
//             }
//         }

//         nodoLista aux = resultado->lista;
//         while (aux != NULL)
//         {
//             aux = aux->sig;
//         }
//         prev = cur;
//         cur = next;
//         next = leerLinea(file);
//     }
//     cout << total;

//     return 0;
// }


int main() {
    ifstream file("input.txt");

    // Cargar todas las filas como lista doblemente enlazada
    ListaFilas cabeza = NULL, ultimo = NULL;

    while (true) {
        Lista fila = leerLinea(file);
        if (fila == NULL)
            break;

        ListaFilas nuevoNodo = new filaNodo;
        nuevoNodo->fila = fila;
        nuevoNodo->sig = NULL;
        nuevoNodo->ant = ultimo;

        if (ultimo != NULL)
            ultimo->sig = nuevoNodo;
        else
            cabeza = nuevoNodo;

        ultimo = nuevoNodo;
    }

    int totalRemovidos = 0;
    bool huboCambios = true;

    while (huboCambios) {
        huboCambios = false;
        ListaFilas original = cabeza;
        ListaFilas nuevoMapa = NULL, ultimoNuevo = NULL;

        while (original != NULL) {
            Lista resultado = crearLista();

            Lista prev = (original->ant != NULL) ? original->ant->fila : NULL;
            Lista cur = original->fila;
            Lista next = (original->sig != NULL) ? original->sig->fila : NULL;

            for (int col = 0; col < cur->total; col++) {
                nodoLista nodoActual = getNodo(cur, col);

                if (nodoActual->valor == '@') {
                    int vecinos = contarVecinos(prev, cur, next, col);
                    if (vecinos < 4) {
                        insertarFinal(resultado, 'x');
                        totalRemovidos++;
                        huboCambios = true;
                    } else {
                        insertarFinal(resultado, '@');
                    }
                } else {
                    insertarFinal(resultado, nodoActual->valor);
                }
            }

            ListaFilas nuevoNodo = new filaNodo;
            nuevoNodo->fila = resultado;
            nuevoNodo->sig = NULL;
            nuevoNodo->ant = ultimoNuevo;

            if (ultimoNuevo != NULL)
                ultimoNuevo->sig = nuevoNodo;
            else
                nuevoMapa = nuevoNodo;

            ultimoNuevo = nuevoNodo;
            original = original->sig;
        }

        cabeza = nuevoMapa;
    }

    cout << "Total removidos: " << totalRemovidos << endl;
    return 0;
}