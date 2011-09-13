#!/bin/sh
TMP=$LANG
export LANG=C
sort $1 | erika_make_node | erika_make_trie $2 
export LANG=$TMP

