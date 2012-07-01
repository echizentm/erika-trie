#!/usr/bin/env perl
use strict;
use warnings;

foreach my $path (@INC) {
  $path =~ s/\/$//;
  if (-d "$path/CORE/") {
    print "$path/\n";
    last;
  }
}

