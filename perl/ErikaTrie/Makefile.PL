use ExtUtils::MakeMaker;
WriteMakefile(
  NAME         => 'ErikaTrie',
  VERSION_FROM => 'lib/ErikaTrie.pm',
  LIBS         => ['-L/usr/lib -L/usr/local/lib -lerika'],
  INC          => '-I. -I/usr/include',
  CC           => '/usr/bin/g++ -O2',
  LD           => '/usr/bin/g++ -O2',
  XSOPT        => '-C++',
  TYPEMAPS     => ['perlobject.map' ],
);

