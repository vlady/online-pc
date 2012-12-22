// Foarte faina problema.
#include <cstdio>
#include <vector>
#include <string.h>
#include <assert.h>

using namespace std;
int N;
int C[100007];
int ciclu[100007];
int stack[100007];
bool visited[100007];
vector<vector<int> > G;

int gasit = 0;
void dfs(int nod, int parent) {
  visited[nod] = true;
  stack[++stack[0]] = nod;
  for (int i = 0; i < G[nod].size(); ++i) {
    int nod2 = G[nod][i];
    if (nod2 == parent) continue;
    if (visited[nod2]) {
      gasit = nod2;
      return;
    }
    dfs(nod2, nod);
    if (gasit) return;
  }
  --stack[0];
}
int    dp[100007][2];
bool memo[100007][2];

int dp2[100007][2];
int na, nb;
int nxt(int poz) {
  poz++;
  while (poz > ciclu[0]) poz -= ciclu[0];
  return poz;
}
int valid(int poz) {
  if (poz >= na && poz <= nb) return 0;
  return 1;
}
int solve2(int poz, int lst) {
  while (poz > ciclu[0]) poz -= ciclu[0];
  if (poz == na) {
    if (lst) return 0;
    return dp[poz][1];
  }
  if (dp2[poz][lst]) return dp2[poz][lst] - 1;
  if (lst == 0) dp2[poz][lst] = solve2(nxt(poz), 1) + dp[ciclu[poz]][1];
  else dp2[poz][lst] = min(solve2(nxt(poz), 1) + dp[ciclu[poz]][1], solve2(nxt(poz), 0)
    + dp[ciclu[poz]][0]);
  dp2[poz][lst] += 1;
  return dp2[poz][lst] - 1;
}

int solve1(int nod, int parent, int forced) {
  if (memo[nod][forced]) return dp[nod][forced];
  dp[nod][forced] = 0; memo[nod][forced] = true;
  int fortat = C[nod];
  int nefortat = 0;
  for (int i = 0; i < G[nod].size(); ++i) {
    int nod2 = G[nod][i];
    if (nod2 == parent || visited[nod2]) continue;
    nefortat += solve1(nod2, nod, 1);
    fortat += solve1(nod2, nod, 0);
  }
  dp[nod][forced] = fortat;
  if (forced == 0 && nefortat < fortat) dp[nod][forced] = nefortat;
  return dp[nod][forced];
}
int main() {
  freopen("mvc.in", "r", stdin);
  freopen("mvc.out", "w", stdout);

  scanf("%d", &N);
  G.resize(N + 1);
  for (int i = 1; i <= N; ++i) scanf("%d", &C[i]);
  for (int i = 1; i <= N; ++i) {
    int a, b; scanf("%d %d", &a, &b);
    G[a].push_back(b);
    G[b].push_back(a);
  }
  assert(N > 2);
  // DFS
  gasit = 0;
  dfs(1, -1);
  memset(visited, 0, sizeof(visited));
  for (int i = 1; i <= stack[0]; ++i) {
    if (stack[i] == gasit) gasit = 0;
    if (gasit == 0) {
      visited[stack[i]] = true;
      ciclu[++ciclu[0]] = stack[i];
    }
  }
  for (int i = 1; i <= N; ++i) if (visited[i]) {
    // calculeaza preturile
    solve1(i, -1, 0); solve1(i, -1, 1);
  }
  // second dp2
  assert(ciclu[0] > 2);
  int ret = -1;
  for (int alege = 1; alege <= 3; ++alege) {
    int aa = alege; while (aa > ciclu[0]) aa -= ciclu[0];
    int bb = nxt(aa);
    memset(dp2, 0, sizeof(dp2));
    na = aa; nb = bb;
    int aux = solve2(nxt(bb), 1) + dp[ciclu[bb]][1];
    if (ret == -1 || aux < ret) ret = aux;
  }
  printf("%d\n", ret);
  fclose(stdin); fclose(stdout);
  return 0;
}
