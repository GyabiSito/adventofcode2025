/*
El dial empieza en 50

50 + L1 => 49
50 + R1 => 51

Si estás en 0 y girás 1 a la izquierda => quedás en 99

Si estás en 99 y girás 1 a la derecha => quedás en 0

0 + 1L => 99
99 + 1R => 0

0 <= dial <= 99

=================
La contraseña es: la cantidad de veces que el dial termina en 0 luego de una rotación.
=================

Empieza en 50

L68 → 82

L30 → 52

========R48 → 0 X========

L5 → 95

R60 → 55

========L55 → 0========

L1 → 99

========L99 → 0========

R14 → 14

L82 → 32


sumatoria=50
R30
sumatoria=80
L25
sumatoria=55

*/

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

struct direccion
{
    int pasos;
    bool derecha;
};

Lista crearLista()
{
    Lista L = new l;
    L->posicion = 50;
    L->lista = new nodo;
    L->total = 0;
    nodoLista aux = L->lista;
    for (int i = 0; i < 100; i++)
    {
        aux->valor = i;
        if (i < 99)
        {
            aux->sig = new nodo;
            aux->sig->ant = aux;
            aux = aux->sig;
        }
    }
    aux->sig = L->lista;
    L->lista->ant = aux;

    return L;
}

nodoLista moverseADireccion(Lista L, int pasos)
{
    int direccion = L->posicion;
    nodoLista aux = L->lista;
    while (aux->valor != L->posicion)
    {
        aux = aux->sig;
    }
    return aux;
}

// Lista recorrer(Lista L, int pasos, bool direccion)
// {
//     nodoLista aux = L->lista;
//     if (direccion)
//     {
//         // derecha
//         // me tengo que mover A L->posicion
//         aux = moverseADireccion(L, L->posicion);
//         while (pasos > 0)
//         {
//             aux = aux->sig;

            
//             pasos--;
//         }
//     }
//     else
//     {
//         aux = moverseADireccion(L, L->posicion);
//         while (pasos > 0)
//         {
//             aux = aux->ant;
//             pasos--;
//         }
//     }
//     cout << "===================================" << endl;
//     cout << "Mi total es:" << L->total << endl;
//     cout << "Mi posicion actual es:" << L->posicion << endl;
//     cout << "===================================" << endl;
//     L->posicion = aux->valor;
//     cout << "------------------------------------" << endl;
//     cout << "Mi posicion cambiada es:" << L->posicion << endl;
//     cout << "Mi total cambaiado es:" << L->total << endl;
//     cout << "------------------------------------" << endl;
//     if (L->posicion == 0)
//     {
//         L->total += 1;
//     }
//     return L;
// }

//Parte 2
Lista recorrer(Lista L, int pasos, bool direccion)
{
    nodoLista aux = moverseADireccion(L, L->posicion);

    while (pasos > 0)
    {
        aux = direccion ? aux->sig : aux->ant;

        if (aux->valor == 0)
        {
            L->total += 1;
        }

        pasos--;
    }

    L->posicion = aux->valor;

    return L;
}


void imprimir_todo(Lista L)
{
    nodoLista aux = L->lista;
    int inicio = aux->valor;
    do
    {
        cout << aux->valor << endl;
        aux = aux->sig;
    } while (aux->valor != inicio);
}

direccion leer_input(char *chars)
{
    /* Recibo algo como:
        R21
        R37
        L39
        L11
     */

    // Tengo que devolver: 1 si es R, y el valor
    direccion d;
    d.derecha = (chars[0] == 'R' || chars[0] == 'r');
    d.pasos = atoi(chars + 1);

    return d;
}

int main()
{
    Lista L = crearLista();
    // imprimir_todo(L);
    cout << "Mi posicion es " << L->posicion << endl;

    FILE *archivo = fopen("input.txt", "r");
    if (archivo == NULL)
    {
        cerr << "No se pudo abrir el archivo" << endl;
        return 1;
    }
    char linea[100];
    while (fgets(linea, sizeof(linea), archivo))
    {
        linea[strcspn(linea, "\r\n")] = 0;

        if (strlen(linea) == 0)
            continue;

        direccion d = leer_input(linea);

        cout << (d.derecha ? "Derecha" : "Izquierda") << " - " << d.pasos << endl;

        recorrer(L, d.pasos, d.derecha);
    }

    fclose(archivo);

    cout << "El total final es:" << L->total << endl;
    return 0;
}