#include <iostream>
#include "erika_defs.h"
using namespace std;
using namespace erika;

int main(int argc, char **argv) {
  try {
    int    label;
    ullong degree;
    int    is_tail;
    int    is_value;
    while (cin >> label) {
      if (cin >> degree && cin >> is_tail) {
        if (is_tail) {
          int tail_label;
          while (1) {
            cin >> tail_label;
            if (tail_label == 0) { break; }
          }

          cin >> is_value;
          if (is_value) {
            string value = "";
            int value_label;
            while (1) {
              cin >> value_label;
              if (value_label == 0) { break; }
              value += uc(value_label);
            }
            reverse(value);
            cout << value << endl;
          }
        }
      }
    }
  } catch (const char *err) {
    cerr << err << endl;
    return 1;
  }
  return 0;
}

