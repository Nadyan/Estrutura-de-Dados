#include "ABB.h"
#include "ABB_priv.h"
#include "math.h"



int criaABB(ppABB pp, int tamInfo)
{  int ret = FRACASSO;
   if ((*pp = (pABB) malloc(sizeof(ABB))) != NULL )
      {	(*pp)->raiz = NULL;
	(*pp)->tamInfo = tamInfo;
	ret = SUCESSO;
      }
	return ret;
}


void destroiABB(ppABB pp)
{  reiniciaABB(*pp);
   free(*pp);
   (*pp)= NULL;
}


void reiniciaABB(pABB p)
{
   apagaNoABB(p->raiz);
   p->raiz = NULL;
}

int buscaABB(pABB p, void *destino, void *chaveDeBusca, unsigned short(* cmp)(void *p1, void *p2))
{
    pNoABB aux1;

    unsigned int ret = FRACASSO;

    aux1 = p->raiz;

    while(aux1 != NULL && (*cmp)(chaveDeBusca,aux1->dados) != '=')
            aux1 = (*cmp)(chaveDeBusca,aux1->dados)== '<' ? aux1->esq : aux1->dir;

    if (aux1 != NULL)
    {
            memcpy(destino, aux1->dados, p->tamInfo);
            ret = SUCESSO;
    }
    return ret;
}


int insereABB(pABB pa, void *novoReg, unsigned short (* cmp)(void *p1, void *p2))
{  	pNoABB p, q, novoNoABB;


    	p = q = pa->raiz;
 	while( p != NULL )
      	{  if ( (*cmp)(novoReg,p->dados) == '=')
               	return FRACASSO;  /* registro já inserido previamente */
            else
     		{   	q = p;
			p = ((*cmp)(novoReg,p->dados)== '<') ? p->esq : p->dir;
                }
        }


  	if ((novoNoABB = (pNoABB) malloc (sizeof(NoABB))) != NULL)
    	{
		if((novoNoABB->dados = (void *)malloc(pa->tamInfo)) !=NULL)
	        {	memcpy(novoNoABB->dados, novoReg, pa->tamInfo);
	         	novoNoABB->dir = novoNoABB->esq = NULL; /* insere nova folha */

	            	if (q != NULL)
	                	if( (*cmp)(novoNoABB->dados,q->dados) == '<')/*ou (*cmp)(novoReg,q->dados)*/
	                	    q->esq = novoNoABB;
				else
               			     q->dir=novoNoABB;
            		else
		                pa->raiz = novoNoABB;   /* árvore com um único nó */
           		return SUCESSO;
        	}
        	else
            		free(novoNoABB);
    }
    return FRACASSO;  /* não conseguiu alocar memória */
}


int removeABB(pABB pa, void *chaveDeBusca, unsigned short (* cmp)(void *p1, void *p2), void *copia)
{	char ch;
	pNoABB subst, paiSubst, alvo, paiDoAlvo, avante;
   	paiDoAlvo = NULL;
	alvo = pa->raiz;
   	while (alvo != NULL && (ch=(*cmp)(chaveDeBusca,alvo->dados)) != '=')
	{	paiDoAlvo = alvo;
  		alvo = (ch == '<' ? alvo->esq : alvo->dir);
	}

   	if (alvo==NULL)   /*alvo não encontrado */
		return FRACASSO;

	if (alvo->esq == NULL)
		if (alvo->dir == NULL) // alvo é uma folha
			subst = NULL;
		else
			subst = alvo->dir; /*alvo possui apenas um filho à dir*/

	else
		if(alvo->dir == NULL)
			subst = alvo->esq; /*alvo possui apenas um filho à esq*/

		else  /* alvo possui os dois filhos*/
		{    	/* determinando o substituto pelo sucessor em ordem: */
			paiSubst = alvo;
		     	subst = alvo->dir;
		     	avante = alvo->esq;
		     	while( avante != NULL)
                	{   paiSubst = subst;
	                    subst = avante;
        	            avante = avante->esq;
        	        }


			if(paiSubst != alvo)
	 	        {  	paiSubst->esq = subst->dir;
				subst->dir = alvo->dir;
 		        }
 		     	subst->esq = alvo->esq; /*o pai do substituto eh o proprio alvo */
	    }

	 if(pa->raiz == alvo) // ou seja se "paiDoAlvo = NULL"
       		pa->raiz = subst; /*alvo era a raiz*/
	 else
	    	alvo == paiDoAlvo->esq ? (paiDoAlvo->esq = subst) : (paiDoAlvo->dir = subst);

	memcpy(copia,alvo->dados,pa->tamInfo);
    	free(alvo->dados);
	free(alvo);
	return SUCESSO;
}


int testaVaziaABB(pABB p)
{ return (p->raiz == NULL ? SIM : NAO);
}


int preOrdem(pABB pa, void (* processa)(void *p))
{   if(pa->raiz == NULL)
        return FRACASSO;
    else
    {
        percorreEmPreOrdem(pa->raiz, processa);
        return SUCESSO;
    }

}

int posOrdem(pABB pa, void (* processa)(void *p))
{   if(pa->raiz == NULL)
        return FRACASSO;
    else
    {
        percorreEmPosOrdem(pa->raiz, processa);
        return SUCESSO;
    }

}

int emOrdem(pABB pa,  void (* processa)(void *p))
{   if(pa->raiz == NULL)
        return FRACASSO;
    else
     {  percorreEmOrdem(pa->raiz, processa);
        return SUCESSO;
     }

}



int numFolhas(pABB p)
{   if(p!=NULL)
        return calcNumFolhas(p->raiz);
    return 0;
}
