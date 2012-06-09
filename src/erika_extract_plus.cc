#include <iostream>
#include <string>
#include <map>
#include "erika_trie.h"
using namespace std;
using namespace erika;

void show_help (void) {
  cerr << "USAGE: erika_extract_plus -i trie_file_path [OPTIONS] < infile" << endl;
  cerr << "OPTIONS:" << endl;
  cerr << "        -c: show total count of each found keywords" << endl;
  cerr << "        -u: show result using UNIX TOOL(cut, paste, e.t.c.) friendly format" << endl;
  cerr << "        -v: sort features by each value of features, when you use -c option" << endl;
  cerr << "        -h: show USAGE" << endl;
}

int main(int argc, char **argv) {
  char   param      = '\0';
  bool   is_unix    = false;
  bool   is_count   = false;
  bool   is_valsort = false;
  bool   is_help    = false;
  string index_path = "";

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == '\0') { continue; }
      switch (argv[i][1]) {
        case 'c': is_count   = true;       break;
        case 'u': is_unix    = true;       break;
        case 'v': is_valsort = true;       break;
        case 'h': is_help    = true;       break;
        default : param      = argv[i][1]; break;
      }
    } else if (param) {
      switch (param) {
        case 'i': index_path = argv[i]; break;
      }
      param = '\0';
    }
  }

  if (is_help) {
    show_help();
    return 0;
  } else if (index_path == "") {
    cerr << "You must set -i parameter as file-path of erika's trie file" << endl;
    show_help();
    return 0;
  }


  try {
    string sep1 = "\t";
    string sep2 = "\n";
    if (is_unix) {
      sep1 = ":";
      sep2 = ",";
    }

    trie   t(index_path.c_str());
    string s;
    while (getline(cin, s)) {
      if (!is_unix) { cout << "# " << s << endl; }
      vector<result> r;
      t.extract(s.c_str(), r);

      map<string, ullong> count_map;
      string sep_tmp = "";
      vector<result>::const_iterator i = r.begin();
      vector<result>::const_iterator e = r.end();
      while (i != e) {
        string key = s.substr(i->begin(), i->end() - i->begin());
        if (is_count) {
          count_map[key]++;
        } else {
          cout << sep_tmp << key << sep1 << i->begin() << sep1 << i->end();
          sep_tmp = sep2;
        }
        i++;
      }
      if (is_count) {
        map<string, ullong>::iterator i = count_map.begin();
        map<string, ullong>::iterator e = count_map.end();
        sep_tmp = "";
        if (!is_valsort) {
          while (i != e) {
            cout << sep_tmp << i->first << sep1 << i->second;
            sep_tmp = sep2;
            i++;
          }
        } else {
          multimap<ullong, string> mm;
          while (i != e) {
            mm.insert(pair<ullong, string>(i->second, i->first));
            i++;
          }
          multimap<ullong, string>::reverse_iterator mi = mm.rbegin();
          multimap<ullong, string>::reverse_iterator me = mm.rend();
          while (mi != me) {
            cout << sep_tmp << mi->second << sep1 << mi->first;
            sep_tmp = sep2;
            mi++;
          }
        }
      }
      cout << endl;
    }
  } catch (const char *err) {
    cerr << err << endl;
    return 1;
  }
  return 0;
}

