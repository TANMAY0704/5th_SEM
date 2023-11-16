#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // Add this line for INT_MAX
using namespace std;



void dfs(int node, int min_width, int n, vector<vector<int>>& W, int& ans) {
    if (node == n - 1) {  // Reached the destination pond
        ans = max(ans, min_width);
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (W[node][i] > 0) {  // There is a channel
            int new_min_width = min(min_width, W[node][i]);
            dfs(i, new_min_width, n, W, ans);
        }
    }
}

int largestAlligator(int n, vector<vector<int>>& W) {
    int ans = 0;
    dfs(0, INT_MAX, n, W, ans);
    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> W(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> W[i][j];

    cout << largestAlligator(n, W);
    return 0;
}
