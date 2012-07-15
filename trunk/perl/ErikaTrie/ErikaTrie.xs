#include "erika_trie.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#ifdef __cplusplus
}
#endif

#ifdef vform
#undef vform
#endif

#include "ppport.h"
using namespace std;
using namespace erika;

MODULE = ErikaTrie		PACKAGE = ErikaTrie	

trie *
trie::new(filename)
char *filename;
CODE:
  trie *t = new trie(filename);
  RETVAL = t;
OUTPUT:
  RETVAL

void
trie::DESTROY()

long
trie::lookup(key)
char *key
CODE:
  RETVAL = THIS->lookup(key);
OUTPUT:
  RETVAL

int
trie::is_value()
CODE:
  RETVAL = THIS->is_value();
OUTPUT:
  RETVAL

SV *
trie::value(pos)
long pos
CODE:
  string value = "";
  if (THIS->is_value()) {
    value = THIS->value(pos);
  }
  RETVAL = newSVpv(value.c_str(), value.length());
OUTPUT:
  RETVAL

int
trie::check(key)
char *key
CODE:
  RETVAL = THIS->check(key);
OUTPUT:
  RETVAL

AV *
trie::extract(key)
char *key
CODE:
  AV *av = (AV *)sv_2mortal((SV *)newAV());

  vector<result> r;
  THIS->extract(key, r);
  vector<result>::const_iterator i = r.begin();
  vector<result>::const_iterator e = r.end();
  while (i != e) {
    string word = string(key, i->begin(), i->end() - i->begin());

    HV *hv = (HV *)sv_2mortal((SV *)newHV());

    SV *sv_word = sv_2mortal(newSVpv(word.c_str(), word.length()));
    SvREFCNT_inc(sv_word);
    if (!hv_store(hv, "word", 4, sv_word, 0)) {
      SvREFCNT_dec(sv_word);
    }
    SV *sv_pos = sv_2mortal(newSVuv(i->pos()));
    SvREFCNT_inc(sv_pos);
    if (!hv_store(hv, "pos", 3, sv_pos, 0)) {
      SvREFCNT_dec(sv_pos);
    }
    SV *sv_begin = sv_2mortal(newSVuv(i->begin()));
    SvREFCNT_inc(sv_begin);
    if (!hv_store(hv, "begin", 5, sv_begin, 0)) {
      SvREFCNT_dec(sv_begin);
    }
    SV *sv_end = sv_2mortal(newSVuv(i->end()));
    SvREFCNT_inc(sv_end);
    if (!hv_store(hv, "end", 3, sv_end, 0)) {
      SvREFCNT_dec(sv_end);
    }
    SV *rv = newRV_inc((SV *)hv);
    av_push(av, rv);
    i++;
  }

  RETVAL = av;
OUTPUT:
  RETVAL

AV *
trie::common_prefix_search(key)
char *key
CODE:
  AV *av = (AV *)sv_2mortal((SV *)newAV());

  vector<result> r;
  THIS->common_prefix_search(key, r);
  vector<result>::const_iterator i = r.begin();
  vector<result>::const_iterator e = r.end();
  while (i != e) {
    string word = string(key, i->begin(), i->end() - i->begin());

    HV *hv = (HV *)sv_2mortal((SV *)newHV());

    SV *sv_word = sv_2mortal(newSVpv(word.c_str(), word.length()));
    SvREFCNT_inc(sv_word);
    if (!hv_store(hv, "word", 4, sv_word, 0)) {
      SvREFCNT_dec(sv_word);
    }
    SV *sv_pos = sv_2mortal(newSVuv(i->pos()));
    SvREFCNT_inc(sv_pos);
    if (!hv_store(hv, "pos", 3, sv_pos, 0)) {
      SvREFCNT_dec(sv_pos);
    }
    SV *sv_begin = sv_2mortal(newSVuv(i->begin()));
    SvREFCNT_inc(sv_begin);
    if (!hv_store(hv, "begin", 5, sv_begin, 0)) {
      SvREFCNT_dec(sv_begin);
    }
    SV *sv_end = sv_2mortal(newSVuv(i->end()));
    SvREFCNT_inc(sv_end);
    if (!hv_store(hv, "end", 3, sv_end, 0)) {
      SvREFCNT_dec(sv_end);
    }
    SV *rv = newRV_inc((SV *)hv);
    av_push(av, rv);
    i++;
  }

  RETVAL = av;
OUTPUT:

AV *
trie::predictive_search(key)
char *key
CODE:
  AV *av = (AV *)sv_2mortal((SV *)newAV());

  vector<pair<string, ullong> > r;
  THIS->predictive_search(key, r);
  vector<pair<string, ullong> >::const_iterator i = r.begin();
  vector<pair<string, ullong> >::const_iterator e = r.end();
  while (i != e) {
    string word = i->first;

    HV *hv = (HV *)sv_2mortal((SV *)newHV());

    SV *sv_word = sv_2mortal(newSVpv(word.c_str(), word.length()));
    SvREFCNT_inc(sv_word);
    if (!hv_store(hv, "word", 4, sv_word, 0)) {
      SvREFCNT_dec(sv_word);
    }
    SV *sv_pos = sv_2mortal(newSVuv(i->second));
    SvREFCNT_inc(sv_pos);
    if (!hv_store(hv, "pos", 3, sv_pos, 0)) {
      SvREFCNT_dec(sv_pos);
    }
    SV *rv = newRV_inc((SV *)hv);
    av_push(av, rv);
    i++;
  }

  RETVAL = av;
OUTPUT:
