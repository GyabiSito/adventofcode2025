#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

struct tile
{
    long long x, y;
    tile *sig;
} typedef *Lista;

void insertar(Lista &L, long long x, long long y)
{
    tile *nuevo = new tile;
    nuevo->x = x;
    nuevo->y = y;
    nuevo->sig = NULL;

    if (L == NULL)
    {
        L = nuevo;
    }
    else
    {
        tile *aux = L;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
}

int main()
{
    ifstream file("input.txt");
    if (!file.is_open())
    {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    string linea;
    Lista L = NULL;

    // Leer archivo y guardar puntos
    while (getline(file, linea))
    {
        if (linea.empty())
            continue;

        int coma = linea.find(',');
        if (coma != string::npos)
        {
            long long x = stoll(linea.substr(0, coma));
            long long y = stoll(linea.substr(coma + 1));
            insertar(L, x, y);
        }
    }

    file.close();


    long long maxArea = 0;
    Lista a = L;
    while (a != NULL)
    {
        Lista b = a->sig;
        while (b != NULL)
        {
            long long x1 = a->x;
            long long y1 = a->y;
            long long x2 = b->x;
            long long y2 = b->y;

            long long width = abs(x1 - x2) + 1; //el +1 para contar tambien LOS BORDES
            long long height = abs(y1 - y2) + 1;

            if (width > 1 && height > 1)
            {
                long long area = width * height;
                if (area > maxArea)
                {
                    maxArea = area;
                }
            }

            b = b->sig;
        }
        a = a->sig;
    }

    cout << maxArea << endl;


    while (L != NULL)
    {
        Lista aux = L;
        L = L->sig;
        delete aux;
    }

    return 0;
}
