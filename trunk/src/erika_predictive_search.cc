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
    char   ch;
    while ((ch = getc(stdin)) != -1) {
      if (ch != '\n') {
        s += ch;
      } else {
        cout << "# " << s << endl;
        vector<pair<string, ullong> > v;
        t.predictive_search(s.c_str(), v);
        vector<pair<string, ullong> >::const_iterator i = v.begin();
        vector<pair<string, ullong> >::const_iterator e = v.end();
        while (i != e) {
          cout << i->first << endl;
          i++;
        }
        s = "";
      }
    }
  } catch (const char *err) {
    cerr << err << endl;
    return 1;
  }
  return 0;
}

