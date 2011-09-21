#include <iostream>
#include "erika_trie.h"
using namespace std;
using namespace erika;

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "USAGE: erika_make_trie <trie_name> < infile" << endl;
    return 0;
  }

  try {
    trie   t;
    int    label;
    ullong degree;
    int    tail;
    while (cin >> label) {
      if (cin >> degree && cin >> tail) {
        t.push(uc(label), degree, ((tail > 0) ? true : false));
      }
    }
    t.write(argv[1]);
  } catch (const char *err) {
    cerr << err << endl;
    return 1;
  }
  return 0;
}

