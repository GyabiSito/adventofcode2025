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

Rango separarRango(char *texto)
{
    Rango r;
    r.desde = 0;
    r.hasta = 0;
    bool enHasta = false;
    for (int i = 0; texto[i] != '\0'; i++)
    {
        if (texto[i] == '-')
        {
            enHasta = true;
            continue;
        }
        if (isdigit(texto[i]))
        {
            if (!enHasta)
                /*
                En vez de usar stoi (porque la longitud de algunos numeros lo rompe) se traduce de esta manera, usando ASCII
                Iteración 1:
                texto[0] = '1'
                '1' - '0' = 1
                numero = 0 * 10 + 1 = 1

                Iteración 2:
                texto[1] = '9'
                '9' - '0' = 9
                numero = 1 * 10 + 9 = 19

                Iteración 3:
                texto[2] = '7'
                '7' - '0' = 7
                numero = 19 * 10 + 7 = 197
                */
               //El *10 esta para mantener el caracter a caracter, porque sino se sumaria solamente
                r.desde = r.desde * 10 + (texto[i] - '0');
            else
                r.hasta = r.hasta * 10 + (texto[i] - '0');
        }
    }
    return r;
}

bool esInvalido(long long numero)
{
    string s = to_string(numero);
    if (s.length() % 2 != 0)
        return false;

    int mitad = s.length() / 2;
    string p1 = s.substr(0, mitad);
    string p2 = s.substr(mitad);
    return p1 == p2;
}

int main()
{
    FILE *archivo = fopen("input.txt", "r");
    if (!archivo)
    {
        return 0;
    }

    char buffer[100000];
    fgets(buffer, sizeof(buffer), archivo);
    fclose(archivo);

    // caracteres basura de los txt
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == '\r' || buffer[i] == '\n')
        {
            buffer[i] = '\0';
            break;
        }
    }

    char *token = strtok(buffer, ",");
    long long total = 0;

    while (token != NULL)
    {
        Rango r = separarRango(token);
        for (long long i = r.desde; i <= r.hasta; i++)
        {
            if (esInvalido(i))
            {
                cout << "Invalido: " << i << endl;
                total += i;
            }
        }
        token = strtok(NULL, ",");
    }

    cout << "\nTotal Final: " << total << endl;
    return 0;
}