#include "cliente.h"


int main(int argc, char *argv[ ])
{
    pABB p = NULL;
    char *arquivo;
    arquivo = (char*)malloc(sizeof(char)*100);
    int opc, foiCriada;

    if(argc != 1) //SE FOI PASSADO O DOCUMENTO POR LINHA DE COMANDO
    {
        strcpy(arquivo, argv[1]); //PASSA O DOCUMENTO DE ARGV PARA 'ARQUIVO'
    }
    else
    {
        strcpy(arquivo, "teste.txt"); //SE NAO, ABRE O DOCUMENTO PADRAO
    }

        if(criaABB(&p, sizeof(info)) == SUCESSO) //TESTA SE A ARVORE FOI CRIADA COM SUCESSO
            foiCriada = 1;
        else
            foiCriada = 0;

        do
        {
            printf("\n\n     PESQUISA DE PALAVRAS EM ARVORE BINARIA\n\n");
            printf("           Informe a operacao:\n\n");
            printf("        1 - Inserir documento\n");
            printf("        2 - Buscar palavra\n");
            printf("        0 - Sair\n\n");

            printf("        ");
            scanf("%d", &opc);
            printf("\n");

            switch(opc)
            {
                case 1:
                    clear_screen();

                    if (foiCriada == 1)
                    {
                        montaABB(p, arquivo);
                    }
                    else
                        printf("        Erro ao criar árvore!\n        ");


                    printf("\n        Pressione qualquer tecla para continuar...\n        ");
                    fflush(stdin);
                    getchar();

                    clear_screen();

                    break;
                case 2:
                    clear_screen();

                    buscaPalavra(p);

                    printf("\n\n        Pressione qualquer tecla para continuar...\n        ");
                    fflush(stdin);
                    getchar();

                    clear_screen();
                    break;
                case 0:
                    if(foiCriada == 1)
                        destroiABB(&p);
                        break;
                default:
                    printf("        Operacao invalida!\n\n");

                    printf("        Pressione qualquer tecla para continuar...\n        ");
                    fflush(stdin);
                    getchar();

                    clear_screen();
                    break;
            }
        }while(opc != 0);

    return 0;
}

int montaABB(pABB p, char *doc) //FUNCAO PARA INSERIR AS PALAVRAS DO DOCUMENTO NA ARVORE
{
    FILE *pFile = fopen(doc, "r");
    char palavra[100];
    int chave;
    int x;
    int linha = 1, coluna = 1, colunaCont = 0, pulaLinha;
    info aux;

    if (pFile == NULL)
        printf("        ERRO AO LER ARQUIVO!\n");
    else
    {
        x = 0;

        while((palavra[x] = fgetc(pFile)) != EOF){

            colunaCont++; //INCREMENTA  A CADA CHAR LIDO

            if((palavra[x] == ' ') || palavra[x] == '\n')
            {
                if(palavra[x] == ' ')
                    coluna = (colunaCont - 1) - (x - 1);  //EFETUA O CALCULO DA COLUNA

                else if(palavra[x] == '\n')
                {
                    pulaLinha = 1;
                    coluna = (colunaCont - 1) - (x - 1);
                }

                palavra[x] = '\0';

                x = 0;
                chave = 0;

                while(palavra[x] != '\0')
                {
                    chave += ((int)(palavra[x]))*(x+1); //DETERMINA A CHAVE DE BUSCA DA PALAVRA
                    x++;
                }

                aux.campoChave = chave;
                aux.linha = linha;
                aux.coluna = coluna;

                if((insereABB(p, &aux, comparaCamposChaves1) == SUCESSO))
                {
                    printf("\n        Palavra '%s' inserida com sucesso!\n", palavra);
                    printf("        - Chave: %d\n", chave);
                    //printf("        **Linha: %d, Coluna: %d\n\n", linha, coluna);
                    chave = 0;
                    x = 0;

                    if(pulaLinha == 1)
                    {
                        linha++;
                        colunaCont = 0;
                        pulaLinha = 0;
                    }
                }

            }
            else
                x++;
        }
    }
    return 0;
}


