#include "erika_bv.h"

namespace erika {
  using namespace std;

  tiny_bv::tiny_bv() {
    for (int i = 0; i < 4; i++) {
      this->B_[i] = 0x0ULL;
      this->r_[i] = 0;
    }
  }
  void tiny_bv::set(ullong i, bool b) {
    ullong m = 0x1ULL << (i % 64);
    if (b) { this->B_[i / 64] |=  m; }
    else   { this->B_[i / 64] &= ~m; }
  }
  bool tiny_bv::get(ullong i) const {
    ullong m = 0x1ULL << (i % 64);
    return this->B_[i / 64] & m;
  }
  void tiny_bv::build() {
    this->r_[0] = 0;
    for (int i = 0; i < 3; i++) {
      this->r_[i + 1] = this->r_[i] + popcount64(this->B_[i]);
    }
  }
  ullong tiny_bv::rank(ullong i) const {
    ullong m = ullong(-1);
    if (i % 64 < 63) { m = (0x1ULL << (i % 64 + 1)) - 1; }
    return this->r_[i / 64] + popcount64(this->B_[i / 64] & m);
  }
  void tiny_bv::write(std::ofstream &ofs) const {
    ofs.write((char *)&(this->B_), sizeof(ullong) * 4);
  }
  bool tiny_bv::read(std::ifstream &ifs) {
    ifs.read((char *)&(this->B_), sizeof(ullong) * 4);
    if (ifs.eof()) { return false; }
    return true;
  }


  void bv::set(ullong i, bool b) {
    if (i < 0) { throw "erika::bv::set(): invalid i."; }
    ullong q = i / 256;
    ullong r = i % 256;
    while ((size_t)q >= this->tbv_.size()) {
      this->tbv_.push_back(tbv_pair(tiny_bv(), 0));
    }
    this->tbv_[q].first.set(r, b);
  }
  bool bv::get(ullong i) const {
    if (i < 0) { throw "erika::bv::get(): invalid i."; }
    ullong q = i / 256;
    ullong r = i % 256;
    if ((size_t)q >= this->tbv_.size()) { return false; }
    return this->tbv_[q].first.get(r);
  }
  void bv::build() {
    vector<tbv_pair>::iterator i = this->tbv_.begin();
    vector<tbv_pair>::iterator e = this->tbv_.end();
    ullong sum = 0;
    while (i != e) {
      i->first.build();
      i->second = sum;
      sum += i->first.rank(255);
      i++;
    }
  }
  ullong bv::rank(ullong i, bool b) const {
    if (this->tbv_.size() == 0) { return (b ? 0 : i + 1); }
    ullong q = i / 256;
    ullong r = i % 256;
    tbv_pair t;
    ullong sum;
    if ((size_t)q >= this->tbv_.size()) {
      t = this->tbv_.back();
      sum = t.second + t.first.rank(255);
    } else {
      t = this->tbv_[q];
      sum = t.second + t.first.rank(r);
    }
    if (b) { return sum; }
    else   { return i + 1 - sum; }
  }
  ullong bv::select(ullong i, bool b) const {
    ullong l = 0;
    ullong r = this->tbv_.size() * 256;
    while (l < r) {
      ullong p   = (l + r) / 2;
      ullong sum = this->rank(p, b);
      if      (i < sum) { r = p; }
      else if (i > sum) { l = p + 1; }
      else {
        while (this->get(p) == (b == false)) { p++; }
        return p;
      }
    }
    throw "erika::bv::select(): not found.";
    return 0;
  }
  void bv::write(ofstream &ofs) const {
    ullong size = this->tbv_.size();
    ofs.write((char *)&size, sizeof(ullong));
    vector<tbv_pair>::const_iterator i = this->tbv_.begin();
    vector<tbv_pair>::const_iterator e = this->tbv_.end();
    while (i != e) { i->first.write(ofs); i++; }
  }
  void bv::write(const char *filename, bool is_append) const {
    ofstream ofs;
    if (is_append) {
      ofs.open(filename, ios::out | ios::binary | ios::app);
    } else {
      ofs.open(filename, ios::out | ios::binary | ios::trunc);
    }
    if (!ofs) { throw "erika::bv::write(): file cannot open for write."; }
    this->write(ofs);
    ofs.close();
    return;
  }
  bool bv::read(ifstream &ifs) {
    ullong size = 0;
    ifs.read((char *)&size, sizeof(ullong));
    this->tbv_.clear();
    for (ullong i = 0; i < size; i++) {
      this->tbv_.push_back(tbv_pair(tiny_bv(), 0));
      if(!(this->tbv_.back().first.read(ifs))) { return false; }
    }
    return true;
  }
  bool bv::read(const char *filename) {
    ifstream ifs;
    ifs.open(filename, ios::in | ios::binary);
    if (!ifs) { throw "erika::bv::read(): file cannot open for read."; }
    bool ret = this->read(ifs);
    ifs.close();
    return ret;
  }
}

