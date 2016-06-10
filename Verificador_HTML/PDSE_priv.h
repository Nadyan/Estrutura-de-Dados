
typedef struct noPDSE
{
    void *dados;
    struct noPDSE *abaixo;
}NoPDSE,*pNoPDSE;

typedef struct PDSE
{
    int tamInfo;
    pNoPDSE topo;
}PDSE;

