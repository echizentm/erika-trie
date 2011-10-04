#ifndef ERIKA_DEFS
#define ERIKA_DEFS
#include <iostream>
#include <string>

namespace erika {
  typedef unsigned long long ullong;
  typedef unsigned int       uint;
  typedef unsigned char      uc;

  inline ullong popcount64(ullong x) {
    x = ((x & 0xaaaaaaaaaaaaaaaaULL) >> 1)
      +  (x & 0x5555555555555555ULL);
    x = ((x & 0xccccccccccccccccULL) >> 2)
      +  (x & 0x3333333333333333ULL);
    x = ((x & 0xf0f0f0f0f0f0f0f0ULL) >> 4)
      +  (x & 0x0f0f0f0f0f0f0f0fULL);
    x = ((x & 0xff00ff00ff00ff00ULL) >> 8)
      +  (x & 0x00ff00ff00ff00ffULL);
    x = ((x & 0xffff0000ffff0000ULL) >> 16)
      +  (x & 0x0000ffff0000ffffULL);
    x = ((x & 0xffffffff00000000ULL) >> 32)
      +  (x & 0x00000000ffffffffULL);
    return x;
  };

  inline void reverse(std::string &s) {
    ullong len = s.length();
    ullong n   = len / 2;
    for (ullong i = 0; i < n; i++) {
      uc tmp = s[i];
      s[i] = s[len - i - 1];
      s[len - i - 1] = tmp;
    }
  }
}

#endif

