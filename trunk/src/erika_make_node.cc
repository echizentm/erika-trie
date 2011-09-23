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
  while (getline(cin, s)) { dic.push_back(s); }
}

void write_nodes(vector<string> &dic) {
  queue<range> q;
  q.push(range(0, dic.size(), 0));
  while (q.size() > 0) {
    range r = q.front();
    q.pop();
    if ((r.e - r.b) == 1) {
      cout << int(uc(dic[r.b][r.d - 1])) << "\t0\t1\t";
      while (r.d < dic[r.b].length()) {
        cout << int(uc(dic[r.b][r.d])) << "\t";
        r.d++;
      }
      cout << "0" << endl;
    } else {
      bool is_tail = false;
      if (dic[r.b].length() == r.d) {
        is_tail = true;
        r.b++;
      }
      ullong degree = 0;
      uc     pre_l  = dic[r.b][r.d];
      ullong pre_b  = r.b;
      for (ullong i = r.b; i < r.e; i++) {
        if (uc(dic[i][r.d]) != pre_l) {
          q.push(range(pre_b, i, r.d + 1));
          degree++;
          pre_b = i;
        }
        pre_l = dic[i][r.d];
      }
      q.push(range(pre_b, r.e, r.d + 1));
      degree++;
      uc label = (r.d > 0) ? dic[r.b][r.d - 1] : 0;
      cout << int(label) << "\t" << degree;
      if (is_tail) { cout << "\t1\t0" << endl; }
      else         { cout << "\t0" << endl; }
    }
  }
}

int main() {
  vector<string> dic;
  read_words(dic);
  write_nodes(dic);
  return 0;
}

