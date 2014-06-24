#include <iostream>
#include <list>
#include <vector>
// #include "Page.cpp"
#include "BufferPool.cpp"


int main() {

  BufferPool bp;
  FILE *file;

  file = fopen("txt/R62500.txt", "r");

  aloca_pagina(bp);
  le_pagina(bp, file, 0);
  // mostra_paginas(bp);
  // cout << "size: " << bp.frames.size() << endl;

  return 0;
}
