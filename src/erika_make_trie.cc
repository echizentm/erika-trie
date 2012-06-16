#include <iostream>
#include "erika_trie.h"
using namespace std;
using namespace erika;

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "USAGE: erika_make_trie <trie_name> [tail_name] [value_name] < infile"
         << endl;
    return 0;
  }
  bool is_tail_trie  = false;
  bool is_value_trie = false;
  if (argc >= 3) { is_tail_trie  = true; }
  if (argc >= 4) { is_value_trie = true; }

  try {
    trie *pt          = NULL;
    trie *ptail_trie  = NULL;
    trie *pvalue_trie = NULL;
    if (is_value_trie) {
      ptail_trie  = new trie(argv[2]);
      pvalue_trie = new trie(argv[3]);
      pt          = new trie(ptail_trie, pvalue_trie);
    } else if (is_tail_trie) {
      ptail_trie = new trie(argv[2]);
      pt         = new trie(ptail_trie);
    } else {
      pt = new trie;
    }

    int    label;
    ullong degree;
    int    is_tail;
    int    is_value;
    while (cin >> label) {
      if (cin >> degree && cin >> is_tail) {
        is_value = 0;
        string tail  = "";
        string value = "";
        if (is_tail) {
          int tail_label;
          while (1) {
            cin >> tail_label;
            if (tail_label == 0) { break; }
            tail += uc(tail_label);
          }

          cin >> is_value;
          if (is_value) {
            int value_label;
            while (1) {
              cin >> value_label;
              if (value_label == 0) { break; }
              value += uc(value_label);
            }
          }
        }
        if (is_value_trie) {
          reverse(tail);
          ullong pos = 0;
          if (is_tail) { pos = ptail_trie->lookup(tail.c_str()); }
          reverse(value);
          ullong vpos = 0;
          if (is_value) { vpos = pvalue_trie->lookup(value.c_str()); }
          pt->push(uc(label), degree, (is_tail == 1), pos,
                   (is_value == 1), vpos);
        } else if (is_tail_trie) {
          reverse(tail);
          ullong pos = 0;
          if (is_tail) { pos = ptail_trie->lookup(tail.c_str()); }
          pt->push(uc(label), degree, (is_tail == 1), pos);
        } else {
          pt->push(uc(label), degree, (is_tail == 1), tail.c_str());
        }
      }
    }
    pt->write(argv[1]);
    delete pt;
  } catch (const char *err) {
    cerr << err << endl;
    return 1;
  }
  return 0;
}

