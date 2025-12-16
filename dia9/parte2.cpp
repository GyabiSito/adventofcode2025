#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

struct Edge {
    long long x1, y1, x2, y2;
};

pair<long long, long long> sort_pair(long long a, long long b) {
    return (a < b) ? make_pair(a, b) : make_pair(b, a);
}

long long abs64(long long a) {
    return a < 0 ? -a : a;
}

long long rectangle_area(long long x1, long long y1, long long x2, long long y2) {
    return (abs64(x2 - x1) + 1) * (abs64(y2 - y1) + 1);
}

long long manhattan_distance(const pair<long long, long long>& a, const pair<long long, long long>& b) {
    return abs64(a.first - b.first) + abs64(a.second - b.second);
}

bool intersects(const vector<Edge>& edges, long long minX, long long minY, long long maxX, long long maxY) {
    for (const auto& e : edges) {
        auto [iMinX, iMaxX] = sort_pair(e.x1, e.x2);
        auto [iMinY, iMaxY] = sort_pair(e.y1, e.y2);
        if (minX < iMaxX && maxX > iMinX && minY < iMaxY && maxY > iMinY) {
            return true;
        }
    }
    return false;
}

long long execute_part2(const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error opening file: " << fileName << endl;
        return 0;
    }

    vector<pair<long long, long long>> redTiles;
    vector<Edge> edges;
    vector<string> lines;
    string line;

    while (getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    file.close();

    if (lines.empty()) return 0;

    auto split = [](const string& s) -> pair<long long, long long> {
        stringstream ss(s);
        string xStr, yStr;
        getline(ss, xStr, ',');
        getline(ss, yStr);
        return {stoll(xStr), stoll(yStr)};
    };

    auto [initX, initY] = split(lines[0]);
    auto [lastX, lastY] = split(lines.back());

    for (size_t i = 0; i < lines.size() - 1; ++i) {
        auto [fX, fY] = split(lines[i]);
        auto [tX, tY] = split(lines[i + 1]);
        edges.push_back({fX, fY, tX, tY});
        redTiles.emplace_back(fX, fY);
        redTiles.emplace_back(tX, tY);
    }

    // Close polygon
    edges.push_back({initX, initY, lastX, lastY});

    long long result = 0;

    for (size_t i = 0; i < redTiles.size() - 1; ++i) {
        for (size_t j = i + 1; j < redTiles.size(); ++j) {
            const auto& from = redTiles[i];
            const auto& to = redTiles[j];

            auto [minX, maxX] = sort_pair(from.first, to.first);
            auto [minY, maxY] = sort_pair(from.second, to.second);

            long long mDist = manhattan_distance(from, to);

            if (mDist * mDist > result) {
                if (!intersects(edges, minX, minY, maxX, maxY)) {
                    long long area = rectangle_area(from.first, from.second, to.first, to.second);
                    if (area > result) {
                        result = area;
                    }
                }
            }
        }
    }

    return result;
}

int main() {
    string fileName = "./input.txt";  // o "./day09/test_input_09.txt"
    long long maxRect = execute_part2(fileName);
    cout << "Max rectangle area: " << maxRect << endl;
    return 0;
}
