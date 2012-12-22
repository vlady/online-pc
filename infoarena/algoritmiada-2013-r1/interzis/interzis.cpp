#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

string v; 
int N, L;
int pre[1024], pre2[1024];
int dp[2][1001];

int main() {
  freopen("interzis.in", "r", stdin);
  freopen("interzis.out", "w", stdout);

  cin >> N >> L >> v;
  // de ce sa bagi si caz cu L = 0?
  if (L == 0) {
    int ret = 1;
    while (N--) {
      ret *= 2; ret %= 101267;
    }
    cout << ret << '\n';
    fclose(stdin); fclose(stdout);
    return 0;
  }
  pre[1] = 0;
  for (int i = 2; i <= L; ++i) {
    int p = i - 1;
    pre[i] = 0;
    do  {
      if (v[pre[p]] == v[i-1]) { pre[i] = pre[p] + 1; break; }
      p = pre[p];
    } while (p);
  }
  pre2[0] = 0;
  for (int i = 1; i < L; ++i) {
    // am i si pun una inversa
    char inv =((v[i] - 'a') ^ 1) + 'a';
    int p = i;
    do {
      if (v[pre[p]] == inv) { pre2[i] = pre[p] + 1; break; }
      p = pre[p];
    } while (p);
  }

  dp[0][0] = 1;
  for (int n = 0; n <= N; ++n) {
    memset(dp[(n&1)^1], 0, sizeof(dp[(n&1)^1]));
    for (int l = 0; l < L; ++l) if (dp[n & 1][l]) {
      while (dp[n & 1][l] > 101267) dp[n & 1][l] -= 101267;
      if (l + 1 != L) dp[(n&1)^1][l + 1] += dp[n&1][l];
      dp[(n&1)^1][pre2[l]] += dp[n&1][l]; 
    }
  }
  int total = 0;
  for (int i = 0; i < L; ++i) total += (int)dp[N & 1][i];
  total %= 101267;
  cout << total << '\n';
  fclose(stdin); fclose(stdout);
  return 0;
}
