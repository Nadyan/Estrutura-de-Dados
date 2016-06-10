#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "PDSE_priv.h"

#define FRACASSO 0
#define SUCESSO 1

#define NAO 0
#define SIM 1



typedef struct PDSE *pPDSE, **ppPDSE;

void verifica(pPDSE p, char *doc);

int cria(ppPDSE pp, int tamInfo);

int insere(pPDSE p, void *novo);

void reinicia(pPDSE p);

int testaSeVazia(pPDSE p);

void destroi(ppPDSE pp);

int busca(pPDSE p, void *reg);

int remover(pPDSE p, void *reg);

void clear_screen();

