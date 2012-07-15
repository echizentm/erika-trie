use ExtUtils::MakeMaker;
WriteMakefile(
  NAME         => 'ErikaTrie',
  VERSION_FROM => 'lib/ErikaTrie.pm',
  LIBS         => ['-L/usr/lib -L/usr/local/lib -lerika'],
  INC          => '-I. -I/usr/include',
  CC           => '/usr/bin/g++',
  LD           => '/usr/bin/g++',
  XSOPT        => '-C++',
  TYPEMAPS     => ['perlobject.map' ],
);

