#ifndef ERIKA_VCODE
#define ERIKA_VCODE
#include <fstream>
#include <vector>

namespace erika {
  typedef unsigned long long ullong;
  typedef unsigned int       uint;

  class vcode {
    std::vector<uint>   cMSB_;
    std::vector<ullong> base_;
    std::vector<ullong> V_;
    ullong              size_;
    ullong              block_size_;

    vcode(const vcode &);
    vcode &operator=(const vcode &);
    void initialize();

  public:
    vcode();
    vcode(std::ifstream &ifs);
    vcode(const char *filename);
    ~vcode();

    ullong size() const;
    void   push(ullong d);
    ullong select(ullong pos) const;
    ullong rank(ullong pos) const;
    ullong diff(ullong pos) const;

    bool read(std::ifstream &ifs);
    bool read(const char *filename);
    void write(std::ofstream &ofs) const;
    void write(const char *filename, bool is_append = false) const;
  };
}

#endif

