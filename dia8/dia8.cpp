#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

using namespace std;

struct Caja
{
    double x, y, z;
};

struct Conexion
{
    int a, b;
    double distancia;
};

struct nodo
{
    int valor;
    nodo *sig;
};
typedef nodo *Lista;

struct Estructura
{
    Caja *cajas;
    Conexion *conexiones;
    Lista *listas;
    int cantidadCajas;
    int cantidadConexiones;
};

struct nodoArbol
{
    nodoArbol *padre;
    int idCaja;
} typedef *Arbol;

Estructura *crearEstructura()
{
    Estructura *e = new Estructura;
    e->cajas = NULL;
    e->conexiones = NULL;
    e->listas = NULL;
    e->cantidadCajas = 0;
    e->cantidadConexiones = 0;
    return e;
}

Arbol buscarPadre(Arbol a)
{
    if (a->padre == a)
        return a;
    a->padre = buscarPadre(a->padre);
    return a->padre;
}

void insertarvalor(Lista &L, int valor)
{
    nodo *nuevo = new nodo{valor, NULL};
    if (!L)
    {
        L = nuevo;
        return;
    }

    nodo *aux = L;
    while (aux->sig)
        aux = aux->sig;
    aux->sig = nuevo;
}

// void unirArboles(Arbol *bosque, int a, int b)
// {
//     Arbol rootA = buscarPadre(bosque[a]);
//     Arbol rootB = buscarPadre(bosque[b]);
//     if (rootA != rootB)
//     {
//         rootB->padre = rootA;
//     }
// }

bool unirArboles(Arbol *bosque, int a, int b)
{
    Arbol rootA = buscarPadre(bosque[a]);
    Arbol rootB = buscarPadre(bosque[b]);
    if (rootA != rootB)
    {
        rootB->padre = rootA;
        return true;
    }
    return false;
}

