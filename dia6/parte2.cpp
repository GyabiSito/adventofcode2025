#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> grid[4]; 
    string operadores;

    // Leer archivo
    ifstream file("input.txt");
    if (!file.is_open())
    {
        cerr << "No se pudo abrir input.txt\n";
        return 1;
    }

    string line;
    int fila = 0;
    while (getline(file, line))
    {
        if (fila < 4)
        {
            for (char c : line)
                grid[fila].push_back(string(1, c)); 
        }
        else
        {
            operadores = line;
        }
        fila++;
    }
    file.close();

    int columnas = grid[0].size();
    int start_col = 0;
    long long total = 0;

    for (int col = 0; col <= columnas; col++)
    {
        bool esColumnaVacia = true;
        if (col < columnas)
        {
            for (int r = 0; r < 4; r++)
            {
                if (grid[r][col] != " ")
                {
                    esColumnaVacia = false;
                    break;
                }
            }
        }

        if (esColumnaVacia)
        {

            if (start_col >= operadores.size())
                break; 
            char op = operadores[start_col]; 

            long long parcial = (op == '*') ? 1 : 0;

            for (int c = start_col; c < col; c++)
            {
                string numStr = "";
                for (int r = 0; r < 4; r++)
                {
                    if (grid[r][c] != " ")
                        numStr += grid[r][c];
                }
                if (!numStr.empty())
                {
                    long long n = stoll(numStr);
                    if (op == '+')
                        parcial += n;
                    else
                        parcial *= n;
                }
            }

            total += parcial;
            start_col = col + 1; 
        }
    }

    cout << "Resultado total: " << total << "\n";
    return 0;
}
