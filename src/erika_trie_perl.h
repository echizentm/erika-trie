#ifndef ERIKA_TRIE_PERL
#define ERIKA_TRIE_PERL
#include "erika_trie.h"
#include <string>
#include <sstream>

class Trie {
  erika::trie t_;
  std::string s_;

public:
  Trie(const char *filename) : t_(filename) {}
  ~Trie() {}

  unsigned long long lookup(const char *key) {
    return this->t_.lookup(key);
  }
  const char *common_prefix_search(const char *key) {
    this->s_ = "common prefix search.";
    return this->s_.c_str();
  }
  const char *predictive_search(const char *key) {
    this->s_ = "predictive search.";
    return this->s_.c_str();
  }   
  const char *extract(const char *key) {
    std::vector<erika::result> r;
    this->t_.extract(key, r);

    std::stringstream ss;
    std::string sep = "";
    std::vector<erika::result>::const_iterator i = r.begin();
    std::vector<erika::result>::const_iterator e = r.end();
    while (i != e) {
      std::string word = std::string(key, i->begin(), i->end() - i->begin());
      ss << sep << word << ":" << i->begin() << ":" << i->end();
      sep = ",";
      i++;
    }
    this->s_ = ss.str();
    return this->s_.c_str();
  }
};

#endif

