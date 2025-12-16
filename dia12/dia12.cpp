#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("input.txt");
    if (!in) {
        cerr << "No se pudo abrir input.txt\n";
        return 1;
    }

    string content((istreambuf_iterator<char>(in)),
                    istreambuf_iterator<char>());

    vector<string> blocks;
    size_t pos = 0;
    while (true) {
        size_t next = content.find("\n\n", pos);
        if (next == string::npos) {
            blocks.push_back(content.substr(pos));
            break;
        }
        blocks.push_back(content.substr(pos, next - pos));
        pos = next + 2;
    }

    istringstream regions(blocks.back());
    string line;
    long long total = 0;

    while (getline(regions, line)) {
        if (line.empty()) continue;

        vector<int> nums;
        int cur = 0;
        bool in_num = false;
        for (char c : line) {
            if (isdigit(c)) {
                cur = cur * 10 + (c - '0');
                in_num = true;
            } else if (in_num) {
                nums.push_back(cur);
                cur = 0;
                in_num = false;
            }
        }
        if (in_num) nums.push_back(cur);

        int W = nums[0];
        int H = nums[1];
        int sum = 0;
        for (int i = 2; i < (int)nums.size(); i++)
            sum += nums[i];

        if ((W / 3) * (H / 3) >= sum)
            total++;
    }

    cout << total << "\n";
    return 0;
}
