#include <iostream>
#include <list>
#include <vector>
// #include "Page.cpp"
#include "BufferPool.cpp"


int main() {

  BufferPool bp;
  FILE *file;

  cria_buffer(bp, 5);

  file = fopen("txt/R62500.txt", "r+");

  aloca_pagina(bp,file,0);
  grava_pagina(bp,file,0);
  mostra_paginas(bp);

  return 0;
}
