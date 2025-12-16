#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

unordered_map<string, vector<string>> graph;
unordered_map<string, unordered_map<string, long long>> memo;

long long count_paths(const string& src, const string& dst) {
    if (src == dst) return 1;
    if (memo[src].count(dst)) return memo[src][dst];

    long long total = 0;
    if (graph.count(src)) {
        for (const string& neighbor : graph[src]) {
            total += count_paths(neighbor, dst);
        }
    }
    return memo[src][dst] = total;
}

int main() {
    ifstream in("input.txt");
    if (!in) {
        cerr << "No se pudo abrir input.txt\n";
        return 1;
    }

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        size_t colon = line.find(':');
        string from = line.substr(0, colon);
        istringstream iss(line.substr(colon + 2));

        string to;
        while (iss >> to) {
            graph[from].push_back(to);
        }
    }

    long long result =
          count_paths("svr", "dac") * count_paths("dac", "fft") * count_paths("fft", "out")
        + count_paths("svr", "fft") * count_paths("fft", "dac") * count_paths("dac", "out");

    cout << result << endl;
    return 0;
}
