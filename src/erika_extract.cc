#include <iostream>
#include <string>
#include "erika_trie.h"
using namespace std;
using namespace erika;

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "USAGE: erika_make_trie <trie_name> < infile" << endl;
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
        vector<value> v;
        t.cpsearch_all(s.c_str(), v);
        vector<value>::const_iterator i = v.begin();
        vector<value>::const_iterator e = v.end();
        while (i != e) {
          cout << s.substr(i->begin(), i->end() - i->begin())
               << "\t" << i->begin() << "\t" << i->end() << endl;
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

