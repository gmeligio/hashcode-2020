#include <bits/stdc++.h>

using namespace std;

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
    sc = score();
  }

  double score() {
    double ret = 0;
    for (auto it : ind) {
      ret += it;
    }
    return ret;
  }
};


class book {
public:
  int rep;
  int id;
  int sc;
  book(int id, int rep, int sc) {
    this->id = id;
    this->rep = rep;
    this->sc = sc;
  }
};

double compute_score(library& l, vector<int>& sc, const int& d) {
  // l.n

  double acc = 0;
  for (auto b : l.ind) acc += sc[b];

  int q = (l.n + l.m - 1) / l.m;

  int o = q + l.t;
  double p = acc / o;

  double br = acc;
  if (o > d) br = acc - (o - d) * p;

  return br / o;
}

int main() {
  int b, l, d; cin >> b >> l >> d; --d;
  vector<int> scores(b);
  for (auto& it : scores) cin >> it;

  map<int, int> mp;
  vector<book> books;

  vector<library> libs;
  for (int i = 0; i < l; ++i) {
    int n, t, m; cin >> n >> t >> m;
    vector<int> ind(n);
    for (auto& it : ind) {
      cin >> it;
      mp[it]++;
    }

    sort(ind.begin(), ind.end(),                \
         [&scores](int a, int b) -> bool {
           return scores[a] < scores[b];
         });

    libs.emplace_back(n, t, m, i, ind);
  }


  int curd = d;
  int libsz = libs.size();
  for (int i = 0; i < min(1, libsz); ++i) {
    for (int j = i; j < libsz; ++j) {
      libs[j].sc = compute_score(libs[j], scores, curd);
    }

    sort(libs.begin() + i, libs.end(),
         [](const library& l1, const library& l2) -> bool {
           return l1.sc > l2.sc;
         });

    curd -= libs[i].t;
  }


  map<int, vector<int>> b2l;
  for (int i = 0; i < (int)libs.size(); ++i) {
    auto& lib = libs[i];
    for (int b : lib.ind) {
      if (!b2l.count(b)) {
        b2l[b].push_back(i);
      }
    }
  }

  for (int i = 0; i < b; ++i) {
    books.emplace_back(i, mp[i], scores[i]);
  }

  sort(books.begin(), books.end(),
       [](const book& b1, const book& b2) -> bool {
         if (b1.sc != b2.sc)
           return b1.sc > b2.sc;
         return b1.rep < b2.rep;
       });

  set<int> sl, sb;
  vector<pair<int, vector<int>>> ans;

  curd = 0;
  for (auto& b : books) {
    if (sb.count(b.id)) continue;
    for (int i : b2l[b.id]) {
      if (sl.count(i)) continue;
      if (curd + libs[i].t > d) continue;

      int day = curd + libs[i].t;
      int k = 0;
      int m = libs[i].m;

      vector<int> lind;

      for (int bid : libs[i].ind) {
        if (sb.count(bid)) continue;

        sb.insert(bid);
        lind.push_back(bid);
        ++k;
        if (k == m) {
          ++day;
          k = 0;
        }
        if (day > d) break;
      }

      if (!lind.empty()) {
        ans.emplace_back(libs[i].id, lind);
        curd += libs[i].t;
      }
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

  return 0;
}
