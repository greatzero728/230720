#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <cassert>

using namespace std;

#define pb push_back
#define mp make_pair
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define foreach(e, x) for (__typeof(x.begin()) e = x.begin(); e != x.end(); ++e)
typedef long long LL;
typedef pair<int, int> PII;

char s[30][30], ss[30][30], t[10][10], tmp[10][10];
bool vis[30][30];
int n, m;
string x;

void doReverse() {
    REP(i, 10) reverse(t[i], t[i] + 10);
}

void doRotate() {
    REP(i, 10) REP(j, 10) tmp[j][9 - i] = t[i][j];
    REP(i, 10) REP(j, 10) t[i][j] = tmp[i][j];
}

int cnt;
bool flag;

void dfs(int i, int j) {
    ++cnt;
    vis[i][j] = true;
    if (i == 0 || i == 29 || j == 0 || j == 29) flag = false;
    if (i > 0 && !vis[i - 1][j]) dfs(i - 1, j);
    if (i < 29 && !vis[i + 1][j]) dfs(i + 1, j);
    if (j > 0 && !vis[i][j - 1]) dfs(i, j - 1);
    if (j < 29 && !vis[i][j + 1]) dfs(i, j + 1);
}

int solve(int y, int x) {
    REP(i, 10) REP(j, 10) if (t[i][j] == '*' && s[y + i][x + j] == '*')
        return 0;
    REP(i, 30) REP(j, 30) ss[i][j] = s[i][j];
    REP(i, 10) REP(j, 10) if (t[i][j] == '*')
        ss[y + i][x + j] = '*';
    REP(i, 30) REP(j, 30) vis[i][j] = ss[i][j] == '*';
    int ret = 0;
    REP(i, 30) REP(j, 30) if (!vis[i][j]) {
        cnt = 0;
        flag = true;
        dfs(i, j);
        if (flag) ret = max(ret, cnt);
    }
    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#else
    freopen("cage.in", "r", stdin);
    freopen("cage.out", "w", stdout);
#endif
	
    ios_base::sync_with_stdio(false);
    REP(i, 30) REP(j, 30) s[i][j] = '.';
    REP(i, 10) REP(j, 10) t[i][j] = '.';
    cin >> n >> m;
    REP(i, n) {
        cin >> x;
        REP(j, m) s[10 + i][10 + j] = x[j];
    }
    cin >> n >> m;
    REP(i, n) {
        cin >> x;
        REP(j, m) t[i][j] = x[j];
    }
    int ans = 0;
    REP(x, 2) {
        REP(y, 4) {
            REP(i, 21) REP(j, 21)
                ans = max(ans, solve(i, j));
            doRotate();
        }
        doReverse();
    }
    cout << ans << '\n';
    return 0;
}
