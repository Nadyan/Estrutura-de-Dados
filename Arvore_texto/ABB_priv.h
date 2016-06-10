#include "ABB.h"

typedef struct noABB
{
    void *dados;
    struct noABB *esq;
    struct noABB *dir;
} NoABB,*pNoABB;

typedef struct ABB
{
    pNoABB raiz;
    int tamInfo;
}ABB, *pABB;

void apagaNoABB(pNoABB p);

void percorreEmPreOrdem(pNoABB pa, void (* processa)(void *p));
void percorreEmPosOrdem(pNoABB pa, void (* processa)(void *p));
void percorreEmOrdem(pNoABB pa,  void (* processa)(void *p));
int calcNumFolhas(pNoABB p);

