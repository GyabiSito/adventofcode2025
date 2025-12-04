#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

int getMaxJoltage(const string& linea) {
    int maxJoltage = 0;

    for (size_t i = 0; i < linea.size(); ++i) {
        for (size_t j = i + 1; j < linea.size(); ++j) {
            int a = linea[i] - '0';
            int b = linea[j] - '0';
            int valor = a * 10 + b; //la misma soronga que hice antes, en vez de hacer un stoi (pq se puede romper), traducirlo de ASCII

            maxJoltage = max(maxJoltage, valor);
        }
    }

    return maxJoltage;
}

int main() {
    ifstream file("input.txt");
    string linea;
    int total = 0;

    while (getline(file, linea)) {
        if (!linea.empty()) {
            total += getMaxJoltage(linea);
        }
    }

    cout << "Total: " << total << endl;
    return 0;
}