void unirListas(Lista &A, Lista &B)
{
    if (A == NULL)
    {
        A = B;
        B = NULL;
        return;
    }

    nodo *aux = A;
    while (aux->sig != NULL)
    {
        aux = aux->sig;
    }

    aux->sig = B;
    B = NULL;
}
double calcularDistancia(Caja *a, Caja *b)
{
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    double dz = a->z - b->z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

double contarCajas(const string &path)
{
    ifstream file(path);
    if (!file.is_open())
        return 0;

    double contador = 0;
    string linea;
    while (getline(file, linea))
    {
        if (!linea.empty())
            contador++;
    }
    file.close();
    return contador;
}

Caja *parsearCaja(const char *texto)
{
    Caja *r = new Caja; // ahora sí, reservamos memoria
    int i = 0, numero = 0, campo = 0;

    while (texto[i] != '\0' && texto[i] != '\n')
    {
        if (texto[i] == ',')
        {
            if (campo == 0)
                r->x = numero;
            else if (campo == 1)
                r->y = numero;

            campo++;
            numero = 0;
        }
        else
        {
            numero = numero * 10 + (texto[i] - '0');
        }
        i++;
    }
    r->z = numero;
    return r;
}
void ordenarConexionesPorDistancia(Conexion *conexiones, int cantidad)
{
    bool ordenado = false;
    int limite = cantidad - 1;

    while (!ordenado)
    {
        // cout << limite << endl;
        ordenado = true;
        for (int i = 0; i < limite; i++)
        {
            if (conexiones[i].distancia > conexiones[i + 1].distancia)
            {
                Conexion temp = conexiones[i];
                conexiones[i] = conexiones[i + 1];
                conexiones[i + 1] = temp;
                ordenado = false;
            }
        }
        limite--; // achicamos el rango
    }
}

bool compararPorDistancia(const Conexion &a, const Conexion &b)
{
    return a.distancia < b.distancia;
}
int main()
{
    ifstream file("input.txt");
    if (!file.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    int totalCajas = contarCajas("input.txt");

    Estructura *e = crearEstructura();
    e->cajas = new Caja[totalCajas];
    e->listas = new Lista[totalCajas];

    Arbol *bosque = new Arbol[totalCajas];
    for (int i = 0; i < totalCajas; i++)
    {
        e->listas[i] = nullptr;
        bosque[i] = new nodoArbol;
        bosque[i]->idCaja = i;
        bosque[i]->padre = bosque[i]; // cada uno es su propio padre al principio
    }

    string linea;
    int i = 0;

    while (getline(file, linea))
    {
        Caja *c = parsearCaja(linea.c_str());
        e->cajas[i] = *c;
        delete c;
        // cout << "Caja: x=" << e->cajas[i].x << " y=" << e->cajas[i].y << " z=" << e->cajas[i].z << endl;
        i++;
        e->cantidadCajas++;
    }
    file.close();

    e->cantidadConexiones = 0;
    int n = e->cantidadCajas;
    e->conexiones = new Conexion[n * (n - 1) / 2];

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            Conexion con;
            con.a = i;
            con.b = j;
            con.distancia = calcularDistancia(&e->cajas[i], &e->cajas[j]);
            e->conexiones[e->cantidadConexiones++] = con;
        }
    }
    sort(e->conexiones, e->conexiones + e->cantidadConexiones, compararPorDistancia);
    cout << "asd" << e->cantidadConexiones << endl;
    cout << "asd" << e->cantidadCajas << endl;

    // for (int i = 0; i < e->cantidadCajas; i++)
    // {
    //     cout << "Caja: x=" << e->cajas[i].x << " y=" << e->cajas[i].y << " z=" << e->cajas[i].z << endl;
    // }

    ofstream output("output.txt");

    for (int i = 0; i < e->cantidadConexiones; i++)
    {
        Caja a = e->cajas[e->conexiones[i].a];
        Caja b = e->cajas[e->conexiones[i].b];

        output << "============================================" << "\n";
        output << "ID A: " << e->conexiones[i].a
               << " (" << a.x << ", " << a.y << ", " << a.z << ")" << "\n";
        output << "ID B: " << e->conexiones[i].b
               << " (" << b.x << ", " << b.y << ", " << b.z << ")" << "\n";
        output << "Distancia: " << e->conexiones[i].distancia << "\n";
        output << "============================================" << "\n";
    }
    output.close();

    // int conexionesHechas = 0;
    // int maxConexiones = 1000;

    // for (int i = 0; i < e->cantidadConexiones && conexionesHechas < maxConexiones; i++)
    // {
    //     int a = e->conexiones[i].a;
    //     int b = e->conexiones[i].b;

    //     unirArboles(bosque, a, b);
    //     conexionesHechas++;
    // }

    long long respuestaParte2 = 0;
    int lastA = -1, lastB = -1;
    int componentes = totalCajas; 

    for (int i = 0; i < e->cantidadConexiones; i++)
    {
        int a = e->conexiones[i].a;
        int b = e->conexiones[i].b;

        if (unirArboles(bosque, a, b))
        {
            componentes--;
            lastA = a;
            lastB = b;

            if (componentes == 1)
            {
                long long xa = (long long)e->cajas[lastA].x;
                long long xb = (long long)e->cajas[lastB].x;
                respuestaParte2 = xa * xb;
                break;
            }
        }
    }
    cout << "Parte 2 (X(a)*X(b) de la ultima union): " << respuestaParte2 << endl;

    for (int i = 0; i < totalCajas; i++)
    {
        int raiz = buscarPadre(bosque[i])->idCaja;
        insertarvalor(e->listas[raiz], i);
    }
    ofstream gruposOut("grupos.txt");

    for (int i = 0; i < totalCajas; i++)
    {
        if (e->listas[i] != nullptr)
        {
            int cantidad = 0;
            Lista actual = e->listas[i];
            while (actual != nullptr)
            {
                cantidad++;
                actual = actual->sig;
            }

            gruposOut << "Grupo raíz " << i << " (tamaño " << cantidad << "): ";
            actual = e->listas[i];
            while (actual != nullptr)
            {
                gruposOut << actual->valor << " ";
                actual = actual->sig;
            }
            gruposOut << endl;
        }
    }
    gruposOut.close();

    // cout << buscarPadre(bosque[0])->idCaja << endl;
    // cout << buscarPadre(bosque[500])->idCaja << endl;
    // cout << buscarPadre(bosque[999])->idCaja << endl;

    int *grupoTamanio = new int[totalCajas];
    for (int i = 0; i < totalCajas; i++)
        grupoTamanio[i] = 0;

    for (int i = 0; i < totalCajas; i++)
    {
        int raiz = buscarPadre(bosque[i])->idCaja;
        grupoTamanio[raiz]++;
    }

    // Paso 2: filtrar los tamaños > 0
    int *tamanios = new int[totalCajas];
    int cantidadGrupos = 0;
    for (int i = 0; i < totalCajas; i++)
    {
        if (grupoTamanio[i] > 0)
        {
            tamanios[cantidadGrupos++] = grupoTamanio[i];
        }
    }

    // Paso 3: ordenar de mayor a menor (bubble sort)
    for (int i = 0; i < cantidadGrupos - 1; i++)
    {
        for (int j = 0; j < cantidadGrupos - i - 1; j++)
        {
            if (tamanios[j] < tamanios[j + 1])
            {
                int temp = tamanios[j];
                tamanios[j] = tamanios[j + 1];
                tamanios[j + 1] = temp;
            }
        }
    }

    // Paso 4: multiplicar los 3 más grandes
    int resultado = 1;
    for (int i = 0; i < 3 && i < cantidadGrupos; i++)
    {
        resultado *= tamanios[i];
    }

    // Paso 5: mostrar y guardar en output2.txt
    cout << "Tamanios más grandes: ";
    for (int i = 0; i < 3 && i < cantidadGrupos; i++)
        cout << tamanios[i] << " ";
    cout << "\nResultado final: " << resultado << endl;

    ofstream out2("output2.txt");
    out2 << "Tamanios más grandes: ";
    for (int i = 0; i < 3 && i < cantidadGrupos; i++)
        out2 << tamanios[i] << " ";
    out2 << "\nResultado final: " << resultado << "\n";
    out2.close();

    // Liberar memoria
    delete[] grupoTamanio;
    delete[] tamanios;
}
