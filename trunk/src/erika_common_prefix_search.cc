#include <iostream>
#include <string>
#include "erika_trie.h"
using namespace std;
using namespace erika;

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "USAGE: erika_common_prefix_search <trie_name> < infile" << endl;
    return 0;
  }

  try {
    trie   t(argv[1]);
    string s;
    while (getline(cin, s)) {
      cout << "# " << s << endl;
      vector<value> v;
      t.common_prefix_search(s.c_str(), v);
      vector<value>::const_iterator i = v.begin();
      vector<value>::const_iterator e = v.end();
      while (i != e) {
        cout << s.substr(i->begin(), i->end() - i->begin()) << endl;
        i++;
      }
    }
  } catch (const char *err) {
    cerr << err << endl;
    return 1;
  }
  return 0;
}

