// Pagina:

#include <list>
#include <vector>
#include <cstring>
#include <cstdlib>

#define MAX_SIZE 10240		// 10 KB = 10240 Bytes = 512 registros/pagina

using namespace std;

// VARIAVEIS GLOBAIS
int g_id = 0;
int CURRENT_SIZE = 512; //reg/ pag; controle do tamanho atual da pagina

struct Slot {			// 8 Bytes
  int pos;			// 4 Bytes
  int tamanho;			// 4 Bytes
};

struct DirSlots {		// 8 + 8 * nroSlots Bytes
  int nroSlots;  		// 4 Bytes
  int freeSpace; 		// 4 Bytes
  vector<Slot> l;			// 8 * nroSlots Bytes // sizeof = 16
};

struct Register {		// 20 Bytes
  int nroPagina;		//  4 Bytes
  int nroSlot;			//  4 Bytes
  char atributo1[11]; 		// 10 Bytes
  char atributo2[11]; 		// 10 Bytes
};

struct Page {
  int id; 			// 4 Bytes
  vector<Register> registros;   // 
  DirSlots ds;  		// 8 + 8 * nroSlots Bytes // sizeof = 24
};


//Funcoes de Controle:
DirSlots cria_diretorio_slots() {
  DirSlots ds;
  ds.nroSlots = 0;
  ds.freeSpace = 0;
  return ds;
}

Page* cria_pagina() {

  Page* p = (Page*) malloc (sizeof(Page));

  p->id = g_id++;
  p->ds = cria_diretorio_slots();

  return p;
}


void aloca_registro(Page* pagina, char* dados1, char* dados2) {

  Register reg;

  reg.nroPagina = pagina->id;
  reg.nroSlot = pagina->ds.nroSlots++;

  strcpy(reg.atributo1, dados1);
  strcpy(reg.atributo2, dados2);

  pagina->registros.push_back(reg);;
  
}
