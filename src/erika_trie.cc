#include "erika_trie.h"

namespace erika {
  using namespace std;

  trie::trie() {
    this->vc_.push(1);
    this->ptail_trie_ = NULL;
  }
  trie::trie(ifstream &ifs) {
    this->ptail_trie_ = NULL;
    if (!(this->read(ifs))) {
      throw "erika::trie::trie(): read() returns false.";
    }
  }
  trie::trie(const char *filename) {
    this->ptail_trie_ = NULL;
    if (!(this->read(filename))) {
      throw "erika::trie::trie(): read() returns false.";
    }
  }
  trie::trie(trie *ptail_trie) {
    this->vc_.push(1);
    this->ptail_trie_ = ptail_trie;
  }
  trie::~trie() {
    if (this->ptail_trie_) { delete this->ptail_trie_; }
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
                     bool is_cps, ullong depth, ullong max) {
    ullong depth_begin = depth;
    ullong pos   = 0;
    while (key[depth] != '\0') {
      ullong begin = this->child(pos);
      ullong end   = begin + this->degree(pos);
      pos  = this->bsearch(uc(key[depth]), begin, end);
      if (pos == this->size()) { return; }
      depth++;

      if(this->is_tail(pos)) {
        const string &tail = this->tail(pos);
        int r = cmp_substr(tail.c_str(), key + depth);
        if (r == 0 || (r == 1 && is_cps)) {
          values.push_back(value(depth_begin,
                                 depth + tail.length(), pos));
          if (values.size() == max) { return; }
        }
      }
    }
  }
  void trie::dsearch(ullong pos, const string &str,
                     vector<pair<string, ullong> > &values) {
    if (this->is_tail(pos)) {
      const string &tail = this->tail(pos);
      values.push_back(pair<string, ullong>(str + tail, pos));
    }
    ullong begin = this->child(pos);
    ullong end   = begin + this->degree(pos);
    while (begin < end) {
      this->dsearch(begin, str + char(this->label(begin)), values);
      begin++;
    }
  }
  ullong trie::lookup(const char *key) {
    vector<value> values;
    this->csearch(key, values, false, 0, 0);
    if (values.size() == 0) { return 0; }
    return values[0].pos();
  }
  void trie::common_prefix_search(const char *key, vector<value> &values) {
    this->csearch(key, values, true, 0, 0);
  }
  void trie::predictive_search(const char *key,
                               vector<pair<string, ullong> > &values) {
    ullong depth = 0;
    ullong pos   = 0;
    while (key[depth] != '\0') {
      ullong begin = this->child(pos);
      ullong end   = begin + this->degree(pos);
      pos  = this->bsearch(uc(key[depth]), begin, end);
      if (pos == this->size()) { return; }
      depth++;

      if (this->is_tail(pos)) {
        const string &tail = this->tail(pos);
        int r = cmp_substr(key + depth, tail.c_str());
        if (r == 0 || r == 1) { break; }
      }
    }
    this->dsearch(pos, string(key, 0, depth), values);
  }
  void trie::extract(const char *key, vector<value> &values) {
    ullong depth = 0;
    while (key[depth] != '\0') {
      this->csearch(key, values, true, depth, 0);
      depth++;
    }
  }
  bool trie::check(const char *key) {
    vector<value> values;
    ullong depth = 0;
    while (key[depth] != '\0') {
      this->csearch(key, values, true, depth, 1);
      if (values.size() > 0) { return true; }
      depth++;
    }
    return false;
  }

  bool trie::read(ifstream &ifs) {
    if (!(this->vc_.read(ifs)))       { return false; }
    if (!(this->tail_pos_.read(ifs))) { return false; }
    if (!(this->is_tail_.read(ifs)))  { return false; }
    this->is_tail_.build();

    uc flg = 0;
    ifs.read((char *)&flg, sizeof(uc));
    if (flg > 0) {
      if (this->ptail_trie_) { delete this->ptail_trie_; }
      this->ptail_trie_ = new trie;
      if (!(this->ptail_trie_->read(ifs))) { return false; }
    }

    ullong size = 0;
    ifs.read((char *)&size, sizeof(ullong));
    uc c = 0;
    this->ls_.clear();
    for (ullong i = 0; i < size; i++) {
      ifs.read((char *)&c, sizeof(uc));
      if (ifs.eof()) { return false; }
      this->ls_.push_back(c);
    }

    ifs.read((char *)&size, sizeof(ullong));
    this->tail_.clear();
    for (ullong i = 0; i < size; i++) {
      char   ch;
      string ss = "";
      while (1) {
        ifs.read((char *)&ch, sizeof(char));
        if (ifs.eof()) { return false; }
        if (ch == '\0') { break; }
        ss += ch;
      }
      this->tail_.push_back(ss);
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
    this->tail_pos_.write(ofs);
    this->is_tail_.write(ofs);

    uc flg = 0;
    if (this->ptail_trie_) { flg = 1; }
    ofs.write((char *)&flg, sizeof(uc));
    if (flg > 0) {
      this->ptail_trie_->write(ofs);
    }

    ullong size = this->size();
    ofs.write((char *)&size, sizeof(ullong));
    for (ullong i = 0; i < size; i++) {
      ofs.write((char *)&(this->ls_[i]), sizeof(uc));
    }

    size = this->tail_.size();
    ofs.write((char *)&size, sizeof(ullong));
    for (ullong i = 0; i < size; i++) {
      char   ch  = '\0';
      ullong len = this->tail_[i].size();
      for (ullong j = 0; j < len; j++) {
        ch = this->tail_[i][j];
        ofs.write((char *)&ch, sizeof(char));
      }
      ch = '\0';
      ofs.write((char *)&ch, sizeof(char));
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

