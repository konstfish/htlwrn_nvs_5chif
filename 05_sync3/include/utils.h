#pragma once

#include <iostream>
#include <mutex>

// habs versucht, templates wollten nicht: mein error log war dieses:

/*
      Philosopher::operator()() in src_Philosopher.cpp.o
  "void println<char [12], std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, char [45]>(char const (&) [12], std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const&, char const (&) [45])", referenced from:
      Philosopher::operator()() in src_Philosopher.cpp.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
ninja: build stopped: subcommand failed.
*/

// daraus ist eh erkennbar, dass es ein linker fehler ist aber stackoverflow hat mir leider nicht geholfen