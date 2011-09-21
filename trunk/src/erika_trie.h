#ifndef ERIKA_TRIE
#define ERIKA_TRIE
#include "erika_bv.h"
#include "erika_vcode.h"
#include <map>
#include <string>

namespace erika {
  class value {
    ullong begin_; // beginning position of key
    ullong end_;   // ending position of key
    ullong pos_;   // node position of trie

  public:
    value(ullong begin, ullong end, ullong pos)
     : begin_(begin), end_(end), pos_(pos) {}
    ullong begin() const { return begin_; }
    ullong end()   const { return end_; }
    ullong pos()   const { return pos_; }
  };

  class trie {
    vcode           vc_;
    bv              tail_;
    std::vector<uc> ls_;

    trie(const trie &);
    trie &operator=(const trie &);
    void initialize();
    ullong bsearch(uc label, ullong l, ullong r) const;
    void csearch(const char *key, std::vector<value> &values,
                 bool is_cps, ullong depth, ullong max);
    void dsearch(ullong pos, const std::string &str,
                 std::vector<std::pair<std::string, ullong> > &values);

  public:
    trie();
    trie(std::ifstream &ifs);
    trie(const char *filename);
    ~trie();

    ullong lookup(const char *key);
    void   common_prefix_search(const char *key, std::vector<value> &values);
    void   predictive_search(const char *key,
               std::vector<std::pair<std::string, ullong> > &values);
    void   extract(const char *key, std::vector<value> &values);
    bool   check(const char *key);
    bool   read(std::ifstream &ifs);
    bool   read(const char *filename);
    void   write(std::ofstream &ofs) const;
    void   write(const char *filename, bool is_append = false) const;

    ullong size() const { return this->ls_.size(); }
    void push(uc label, ullong degree, bool is_tail) {
      this->vc_.push(degree);
      this->ls_.push_back(label);
      this->tail_.set(this->size() - 1, is_tail);
    }
    ullong child(ullong pos)   const { return this->vc_.select(pos); }
    ullong parent(ullong pos)  const { return ullong(this->vc_.rank(pos + 1) - 1); }
    ullong degree(ullong pos)  const { return this->vc_.diff(pos + 1); }
    uc     label(ullong pos)   const { return this->ls_[pos]; }
    bool   is_tail(ullong pos) const { return this->tail_.get(pos); }
  };
}

#endif

