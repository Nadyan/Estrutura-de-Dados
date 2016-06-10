#include "ABB_priv.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void apagaNoABB(pNoABB p)
{ if(p!=NULL)
   {   apagaNoABB(p->esq);
       apagaNoABB(p->dir);
       free( p->dados );
       free(p);
   }

}



void percorreEmPreOrdem(pNoABB p,  void (* processa)(void *p))
{  if(p != NULL)
    { processa(p->dados);
      percorreEmPreOrdem(p->esq, processa);
      percorreEmPreOrdem(p->dir, processa);
    }
}

void percorreEmOrdem(pNoABB p,  void (* processa)(void *p))
{  if(p != NULL)
    { percorreEmOrdem(p->esq, processa);
      processa(p->dados);
      percorreEmOrdem(p->dir, processa);
    }
}

void percorreEmPosOrdem(pNoABB p, void (* processa)(void *p))
{ if(p != NULL)
    { percorreEmPosOrdem(p->esq, processa);
      percorreEmPosOrdem(p->dir, processa);
      processa(p->dados);
    }
}



int calcNumFolhas(pNoABB p)
{   if(!p)
     return 0;
    else
     if(!(p->esq) && !(p->dir))
        return 1;
     else
        return calcNumFolhas(p->esq)+calcNumFolhas(p->dir);
}


