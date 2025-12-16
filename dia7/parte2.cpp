#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "No se pudo abrir input.txt\n";
        return 1;
    }

    vector<string> grid;
    string line;
    while (getline(file, line)) {
        grid.push_back(line);
    }

    int filas = grid.size();
    int columnas = grid[0].size();

    int startRow = -1, startCol = -1;

    // Buscar S
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (grid[i][j] == 'S') {
                startRow = i;
                startCol = j;
                break;
            }
        }
        if (startRow != -1) break;
    }

    if (startRow == -1) {
        cerr << "No se encontro S\n";
        return 1;
    }

    vector<vector<long long>> dp(filas, vector<long long>(columnas, 0));

    dp[startRow][startCol] = 1;

    // Simulación lógica
    for (int i = startRow; i < filas - 1; i++) {
        for (int j = 0; j < columnas; j++) {
            if (dp[i][j] == 0) continue;

            if (grid[i][j] == '.' || grid[i][j] == 'S') {
                dp[i + 1][j] += dp[i][j];
            }
            else if (grid[i][j] == '^') {
                if (j - 1 >= 0)
                    dp[i + 1][j - 1] += dp[i][j];
                if (j + 1 < columnas)
                    dp[i + 1][j + 1] += dp[i][j];
            }
        }
    }

    long long resultado = 0;
    for (int j = 0; j < columnas; j++) {
        resultado += dp[filas - 1][j];
    }

    cout << "Total de timelines: " << resultado << endl;

    return 0;
}
