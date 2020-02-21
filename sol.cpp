#include <bits/stdc++.h>

using namespace std;

using ll = long long;

class library {
 public:
  int n, t, m, id;
  double sc;
  vector<int> ind;
  library(int n, int t, int m, int id, vector<int>& ind) {
    this->n = n;
    this->t = t;
    this->m = m;
    this->id = id;
    this->ind = ind;
    sc = -1;
  }
};

double compute_score(library& l, vector<int>& sc, set<int>& marked, const int& d) {
  // l.n

  double acc = 0;
  for (auto b : l.ind) {
    if (marked.count(b)) continue;
    acc += sc[b];
  }

  int q = (l.n + l.m - 1) / l.m;

  int o = q + l.t;
  double p = acc / o;

  double br = acc;
  if (o > d) br = acc - (o - d) * p;

  return br / o;
}

int main() {
  int b, l, d;
  cin >> b >> l >> d;
  vector<int> scores(b);
  for (auto& it : scores) cin >> it;

  map<int, int> mp;

  vector<library> libs;
  for (int i = 0; i < l; ++i) {
    int n, t, m;
    cin >> n >> t >> m;
    vector<int> ind(n);
    for (auto& it : ind) {
      cin >> it;
      ++mp[it];
    }

    sort(ind.begin(), ind.end(),
         [&scores](int a, int b) -> bool { return scores[a] < scores[b]; });

    libs.emplace_back(n, t, m, i, ind);
  }

  for (auto& lib : libs) {
    sort(lib.ind.begin(), lib.ind.end(),
         [&mp, &scores](int b1, int b2) -> bool {
           if (scores[b1] != scores[b2]) {
             return scores[b1] > scores[b2];
           }
           return mp[b1] < mp[b2];
         });
  }

  set<int> marked;

  int curd = d;
  int libsz = libs.size();
  for (int i = 0; i < min(100, libsz); ++i) {
    for (int j = i; j < libsz; ++j) {
      libs[j].sc = compute_score(libs[j], scores, marked, curd);
    }

    sort(libs.begin() + i, libs.end(),
         [](const library& l1, const library& l2) -> bool {
           return l1.sc > l2.sc;
         });

    for (auto bid : libs[i].ind) {
      marked.insert(bid);
    }
    curd -= libs[i].t;
  }

  set<int> books;
  vector<pair<int, vector<int>>> ans;
  int cur_cooldown = 0;
  for (auto& lib : libs) {
    if (cur_cooldown + lib.t > d) continue;
    pair<int, vector<int>> p;
    p.first = lib.id;

    for (int b : lib.ind) {
      if (books.count(b)) continue;
      p.second.push_back(b);
      books.insert(b);
    }

    if (!p.second.empty()) {
      ans.push_back(p);
      cur_cooldown += lib.t;
    }
  }

  cout << ans.size() << endl;
  for (auto& lib : ans) {
    cout << lib.first << " " << lib.second.size() << endl;
    for (auto i : lib.second) {
      cout << i << " ";
    }
    cout << endl;
  }
}
