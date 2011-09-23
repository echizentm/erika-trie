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
    int    is_tail;
    while (cin >> label) {
      if (cin >> degree && cin >> is_tail) {
        string tail = "";
        if (is_tail) {
          int tail_label;
          while (1) {
            cin >> tail_label;
            if (tail_label == 0) { break; }
            tail += uc(tail_label);
          }
        }
        t.push(uc(label), degree, (is_tail == 1), tail.c_str());
      }
    }
    t.write(argv[1]);
  } catch (const char *err) {
    cerr << err << endl;
    return 1;
  }
  return 0;
}

