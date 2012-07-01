CC  = /usr/bin/g++
BIN = /usr/local/bin/
LIB = /usr/local/lib/
INC = /usr/local/include/
SRC = erika_bv.cc erika_vcode.cc erika_trie.cc
HDR = erika_defs.h erika_bv.h erika_vcode.h erika_trie.h
LIBPERL = $(shell ./find_libperl.pl)
UNAME = $(shell uname)

erika: liberika tools

tools: liberika $(SRC) \
       erika_make_node.cc erika_make_trie.cc \
       erika_make_tail.cc erika_make_value.cc \
       erika_extract.cc erika_predictive_search.cc \
       erika_common_prefix_search.cc \
       erika_extract_plus.cc
	$(CC) -O2 -Wall -g erika_make_node.cc -o erika_make_node
	$(CC) -O2 -Wall -g erika_make_trie.cc $(SRC) -o erika_make_trie
	$(CC) -O2 -Wall -g erika_make_tail.cc $(SRC) -o erika_make_tail
	$(CC) -O2 -Wall -g erika_make_value.cc $(SRC) -o erika_make_value
	$(CC) -O2 -Wall -g erika_extract.cc $(SRC) -o erika_extract
	$(CC) -O2 -Wall -g erika_predictive_search.cc $(SRC) \
                    -o erika_predictive_search
	$(CC) -O2 -Wall -g erika_common_prefix_search.cc $(SRC) \
                    -o erika_common_prefix_search
	$(CC) -O2 -Wall -g erika_extract_plus.cc $(SRC) -o erika_extract_plus

liberika: $(SRC) $(HDR)
ifeq ($(UNAME), Darwin)
#	swig -c++ -perl -shadow -o erika_trie_perl.cc erika_trie_perl.i
	$(CC) -O2 -fno-common -Wall -fPIC -g -c erika_trie_perl.cc -I$(LIBPERL)CORE/
	$(CC) -O2 -fno-common -Wall -fPIC -g -c erika_bv.cc
	$(CC) -O2 -fno-common -Wall -fPIC -g -c erika_vcode.cc
	$(CC) -O2 -fno-common -Wall -fPIC -g -c erika_trie.cc
	$(CC) -O2 -Wall -g -dynamiclib -install_name=$(LIB)liberika.1.0.dylib \
          -o liberika.1.0.dylib erika_bv.o erika_vcode.o erika_trie.o
	$(CC) -O2 -Wall -g -dynamiclib -install_name=$(LIB)Erika.dylib \
          -o Erika.dylib \
          erika_trie_perl.o erika_bv.o erika_vcode.o erika_trie.o \
          -lstdc++ -lperl -L$(LIBPERL)CORE/
else
	$(CC) -O2 -Wall -fPIC -g -c erika_trie_perl.cc -I$(LIBPERL)CORE/
	$(CC) -O2 -Wall -fPIC -g -c erika_bv.cc
	$(CC) -O2 -Wall -fPIC -g -c erika_vcode.cc
	$(CC) -O2 -Wall -fPIC -g -c erika_trie.cc
	$(CC) -O2 -Wall -g -shared -Wl,-soname,liberika.so.1 \
          -o liberika.so.1.0 erika_bv.o erika_vcode.o erika_trie.o
	$(CC) -O2 -Wall -g -shared -Wl,-soname,Erika.so \
          -o Erika.so \
          erika_trie_perl.o erika_bv.o erika_vcode.o erika_trie.o \
          -lstdc++ -lperl -L$(LIBPERL)CORE/
endif
#	- rm erika_trie_perl.cc
	- rm erika_trie_perl.o
	- rm erika_bv.o
	- rm erika_vcode.o
	- rm erika_trie.o

clean:
	- rm -f erika_make_node
	- rm -f erika_make_trie
	- rm -f erika_make_tail
	- rm -f erika_make_value
	- rm -f erika_extract
	- rm -f erika_predictive_search
	- rm -f erika_common_prefix_search
	- rm -f erika_extract_plus
	- rm -f liberika.so.1.0
	- rm -f liberika.1.0.dylib
	- rm -f Erika.so
	- rm -f Erika.dylib
#	- rm -f Erika.pm
	- rm -Rf *.dSYM

install:
ifeq ($(UNAME), Linux)
	cp liberika.so.1.0 $(LIB)
	/sbin/ldconfig -n $(LIB)
	ln -fs $(LIB)liberika.so.1 $(LIB)liberika.so
	cp Erika.so $(LIBPERL)
	cp Erika.pm $(LIBPERL)
else
ifeq ($(UNAME), Darwin)
	cp liberika.1.0.dylib $(LIB)
	ln -fs $(LIB)liberika.1.0.dylib $(LIB)liberika.1.dylib
	ln -fs $(LIB)liberika.1.dylib $(LIB)liberika.dylib
	cp Erika.dylib $(LIBPERL)
	cp Erika.pm $(LIBPERL)
else
	cp liberika.so.1.0 $(LIB)
	ln -fs $(LIB)liberika.so.1.0 $(LIB)liberika.so.1
	/sbin/ldconfig -m $(LIB)
	ln -fs $(LIB)liberika.so.1 $(LIB)liberika.so
	cp Erika.so $(LIBPERL)
	cp Erika.pm $(LIBPERL)
endif
endif
	cp erika_*.h                  $(INC)
	cp erika_make_node            $(BIN)
	cp erika_make_trie            $(BIN)
	cp erika_make_tail            $(BIN)
	cp erika_make_value           $(BIN)
	cp erika_*.sh                 $(BIN)
	cp erika_extract              $(BIN)
	cp erika_predictive_search    $(BIN)
	cp erika_common_prefix_search $(BIN)
	cp erika_extract_plus         $(BIN)

uninstall:
	- rm -f $(LIB)liberika.so
	- rm -f $(LIB)liberika.so.1
	- rm -f $(LIB)liberika.so.1.0
	- rm -f $(LIB)liberika.dylib
	- rm -f $(LIB)liberika.1.dylib
	- rm -f $(LIB)liberika.1.0.dylib
	- rm -f $(LIBPERL)Erika.so
	- rm -f $(LIBPERL)Erika.dylib
	- rm -f $(LIBPERL)Erika.pm
	- rm -f $(INC)erika_*.h
	- rm -f $(BIN)erika_make_node
	- rm -f $(BIN)erika_make_trie
	- rm -f $(BIN)erika_make_tail
	- rm -f $(BIN)erika_make_value
	- rm -f $(BIN)erika_*.sh
	- rm -f $(BIN)erika_extract
	- rm -f $(BIN)erika_predictive_search
	- rm -f $(BIN)erika_common_prefix_search
	- rm -f $(BIN)erika_extract_plus

