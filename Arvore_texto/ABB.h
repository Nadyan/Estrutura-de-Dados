#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#define SIM 1
#define NAO 0
#define MAIOR
#define MENOR
#define IGUAL
#define SUCESSO 1
#define FRACASSO 0

typedef struct ABB *pABB,**ppABB;



/*
operação de criação:
pré-condição: a existência de um apontador adequadamente
declarado e passado por referência para a função juntamente com
o tamanho (a quantidade de bytes) do tipo de informação a ser manipulada.
pós-condição: a criação e inicialização do TDA ABB, atribuição do seu endereço ao
ponteiro passado por referencia. Na ocorrência de algum problema durante a
criação retorna-se a macro FRACASSO, caso contrário retorna-se a macro SUCESSO.*/
int criaABB(ppABB pp, int tamInfo);

/*operação destrutora:
pré-condição: a existência de um apontador declarado externamente a esta função,
devidamente iniciado com o endereço do TDA e cujo endereço (deste apontador)
deve ser passado para a função.
pós-condição: a liberação de qualquer região de memória utilizada pelo TDA
seguida da anulação do ponteiro passado por referencia*/
void destroiABB(ppABB pp);

/* tipo de operação: função de manipulação.
pré condição: a pré existência do TDA cujo endereço é passado para a função.
pós condição: esvaziamento dos dados, o TDA retorna ao estado apresentado
imediatamente após a sua criação. */
void reiniciaABB(pABB p);

//void apagaNoABB(pNoABB p);

int buscaABB(pABB p, void *destino, void *chaveDeBusca, unsigned short (* cmp)(void *p1, void *p2));

int insereABB(pABB p, void *novoReg, unsigned short (* cmp)(void *p1, void *p2));

int removeABB(pABB p, void *chave, unsigned short (* cmp)(void *p1, void *p2), void *copia);

int testaVaziaABB(pABB);





int numFolhas(pABB p);

int emOrdem(pABB pa, void (* processa)(void *p));

int posOrdem(pABB pa, void (* processa)(void *p));

int preOrdem(pABB pa,  void (* processa)(void *p));

void clear_screen();

int montaABB(pABB p, char *doc);

int buscaPalavra(pABB p);
