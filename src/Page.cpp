// Pagina:
#include <list>
#define MAX_SIZE 8192

int CURRENT_SIZE; //controle do tamanho atual da pagina

struct Slot {
  int pos;
  int tamanho;
};

struct DirDeSlots {
  int nroSlots;  //4 Bytes
  int freeSpace; //4 Bytes
  std::list<Slot> l;
};

struct Page {
  int id; //4Bytes
  char dados[];
  DirDeSlots ds;  
};

//Funcoes de Controle:
void aloca_pagina();
void cria_diretorio_slots ();
