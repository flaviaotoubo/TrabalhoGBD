// BufferPool
#include <vector>
#include "Page.cpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>

struct Frame {
  Page* pagina;
  int pinCount;
  int dirtyBit;
};

struct BufferPool {
  int size;			// Total de Frames
  int next;			// Indica proximo Frame vazio (inicio)
  Frame* frames;		// array de frames
  list<int> politicaSubs; // lista com indices de frame, em ordem decrescente de tempos
  // Usando: LRU
};

void cria_buffer(BufferPool& bp, int size) {

  bp.frames = (Frame*) malloc (size*sizeof(Frame));
  bp.size = size;
  bp.next = 0;
}

Page* le_pagina(BufferPool& bp, FILE* file, int pageId) {

  char dados1[11];   char dados2[11];
  int tamanho_pagina = CURRENT_SIZE;
  int pular_paginas = (pageId) * 23 * tamanho_pagina;

  fseek(file, pular_paginas, SEEK_SET);

  Page* pagina = cria_pagina();
  pagina->id = pageId;

  for (int i = 0; i < CURRENT_SIZE; ++i) {

    fgets(dados1, 11, file);
    fseek(file, 1, SEEK_CUR);

    fgets(dados2, 11, file);
    fseek(file, 2, SEEK_CUR);

    aloca_registro(pagina, dados1, dados2);
  }
  
  return pagina;
}

void aloca_pagina(BufferPool& bp, FILE* file, int pageId) {
  
  Page* p = le_pagina(bp, file, pageId);

  if (bp.next < bp.size ) {	// Se o Buffer nao esta cheio ainda 

    bp.frames[bp.next].pinCount = bp.frames[bp.next].dirtyBit = 0;
    bp.frames[bp.next].pagina = p;

    bp.politicaSubs.push_back(bp.next);
    bp.next++;

  }

  else { // se está cheio -> Politica de Substituicao de Pagina:


    // POLITICA LRU:
    int libera = bp.politicaSubs.front();
    bp.politicaSubs.pop_front();

    bp.frames[libera].pagina = p;
    bp.politicaSubs.push_back(libera);
  }    
}

void mostra_paginas(BufferPool bp) {

  int i,j;
  
  for (i = 0; i < bp.next; ++i) {

    for (j = 0; j < CURRENT_SIZE; ++j) {

      printf("%s ; %s<>\n", bp.frames[i].pagina->registros.at(j).atributo1, bp.frames[i].pagina->registros.at(j).atributo2);

    }
  }
}

void grava_pagina(BufferPool& bp, FILE* file, int pageId) {

  for (int i = 0; i < bp.next; ++i) {

    if (bp.frames[i].pagina->id == pageId) {

      fseek(file, pageId * 23 * CURRENT_SIZE,SEEK_SET);

      for (int j = 0; j < CURRENT_SIZE; ++j) {
	char *a = bp.frames[i].pagina->registros.at(j).atributo1;
	fputs(a, file); fflush(file);	
	fputc(',', file); fflush(file);

	char *b = bp.frames[i].pagina->registros.at(j).atributo2;
	fputs(b, file); fflush(file);
	fputs("\r\n", file); fflush(file);

	
      }

      break;
    }

  }

}