int buscaPalavra(pABB p)
{
    char palavra[100];
    int chave = 0;
    int x = 0;
    info aux, retorno;

    printf("\n\n        Informe a palavra a ser buscada: ");
    scanf("%s", palavra);
    printf("\n\n");

    while(palavra[x] != '\0')
    {
        chave += ((int)(palavra[x]))*(x+1);
        x++;
    }

    aux.campoChave = chave;

    if(buscaABB(p, &retorno, &aux.campoChave, comparaCamposChaves1) == SUCESSO)
    {
        printf("        Palavra '%s'\n", palavra);
        printf("        Linha: %d\n", retorno.linha);
        printf("        Coluna: %d\n", retorno.coluna);

        return SUCESSO;
    }
    else
    {
        printf("        Erro ao encontrar palavra!\n\n");
        return FRACASSO;
    }
}


///////////////////////////////////////////////////////////////////////////////////////
/*dados os endereços de duas instancias de registros, há a comparação dos
respectivos campos chaves e o retorno da relação entre eles: >, < ou = */
unsigned short comparaCamposChaves1(void *pInfo1, void *pInfo2)
{	tipoChave a1 = ((info *)pInfo1)->campoChave, a2 = ((info *)pInfo2)->campoChave;
 	if (a1 > a2)
		return '>';
	else
    		if (a1 < a2)
         		return '<';
      		else
         		return '=';
}


//////////////////////////////////////////////////////////////////////////////////////////
/*dados o endereço do campo chave "chave" de um registro e o endereço de uma instancia
de um registro, há a comparação da "chave" com o campo chave do registro e o
retorno da relação entre eles: >, < ou = */
unsigned short  comparaCamposChaves2(void *chave, void *pInfo)
{  tipoChave ch1 = *((tipoChave *)chave), ch2 = ((info *)pInfo)->campoChave;
   if (ch1 > ch2)
	return '>';
   else
    	if (ch1 < ch2)
         	return '<';
       	else
         	return '=';
}

///////////////////////////////////////////////////////////
void exibeChave(void *pInfo)
{ //static int i=0;
  printf( mascaraChave,((info *)pInfo)->campoChave);

}

//////////////////////////////////////////////////////////
void flush(FILE *in)
{ int c;
  do{ c=fgetc(in);
	}while(c!='\n' && c != EOF);
}


/////////////////////////////////////////////////////////
void menu(pABB p)
{    	unsigned int opc=1;
	info aux,retorno;
        while(1)
        {
	 system("clear");
	 printf("\n");
	 puts("0:sair         1:inserir          2:remover             3:buscar  ");
         puts("4:reiniciar    5:perc. em ordem   6:perc. em pos-ordem  7:perc. em pre-ordem");
	 puts("8:ABB vazia? ");
	 printf("\n:>");
         scanf("%u",&opc);


         switch (opc)
          { case 0:
          	destroiABB(&p);
		return;
	    case 1:
          	printf("entre com matricula: ");
		flush(stdin);
          	scanf("%i", &(aux.campoChave));
                if (insereABB(p,&aux,comparaCamposChaves1)==SUCESSO)
          		puts(">>> Sucesso na inserção");
          	else
            		puts(">>> Fracasso na inserção");
          	break;
            case 2:
            	printf("entre com matricula: ");

          	scanf("%i", &aux.campoChave);
          	if (removeABB(p,&aux.campoChave,comparaCamposChaves2,&retorno)==SUCESSO)
          		printf(">>> Removeu: %i",retorno.campoChave);
          	else
            		puts(">>> Fracasso na remocao");
            	break;
            case 3:
		printf("entre com matricula: ");

          	scanf("%i", &aux.campoChave);
          	if (buscaABB(p,&retorno,&aux.campoChave,comparaCamposChaves2)==SUCESSO)
			printf(">>> Buscou: %i",retorno.campoChave);
		else
			puts(">>> Fracasso na busca");
		break;
            case 4:
		reiniciaABB(p);
		puts(">>> ABB purgada!");
	 	break;
            case 5:
                if (emOrdem(p,exibeChave)==FRACASSO)
         	        puts(">>> ABB vazia");
		break;
            case 6:
                if (posOrdem(p,exibeChave)==FRACASSO)
                       puts(">>> ABB vazia");
	        break;
            case 7:
                if (preOrdem(p,exibeChave)==FRACASSO)
                      puts(">>> ABB vazia");
            	break;
            case 8:
                if (testaVaziaABB(p)==SIM)
                       	puts(">>> ABB vazia");
                else
                	puts(">>> ABB nao vazia");
            	break;

          }
	 printf("\n tecle para continuar...");
         flush(stdin);
         getchar();
       }
	return;
}

void clear_screen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system ("clear");
    #endif
}
