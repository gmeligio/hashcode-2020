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


double compute_score(library& l, vector<int>& sc) {

  // l.n

  double acc = 0;
  for (auto b : l.ind) acc += sc[b];

  int q = (l.n + l.m - 1) / l.m + l.t;

  return acc / q;
}

int main() {
  int b, l, d; cin >> b >> l >> d;
  vector<int> scores(b);
  for (auto& it : scores) cin >> it;


  vector<library> libs;
  for (int i = 0; i < l; ++i) {
    int n, t, m; cin >> n >> t >> m;
    vector<int> ind(n);
    for (auto& it : ind) cin >> it;

    sort(ind.begin(), ind.end(),                \
         [&scores](int a, int b) -> bool {
           return scores[a] < scores[b];
         });

    libs.emplace_back(n, t, m, i, ind);
  }

  for (auto& lib : libs) {
    lib.sc = compute_score(lib, scores);
  }
  sort(libs.begin(), libs.end(),
       [](const library& l1, const library& l2) -> bool {
         return l1.sc > l2.sc;
       });

  set<int> books;
  vector<pair<int, vector<int>>> ans;
  int cur_cooldown = 0;
  for (auto& lib : libs) {
    if (cur_cooldown + lib.t > d) continue;
    pair<int , vector<int>> p;
    p.first = lib.id;

    cur_cooldown += lib.t;

    for (int b : lib.ind) {
      if (books.count(b)) continue;
      p.second.push_back(b);
      books.insert(b);
    }
    ans.push_back(p);
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
