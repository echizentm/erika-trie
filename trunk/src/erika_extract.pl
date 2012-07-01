#!/usr/bin/env perl
use strict;
use warnings;
use Erika;

my $filename = shift @ARGV;
my $t = Erika::Trie->new($filename);
while (my $key = <>) {
  chomp($key);
  print $t->extract($key)."\n";
}

