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

void read_words(vector<string> &keys, vector<string> &values) {
  string s;
  while (getline(cin, s)) {
    ullong pos = s.find('\t');
    if (pos != string::npos) {
      keys.push_back(s.substr(0, pos));
      values.push_back(s.substr(pos + 1));
    } else {
      keys.push_back(s);
    }
  }
}

void print_value(vector<string> &values, ullong pos) {
  if (values.size() > 0) {
    cout << "1\t";
    ullong i = 0;
    while (i < values[pos].length()) {
      cout << int(uc(values[pos][i])) << "\t";
      i++;
    }
  }
  cout << "0" << endl;
}

void write_nodes(vector<string> &keys, vector<string> &values) {
  queue<range> q;
  q.push(range(0, keys.size(), 0));
  while (q.size() > 0) {
    range r = q.front();
    q.pop();
    if ((r.e - r.b) == 1) {
      cout << int(uc(keys[r.b][r.d - 1])) << "\t0\t1\t";
      while (r.d < keys[r.b].length()) {
        cout << int(uc(keys[r.b][r.d])) << "\t";
        r.d++;
      }
      cout << "0\t";
      print_value(values, r.b);
    } else {
      bool is_tail = false;
      if (keys[r.b].length() == r.d) {
        is_tail = true;
        r.b++;
      }
      ullong degree = 0;
      uc     pre_l  = keys[r.b][r.d];
      ullong pre_b  = r.b;
      for (ullong i = r.b; i < r.e; i++) {
        if (uc(keys[i][r.d]) != pre_l) {
          q.push(range(pre_b, i, r.d + 1));
          degree++;
          pre_b = i;
        }
        pre_l = keys[i][r.d];
      }
      q.push(range(pre_b, r.e, r.d + 1));
      degree++;
      uc label = (r.d > 0) ? keys[r.b][r.d - 1] : 0;
      cout << int(label) << "\t" << degree;
      if (is_tail) { cout << "\t1\t0\t"; print_value(values, r.b - 1); }
      else         { cout << "\t0" << endl; }
    }
  }
}

int main() {
  vector<string> keys;
  vector<string> values;
  read_words(keys, values);
  write_nodes(keys, values);
  return 0;
}

