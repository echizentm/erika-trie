#include <iostream>
#include <string>
#include <queue>
#include "erika_trie.h"
using namespace std;
using namespace erika;

struct range {
  ullong b; // begin node
  ullong e; // end node
  ullong d; // depth
  range(ullong bb, ullong ee, ullong dd)
   : b(bb), e(ee), d(dd) {}
};

void read_words(vector<string> &dic) {
  string s;
  while (cin >> s) {
    dic.push_back(s);
  }
}

void write_nodes(vector<string> &dic) {
  queue<range> q;
  q.push(range(0, dic.size(), 0));
  while (q.size() > 0) {
    range r = q.front();
    q.pop();
    uc     pre_l  = dic[r.b][r.d];
    ullong pre_b  = r.b;
    if (dic[pre_b].length() < r.d) {
      cout << "0\t0" << endl;
      pre_b++;
      if (pre_b == r.e) { continue; }
    }
    ullong degree = 0;
    for (ullong i = pre_b; i < r.e; i++) {
      if (dic[i][r.d] != pre_l) {
        q.push(range(pre_b, i, r.d + 1));
        degree++;
        pre_b = i;
      }
      pre_l = dic[i][r.d];
    }
    q.push(range(pre_b, r.e, r.d + 1));
    uc label = (r.d > 0) ? dic[r.b][r.d - 1] : 0;
    cout << int(label) << "\t" << (degree + 1) << endl;
  }
}

int main() {
  vector<string> dic;
  read_words(dic);
  write_nodes(dic);
  return 0;
}

