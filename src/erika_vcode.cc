#include "erika_vcode.h"

namespace erika {
  using namespace std;

  void vcode::initialize() {
    this->cMSB_.push_back(0);
    this->base_.push_back(0);
    this->size_       = 0;
    this->block_size_ = sizeof(ullong) * 8;
  }

  vcode::vcode() {
    this->initialize();
  }
  vcode::vcode(ifstream &ifs) {
    this->initialize();
    if (!(this->read(ifs))) {
      throw "erika::vcode::vcode(): read() returns false.";
    }
  }
  vcode::vcode(const char *filename) {
    this->initialize();
    if (!(this->read(filename))) {
      throw "erika::vcode::vcode(): read() returns false.";
    }
  }
  vcode::~vcode() {
  }

  ullong vcode::size() const {
    return this->size_;
  }

  void vcode::push(ullong d) {
    // add element to vector if size is over
    ullong q = this->size_ % this->block_size_;
    if (q == 0) {
      this->cMSB_.push_back(*(this->cMSB_.rbegin()));
      this->base_.push_back(*(this->base_.rbegin()));
    }

    // get MSB
    vector<uint>::reverse_iterator icMSB = this->cMSB_.rbegin();
    uint MSB = *icMSB;
    icMSB++;
    uint preMSB = *icMSB;
    MSB -= preMSB;

    // get SB
    uint SB = this->block_size_;
    while ((SB > 0) && (((d & (1ULL << (SB - 1))) >> (SB - 1)) == 0)) { SB--; }

    // update cMSB & base
    for (uint i = MSB; i < SB; i++) {
      (*(this->cMSB_.rbegin()))++;
      this->V_.push_back(0);
    }
    (*(this->base_.rbegin())) += d;

    // update V
    for (uint i = 0; i < SB; i++) {
      this->V_[preMSB + i] |= (((d & (1ULL << i)) >> i) << q);
    }
    this->size_++;
    return;
  }

  ullong vcode::select(ullong pos) const {
    if (this->size_ <= pos) {
      throw "erika::vcode::get(): pos is out of range.";
    }

    ullong p     = pos / this->block_size_;
    ullong q     = (pos % this->block_size_) + 1ULL;
    uint   begin = this->cMSB_[p];
    uint   end   = this->cMSB_[p + 1];

    ullong value = this->base_[p];
    if (q == this->block_size_) {
      for (uint i = begin; i < end; i++) {
        value += (popcount64(this->V_[i])
                  << (i - begin));
      }
    } else {
      for (uint i = begin; i < end; i++) {
        value += (popcount64((this->V_[i] & ((1ULL << q) - 1ULL)))
                  << (i - begin));
      }
    }
    return value;
  }
  ullong vcode::rank(ullong n) const {
    ullong l = 0;
    ullong r = this->size_;
    while (l < r) {
      ullong p  = (l + r) / 2;
      ullong n2 = this->select(p);
      if      (n < n2) { r = p; }
      else if (n > n2) { l = p + 1; }
      else {
        while (p > 0 && this->diff(p) == 0) { p--; }
        return p;
      }
    }
    return r;
  }

  ullong vcode::diff(ullong pos) const {
    if (this->size_ <= pos) {
      throw "erika::vcode::diff(): pos is out of range.";
    }

    ullong p     = pos / this->block_size_;
    ullong q     = (pos % this->block_size_) + 1ULL;
    uint   begin = this->cMSB_[p];
    uint   end   = this->cMSB_[p + 1];

    ullong value = 0;
    for (uint i = begin; i < end; i++) {
      value += (((this->V_[i] & (1ULL << (q - 1ULL))) >> (q - 1ULL))
                << (i - begin));
    }
    return value;
  }

  bool vcode::read(ifstream &ifs) {
    ullong buf_ull;
    uint   buf_ui;

    ifs.read((char *)&(this->size_), sizeof(ullong));
    if (ifs.eof()) { return false; }
    ullong block_num = ((this->size_ + this->block_size_ - 1) / this->block_size_)
                       + 1;

    this->cMSB_.clear();
    while(1) {
      if (this->cMSB_.size() >= block_num) { break; }
      ifs.read((char *)&buf_ui, sizeof(uint));
      if (ifs.eof()) { return false; }
      this->cMSB_.push_back(buf_ui);
    }

    this->base_.clear();
    while(1) {
      if (this->base_.size() >= block_num) { break; }
      ifs.read((char *)&buf_ull, sizeof(ullong));
      if (ifs.eof()) { return false; }
      this->base_.push_back(buf_ull);
    }

    this->V_.clear();
    while(1) {
      if (this->V_.size() >= *(this->cMSB_.rbegin())) { break; }
      ifs.read((char *)&buf_ull, sizeof(ullong));
      if (ifs.eof()) { return false; }
      this->V_.push_back(buf_ull);
    }
    return true;
  }
  bool vcode::read(const char *filename) {
    ifstream ifs;
    ifs.open(filename, ios::in | ios::binary);
    if (!ifs) { throw "erika::vcode::read(): file cannot open for read."; }
    bool ret = this->read(ifs);
    ifs.close();
    return ret;
  }

  void vcode::write(ofstream &ofs) const {
    ofs.write((char *)&(this->size_), sizeof(ullong));
    for (ullong i = 0; i < this->cMSB_.size(); i++) {
      ofs.write((char *)&(this->cMSB_[i]), sizeof(uint));
    }
    for (ullong i = 0; i < this->base_.size(); i++) {
      ofs.write((char *)&(this->base_[i]), sizeof(ullong));
    }
    for (ullong i = 0; i < this->V_.size(); i++) {
      ofs.write((char *)&(this->V_[i]), sizeof(ullong));
    }
    return;
  }
  void vcode::write(const char *filename, bool is_append) const {
    ofstream ofs;
    if (is_append) {
      ofs.open(filename, ios::out | ios::binary | ios::app);
    } else {
      ofs.open(filename, ios::out | ios::binary | ios::trunc);
    }
    if (!ofs) { throw "erika::vcode::write(): file cannot open for write."; }
    this->write(ofs);
    ofs.close();
    return;
  }
}

