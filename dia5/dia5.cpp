#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstring>
using namespace std;

struct Rango
{
    long long desde;
    long long hasta;
};
struct nodoRango
{
    Rango valor;
    nodoRango *sig;
    nodoRango *ant;
};
struct listaRango
{
    int total;
    nodoRango *lista;
};
typedef listaRango *ListaRango;

ListaRango crearListaRango()
{
    ListaRango L = new listaRango;
    L->total = 0;
    L->lista = NULL;
    return L;
}

void insertarRango(ListaRango L, Rango r)
{
    nodoRango *nuevo = new nodoRango;
    nuevo->valor = r;
    nuevo->sig = NULL;
    nuevo->ant = NULL;

    if (L->lista == NULL)
    {
        L->lista = nuevo;
    }
    else
    {
        nodoRango *aux = L->lista;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
        nuevo->ant = aux;
    }
    L->total++;
}

struct nodoInt
{
    long long valor;
    nodoInt *sig;
    nodoInt *ant;
};
struct listaInt
{
    int total;
    nodoInt *lista;
};
typedef listaInt *ListaInt;

ListaInt crearListaInt()
{
    ListaInt L = new listaInt;
    L->total = 0;
    L->lista = NULL;
    return L;
}

void insertarInt(ListaInt L, long long v)
{
    nodoInt *nuevo = new nodoInt;
    nuevo->valor = v;
    nuevo->sig = NULL;
    nuevo->ant = NULL;

    if (L->lista == NULL)
    {
        L->lista = nuevo;
    }
    else
    {
        nodoInt *aux = L->lista;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
        nuevo->ant = aux;
    }
    L->total++;
}
Rango separarRango(const string &linea)
{
    Rango r;
    r.desde = 0;
    r.hasta = 0;
    bool enHasta = false;
    for (int i = 0; i < linea.size(); i++)
    {
        if (linea[i] == '-')
        {
            enHasta = true;
            continue;
        }
        if (isdigit(linea[i]))
        {
            if (!enHasta)
                r.desde = r.desde * 10 + (linea[i] - '0');
            else
                r.hasta = r.hasta * 10 + (linea[i] - '0');
        }
    }
    return r;
}
bool esFresco(long long id, ListaRango rangos)
{
    nodoRango *actual = rangos->lista;
    while (actual != NULL)
    {
        if (id >= actual->valor.desde && id <= actual->valor.hasta)
            return true;
        actual = actual->sig;
    }
    return false;
}

int main()
{
    ifstream file("input.txt");
    if (!file.is_open())
    {
        return 0;
    }

    ListaRango rangos = crearListaRango();
    ListaInt ids = crearListaInt();

    string linea;
    bool leyendoRangos = true;

    while (getline(file, linea))
    {
        if (linea.empty())
        {
            leyendoRangos = false;
            continue;
        }

        if (leyendoRangos)
        {
            Rango r = separarRango(linea);
            insertarRango(rangos, r);
        }
        else
        {
            long long id = stoll(linea);
            insertarInt(ids, id);
        }
    }

    // ordenar los rangos por 'desde'
    ListaRango rangosOrdenados = crearListaRango();
    nodoRango *r = rangos->lista;
    while (r != NULL)
    {
        // Inserción ordenada
        Rango nuevo = r->valor;
        nodoRango *actual = rangosOrdenados->lista;
        nodoRango *anterior = NULL;

        nodoRango *nuevoNodo = new nodoRango;
        nuevoNodo->valor = nuevo;
        nuevoNodo->sig = NULL;
        nuevoNodo->ant = NULL;

        while (actual != NULL && actual->valor.desde < nuevo.desde)
        {
            anterior = actual;
            actual = actual->sig;
        }

        if (anterior == NULL)
        {
            // insertar al inicio
            nuevoNodo->sig = rangosOrdenados->lista;
            if (rangosOrdenados->lista != NULL)
                rangosOrdenados->lista->ant = nuevoNodo;
            rangosOrdenados->lista = nuevoNodo;
        }
        else
        {
            nuevoNodo->sig = anterior->sig;
            if (anterior->sig != NULL)
                anterior->sig->ant = nuevoNodo;
            anterior->sig = nuevoNodo;
            nuevoNodo->ant = anterior;
        }

        rangosOrdenados->total++;
        r = r->sig;
    }

    // mergear rangos
    ListaRango rangosFinales = crearListaRango();
    nodoRango *it = rangosOrdenados->lista;
    while (it != NULL)
    {
        Rango actual = it->valor;
        it = it->sig;

        while (it != NULL && it->valor.desde <= actual.hasta + 1)
        {
            actual.hasta = max(actual.hasta, it->valor.hasta);
            it = it->sig;
        }

        insertarRango(rangosFinales, actual);
    }

    //  sumar cantidad total de IDs frescos
    long long totalFrescos = 0;
    nodoRango *final = rangosFinales->lista;
    while (final != NULL)
    {
        totalFrescos += (final->valor.hasta - final->valor.desde + 1);
        final = final->sig;
    }

    cout << totalFrescos << endl;

    // int frescos = 0;
    // nodoInt *actual = ids->lista;
    // while (actual != NULL)
    // {
    //     if (esFresco(actual->valor, rangos))
    //         frescos++;
    //     actual = actual->sig;
    // }

    // cout << frescos << endl;
    return 0;
}
