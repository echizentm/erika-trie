#include <iostream>
#include <string>
#include "erika_trie.h"
using namespace std;
using namespace erika;

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "USAGE: erika_predictive_search <trie_name> < infile" << endl;
    return 0;
  }

  try {
    trie   t(argv[1]);
    string s;
    while (getline(cin, s)) {
      cout << "# " << s << endl;
      vector<pair<string, ullong> > r;
      t.predictive_search(s.c_str(), r);
      vector<pair<string, ullong> >::const_iterator i = r.begin();
      vector<pair<string, ullong> >::const_iterator e = r.end();
      while (i != e) {
        cout << i->first;
        if (t.is_value()) { cout << "\t" << t.value(i->second); }
        cout << endl;
        i++;
      }
    }
  } catch (const char *err) {
    cerr << err << endl;
    return 1;
  }
  return 0;
}

