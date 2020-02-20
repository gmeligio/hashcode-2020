#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {

  string exe = argv[1];
  string kase = argv[2];

  string cmd = "./" + exe + " < " + kase + ".in > " + kase + ".out";

  system(cmd.c_str());

  freopen((kase + ".in").c_str(), "r", stdin);
  int b, l, d;
  cin >> b >> l >> d;

  map<int, int> sc;
  for (int i = 0; i < b; ++i) cin >> sc[i];

  map<int, pair<int, int>> mp;
  for (int i = 0; i < l; ++i) {
    int n, t, m;
    cin >> n >> t >> m;
    mp[i] = pair<int, int>{t, m};
    int tt;
    for (int i = 0; i < n; ++i) cin >> tt;
  }

  freopen((kase + ".out").c_str(), "r", stdin);

  int n;
  cin >> n;

  long long ans = 0;
  int cur_day = 0;

  for (int i = 0; i < n; ++i) {
    int id, b;
    cin >> id >> b;

    cur_day += mp[id].first;
    int day = cur_day;
    int k = 0;
    for (int j = 0; j < b; ++j) {
      int bid;
      cin >> bid;
      if (day > d) break;

      ans += sc[bid];
      ++k;
      if (k == mp[id].second) {
        k = 0;
        ++day;
      }
    }
  }

  cout << ans << endl;
}
