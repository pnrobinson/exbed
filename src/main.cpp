

#include <iostream>
#include "euclidean.h"





int main(int argc,char ** argv) {
  if (argc != 2) {
    std::cerr << "usage exbed ..hn2v-output-file\n";
    exit(EXIT_FAILURE);
  }
  Parser parser{argv[1]};
  parser.status();




}
