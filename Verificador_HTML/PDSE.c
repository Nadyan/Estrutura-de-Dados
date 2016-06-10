#include "PDSE.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*****************************//******************************/
/****************************PILHA****************************/
/*****************************//******************************/

int cria(ppPDSE pp, int tamInfo)
{
    int ret = FRACASSO;

	if(((*pp) = (pPDSE)malloc(sizeof(PDSE))) == NULL)
    {
		ret = FRACASSO;
    }
	else
	{
	    (*pp)->topo = NULL;
        (*pp)->tamInfo = tamInfo;

        ret = SUCESSO;
	}

    return ret;
}


int insere(pPDSE p, void *novo)
{
    pNoPDSE temp;
    int ret = FRACASSO;

    if((temp = (NoPDSE *)malloc(sizeof(NoPDSE)))!= NULL)
    {
        if((temp->dados = (void *) malloc(p->tamInfo)) != NULL )
        {
             memcpy(temp->dados, novo, p->tamInfo);
             temp->abaixo = p->topo;
             p->topo = temp;
             ret = SUCESSO;
        }
    }
    else
    {
        free(temp);
    }

    return ret;
}


int remover(pPDSE p, void *reg)
{
    int ret = FRACASSO;
    pNoPDSE aux=NULL;

	if(p->topo != NULL)
	{
	    aux = p->topo->abaixo;

        memcpy(reg, p->topo->dados, p->tamInfo);

        free(p->topo->dados);
        free(p->topo);

        p->topo = aux;

        ret = SUCESSO;
	}

   return ret;
}


int busca(pPDSE p, void *reg)
{
    int ret = FRACASSO;

    if(p->topo != NULL)
	{
	    memcpy(reg, p->topo->dados, p->tamInfo);
        ret = SUCESSO;
	}

   return ret;
}


int testaSeVazia(pPDSE p)
{
    if(p->topo != NULL)
        return NAO;
    else
        return SIM;
}


void reinicia(pPDSE p)
{
    pNoPDSE aux = NULL;

    if(p->topo != NULL)
	{
	    aux = p->topo->abaixo;

	    while(aux != NULL)
		{
            free(p->topo->dados);
		 	free(p->topo);

		 	p->topo=aux;

		 	aux = p->topo->abaixo;
		}

	   free(p->topo->dados);
       free(p->topo);

       p->topo = NULL;
	}
}


void destroi(ppPDSE pp)
{
	reinicia(*pp);

	free(*pp);

    (*pp) = NULL;
}
