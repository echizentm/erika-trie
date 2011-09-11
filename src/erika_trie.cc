#include "erika_trie.h"

namespace erika {
  using namespace std;

  void trie::initialize() {
  } 

  trie::trie() {
    this->initialize();
    this->vc_.push(1);
  }
  trie::trie(ifstream &ifs) {
    this->initialize();
    if (!(this->read(ifs))) {
      throw "erika::trie::trie(): read() returns false.";
    }
  }
  trie::trie(const char *filename) {
    this->initialize();
    if (!(this->read(filename))) {
      throw "erika::trie::trie(): read() returns false.";
    }
  }
  trie::~trie() {
  }

  ullong trie::bsearch(uc label, ullong l, ullong r) const {
    while (l < r) {
      ullong p      = (l + r) / 2;
      ullong label2 = this->label(p);
      if      (label < label2) { r = p; }
      else if (label > label2) { l = p + 1; }
      else { return p; }
    }
    return this->size();
  }
  void trie::csearch(const char *key, vector<value> &values,
                     bool is_cps, ullong depth) {
    ullong depth_begin = depth;
    ullong pos   = 0;
    ullong begin = this->child(pos);
    ullong end   = begin + this->degree(pos);
    while (key[depth] != '\0') {
      pos  = this->bsearch(uc(key[depth]), begin, end);
      if (pos == this->size()) { return; }
      depth++;

      begin = this->child(pos);
      end   = begin + this->degree(pos);
      if (is_cps || key[depth] == '\0') {
        ullong v = this->bsearch('\0', begin, end);
        if(v != this->size()) { values.push_back(value(depth_begin, depth, v)); }
        //if((end > begin) && this->label(begin) == '\0') {
        //  values.push_back(value(depth_begin, depth, begin));
        //}
      }
    }
  }
  ullong trie::search(const char *key) {
    vector<value> values;
    this->csearch(key, values, false, 0);
    if (values.size() == 0) { return 0; }
    return values[0].pos();
  }
  void trie::cpsearch(const char *key, vector<value> &values) {
    this->csearch(key, values, true, 0);
  }
  void trie::cpsearch_all(const char *key, vector<value> &values) {
    ullong depth = 0;
    while (key[depth] != '\0') {
      this->csearch(key, values, true, depth);
      depth++;
    }
  }

  bool trie::read(ifstream &ifs) {
    bool r = this->vc_.read(ifs);
    if (!r) { return false; }
    ullong size = 0;
    ifs.read((char *)&size, sizeof(ullong));
    uc c = 0;
    this->ls_.clear();
    for (ullong i = 0; i < size; i++) {
      ifs.read((char *)&c, sizeof(uc));
      if (ifs.eof()) { return false; }
      this->ls_.push_back(c);
    }
    return true;
  }
  bool trie::read(const char *filename) {
    ifstream ifs;
    ifs.open(filename, ios::in | ios::binary);
    if (!ifs) { throw "erika::trie::read(): file cannot open for read."; }
    bool ret = this->read(ifs);
    ifs.close();
    return ret;
  }

  void trie::write(ofstream &ofs) const {
    this->vc_.write(ofs);
    ullong size = this->size();
    ofs.write((char *)&size, sizeof(ullong));
    for (ullong i = 0; i < size; i++) {
      ofs.write((char *)&(this->ls_[i]), sizeof(uc));
    }
  }
  void trie::write(const char *filename, bool is_append) const {
    ofstream ofs;
    if (is_append) {
      ofs.open(filename, ios::out | ios::binary | ios::app);
    } else {
      ofs.open(filename, ios::out | ios::binary | ios::trunc);
    }
    if (!ofs) { throw "erika::trie::write(): file cannot open for write."; }
    this->write(ofs);
    ofs.close();
    return;
  }
}

