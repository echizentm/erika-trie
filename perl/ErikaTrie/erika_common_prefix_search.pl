#!/usr/bin/env perl -Iblib/lib -Iblib/arch
use strict;
use warnings;
use ErikaTrie;

my $filename = shift @ARGV;
my $t = ErikaTrie->new($filename);
while (my $key = <>) {
  chomp($key);
  my $value = $t->common_prefix_search($key);
  my $line = "";
  foreach my $elem (@$value) {
    $line .= "$elem->{word}";
    $line .= ":".($t->value($elem->{pos})) if ($t->is_value());
    $line .= ":$elem->{begin}:$elem->{end},";
  }
  chop($line);
  print "$line\n";
}

