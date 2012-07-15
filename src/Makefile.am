AM_CXXFLAGS = -Wall -g -O2

lib_LTLIBRARIES = liberika.la

liberika_la_SOURCES = \
  erika_trie.cc \
  erika_bv.cc \
  erika_vcode.cc

include_HEADERS = \
  erika_trie.h \
  erika_bv.h \
  erika_vcode.h \
  erika_defs.h

bin_PROGRAMS = \
  erika_make_node \
  erika_make_trie \
  erika_make_value \
  erika_make_tail \
  erika_common_prefix_search \
  erika_predictive_search \
  erika_extract \
  erika_extract_plus

erika_make_node_SOURCES = \
  erika_make_node.cc
erika_make_node_LDADD = \
  liberika.la

erika_make_trie_SOURCES = \
  erika_make_trie.cc
erika_make_trie_LDADD = \
  liberika.la

erika_make_value_SOURCES = \
  erika_make_value.cc
erika_make_value_LDADD = \
  liberika.la

erika_make_tail_SOURCES = \
  erika_make_tail.cc
erika_make_tail_LDADD = \
  liberika.la

erika_common_prefix_search_SOURCES = \
  erika_common_prefix_search.cc
erika_common_prefix_search_LDADD = \
  liberika.la

erika_predictive_search_SOURCES = \
  erika_predictive_search.cc
erika_predictive_search_LDADD = \
  liberika.la

erika_extract_SOURCES = \
  erika_extract.cc
erika_extract_LDADD = \
  liberika.la

erika_extract_plus_SOURCES = \
  erika_extract_plus.cc
erika_extract_plus_LDADD = \
  liberika.la

bin_SCRIPTS = \
  erika_make.sh \
  erika_make_vt.sh \
  erika_make_tt.sh

