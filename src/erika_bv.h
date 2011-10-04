#ifndef ERIKA_BV
#define ERIKA_BV
#include "erika_defs.h"
#include <map>
#include <vector>
#include <fstream>

namespace erika {
  class tiny_bv {
    ullong B_[4];
    uc     r_[4];

  public:
    tiny_bv();
    void   set(ullong i, bool b = true);
    bool   get(ullong i) const;
    void   build();
    ullong rank(ullong i) const;
    void   write(std::ofstream &ofs) const;
    bool   read(std::ifstream &ifs);
  };


  typedef std::pair<tiny_bv, ullong> tbv_pair;

  class bv {
    std::vector<tbv_pair> tbv_;

  public:
    void   set(ullong i, bool b = true);
    bool   get(ullong i) const;
    void   build();
    ullong rank(ullong i, bool b = true) const;
    ullong select(ullong i, bool b = true) const;
    void   write(std::ofstream &ofs) const;
    void   write(const char *filename, bool is_append = false) const;
    bool   read(std::ifstream &ifs);
    bool   read(const char *filename);
  };
}

#endif

