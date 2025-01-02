#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
class SegmentTree {
    vector<int> tree, lazy;
public:
    SegmentTree(int size) {
        tree.resize(size * 4);
        lazy.resize(size * 4);
    }
    void update(int node, int start, int end, int l, int r, int value) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        if (start > end || start > r || end < l) return;
        if (start >= l && end <= r) {
            tree[node] += value;
            if (start != end) {
                lazy[node * 2] += value;
                lazy[node * 2 + 1] += value;
            }
            return;
        }
        int mid = (start + end) / 2;
        update(node * 2, start, mid, l, r, value);
        update(node * 2 + 1, mid + 1, end, l, r, value);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }
    int query(int node, int start, int end, int l, int r) {
        if (start > end || start > r || end < l) return 0;
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        if (start >= l && end <= r) return tree[node];
        int mid = (start + end) / 2;
        int q1 = query(node * 2, start, mid, l, r);
        int q2 = query(node * 2 + 1, mid + 1, end, l, r);
        return max(q1, q2);
    }
};
int solve(int N, vector<vector<int>>& grid) {
    vector<int> minX(10, N), minY(10, N), maxX(10, -1), maxY(10, -1);
    unordered_set<int> visibleColors;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int color = grid[i][j];
            if (color > 0) {
                visibleColors.insert(color);
                minX[color] = min(minX[color], i);
                minY[color] = min(minY[color], j);
                maxX[color] = max(maxX[color], i);
                maxY[color] = max(maxY[color], j);
            }
        }
    }
    vector<bool> canBeFirst(10, true);
    for (int color : visibleColors) {
        for (int i = minX[color]; i <= maxX[color]; ++i) {
            for (int j = minY[color]; j <= maxY[color]; ++j) {
                int overlappingColor = grid[i][j];
                if (overlappingColor != color) {
                    canBeFirst[overlappingColor] = false;
                }
            }
        }
    }
    int firstColors = 0;
    for (int color : visibleColors) {
        if (canBeFirst[color]) {
            ++firstColors;
        }
    }
    return firstColors;
}
int main() {
    ifstream inFile("art.in");
    ofstream outFile("art.out");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    inFile >> N;
    vector<vector<int>> grid(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        string line;
        inFile >> line;
        for (int j = 0; j < N; ++j) {
            grid[i][j] = line[j] - '0';
        }
    }
    outFile << solve(N, grid) << "\n";
    return 0;
}