#include <iostream>
#include <string>
#include "erika_trie.h"
using namespace std;
using namespace erika;

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "USAGE: erika_extract <trie_name> < infile" << endl;
    return 0;
  }

  try {
    trie   t(argv[1]);
    string s;
    while (getline(cin, s)) {
      cout << "# " << s << endl;
      vector<result> r;
      t.extract(s.c_str(), r);
      vector<result>::const_iterator i = r.begin();
      vector<result>::const_iterator e = r.end();
      while (i != e) {
        cout << s.substr(i->begin(), i->end() - i->begin())
             << "\t" << i->begin() << "\t" << i->end();
        if (t.is_value()) { cout << "\t" << t.value(i->pos()); }
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

