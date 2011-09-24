#!/bin/sh
TMP=$LANG
export LANG=C
sort -u $1 | erika_make_node > $1.node
erika_make_tail < $1.node | sort -u | erika_make_node \
 | erika_make_trie $1.tail_trie
erika_make_trie $2 $1.tail_trie < $1.node
rm -f $1.node
rm -f $1.tail_trie
export LANG=$TMP

