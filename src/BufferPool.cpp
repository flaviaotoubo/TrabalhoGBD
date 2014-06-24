// BufferPool
#include <vector>
#include "Page.cpp"
#include <cstdio>
#include <iostream>

struct Frame {
  Page pagina;
  int pinCount;
  int dirtyBit;
};

struct BufferPool {
  vector<Frame> frames;
};

void aloca_pagina(BufferPool& bp){//, Identificador N, TamanhoBuffer B) {
  
  bp.frames.resize(bp.frames.size());
 
}

void le_pagina(BufferPool& bp, FILE* file, int pageId) {

  char dados1[11];   char dados2[11];
  int tamanho_pagina = CURRENT_SIZE - 1;
  int pular_paginas = (pageId) * 23 * tamanho_pagina;

  fseek(file, pular_paginas, SEEK_SET);
  Page pagina = cria_pagina();
  pagina.id = pageId;

  for (int i = 0; i < CURRENT_SIZE; ++i) {

    fscanf(file, "%10s", dados1);
    fseek(file, 1, SEEK_CUR);

    fscanf(file, "%10s", dados2);
    fseek(file, 2, SEEK_CUR);

    aloca_registro(pagina, dados1, dados2);
  }
  
  Frame f;
  f.pagina = pagina;
  f.pinCount = f.dirtyBit = 0;
  bp.frames.push_back(f);

}

void mostra_paginas(BufferPool& bp) {

  unsigned int i;
  int j;

  for (i = 0; i < bp.frames.size(); ++i) {
    for (j = 0; j < CURRENT_SIZE; ++j) {

  // for (i = 0; i < 1; ++i) {
  //   for (j = 0; j < 1; ++j) {

      printf("%s, %s\n", bp.frames.at(i).pagina.registros.at(j).atributo1, bp.frames.at(i).pagina.registros.at(j).atributo1);

      // printf("%s, %s\n", bp.frames.at(i).pagina.registros.at(j).atributo1, bp.frames.at(i).pagina.registros.at(j).atributo1);
    }
  }
}
