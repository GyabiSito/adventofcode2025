#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <sstream>
#include <climits>
#include <fstream>

using namespace std;

int min_button_presses(const vector<int>& goal, const vector<vector<int>>& buttons) {
    int m = goal.size();
    int n = buttons.size();
    int min_presses = INT_MAX;

    for (int mask = 0; mask < (1 << n); ++mask) {
        vector<int> state(m, 0);
        int press_count = 0;

        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                press_count++;
                for (int j : buttons[i]) {
                    state[j] ^= 1;
                }
            }
        }

        if (state == goal) {
            min_presses = min(min_presses, press_count);
        }
    }

    return min_presses;
}

vector<int> parse_goal(const string& line) {
    size_t start = line.find('[');
    size_t end = line.find(']');
    vector<int> res;
    if (start == string::npos || end == string::npos) return res;

    string inside = line.substr(start + 1, end - start - 1);
    for (char c : inside) {
        if (c == '#') res.push_back(1);
        else if (c == '.') res.push_back(0);
    }
    return res;
}

vector<vector<int>> parse_buttons(const string& line) {
    vector<vector<int>> buttons;
    size_t pos = 0;
    while ((pos = line.find('(', pos)) != string::npos) {
        size_t end = line.find(')', pos);
        if (end == string::npos) break;

        string group = line.substr(pos + 1, end - pos - 1);
        stringstream ss(group);
        string num;
        vector<int> btn;

        while (getline(ss, num, ',')) {
            if (!num.empty()) {
                btn.push_back(stoi(num));
            }
        }

        buttons.push_back(btn);
        pos = end + 1;
    }

    return buttons;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo input.txt" << endl;
        return 1;
    }

    string line;
    int total = 0;
    int maquina = 1;

    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<int> goal = parse_goal(line);
        vector<vector<int>> buttons = parse_buttons(line);

        if (goal.empty() || buttons.empty()) {
            continue;
        }

        int presses = min_button_presses(goal, buttons);
        total += presses;

    }

    cout  << total << endl;

    file.close();
    return 0;
}
