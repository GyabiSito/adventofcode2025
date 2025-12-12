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
int contarVecinos(Lista prev, Lista cur, Lista next, int col)
{
    int total = 0;

    // listas disponibles: prev, cur, next
    // cada una puede ser NULL (bordes)

    Lista filas[3] = {prev, cur, next};
    int filasIndex[3] = {-1, 0, 1}; // -1 fila arriba, 0 actual, +1 abajo

    for (int f = 0; f < 3; f++)
    {
        if (filas[f] == NULL)
            continue;

        for (int dc = -1; dc <= 1; dc++)
        {

            if (filasIndex[f] == 0 && dc == 0)
                continue; // no contar a sí mismo

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

int main()
{
    ifstream file("input.txt");

    // Mantener 3 punteros:
    Lista prev = NULL;            // fila anterior
    Lista cur = leerLinea(file);  // fila actual
    Lista next = leerLinea(file); // fila siguiente
    int total = 0;
    while (cur != NULL)
    {

        Lista resultado = crearLista();

        for (int col = 0; col < cur->total; col++)
        {

            nodoLista nodoActual = getNodo(cur, col);

            if (nodoActual->valor == '@')
            {
                int vecinos = contarVecinos(prev, cur, next, col);

                if (vecinos < 4)
                {

                    insertarFinal(resultado, 'x');
                    total++;
                }

                else
                    insertarFinal(resultado, '@');
            }
            else
            {
                insertarFinal(resultado, nodoActual->valor); // .
            }
        }

        nodoLista aux = resultado->lista;
        while (aux != NULL)
        {
            aux = aux->sig;
        }
        prev = cur;
        cur = next;
        next = leerLinea(file);
    }
    cout << total;

    return 0;
}