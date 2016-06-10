#include "PDSE.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/******************************//******************************/
/***************************APLICAÇÃO**************************/
/******************************//******************************/

void verifica(pPDSE p, char *doc)
{
    int certo = 1; //VARIAVEL VERIFICADORA
    char aux[60];
    char tag[60];
    FILE *pFile = fopen(doc, "r");

    if (pFile == NULL)
        printf("        ERRO AO LER ARQUIVO!\n");
    else
    {
        cria(&p, 60*sizeof(char));

        printf("\n\n        Relatorio:\n\n        \n");

        while(fscanf(pFile, "%s", tag) != EOF)
        {
            if((tag[0] == '<') && (tag[1] == '/'))  //SE FOR FECHAMENTO DE TAG
            {
                printf("        Tag lida: %s\n\n", tag);

                remover(p, aux); //AUX RECEBE A TAG REMOVIDA

                memmove(&tag[1], &tag[2], (strlen(tag) - 2) * sizeof(char)); //TIRAR O / DA TAG
                tag[strlen(tag) - 1] = '\0';  //INDICA O FIM DA STRING PRA NAO REPETIR O >

                if(strcmp(tag, aux) != 0) //SE A TAG REMOVIDA FOR A TAG ERRADA, ENCERRA O PROGRAMA COM ERRO
                {
                    certo = 0;
                    break;
                }

                printf("        - Tag removida: %s\n\n", tag);

            }
            else if((tag[0] == '<') && (tag[1] != '/') && (tag[1] != '!'))  //SE FOR ABERTURA DE TAG E NAO COMENTARIO
            {
                if(strcmp(tag, "<br>") && strcmp(tag, "<frame>") && strcmp(tag, "<img>") && strcmp(tag, "<input>")) //SE NAO FOR TAG QUE NAO PRECISA DE FECHAMENTO
                {
                    printf("        Tag lida: %s\n\n", tag);

                    insere(p, tag);
                    printf("        + Tag inserida: %s\n\n", tag);
                }
            }
        }

        if(testaSeVazia(p) && (certo == 1))
        {
            printf("\n        NENHUM ERRO DE ANINHAMENTO ENCONTRADO!\n\n");
            printf("        ______________________________________\n\n");
        }
        else
        {
            printf("\n        ERRO DE ANINHAMENTO ENCONTRADO COM A TAG %s\n\n", tag);
            printf("        ______________________________________________________\n\n");
        }
    }

    fclose(pFile);
    destroi(&p);
}

int main(int argc, char *argv[ ])
{
    PDSE pilha;
    int option;
    char arquivo[100];

    if(argc != 1) //SE FOI PASSADO O DOCUMENTO POR LINHA DE COMANDO
    {
        strcpy(arquivo, argv[1]); //PASSA O DOCUMENTO DE ARGV PARA 'ARQUIVO'
    }
    else
    {
        strcpy(arquivo, "documentoHTML.txt"); //SE NAO, ABRE O DOCUMENTO PADRAO
    }

    do
    {
        printf("\n\n     VERIFICADOR DE ANINHAMENTO HTML\n\n");
        printf("           Informe a operacao:\n\n");
        printf("        1 - Verificar documento\n");
        printf("        0 - Sair\n\n");

        printf("        ");
        scanf("%d", &option);
        printf("\n");

        switch(option)
        {
            case 1:
                clear_screen();

                verifica(&pilha, arquivo);

                printf("        Pressione qualquer tecla para continuar...\n        ");
                fflush(stdin);
                getchar();

                clear_screen();

                break;
            case 0:
                break;
            default:
                printf("        Operacao invalida!\n\n");

                printf("        Pressione qualquer tecla para continuar...\n        ");
                fflush(stdin);
                getchar();

                clear_screen();
                break;
        }
    }while(option != 0);

    return 0;
}

void clear_screen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system ("clear");
    #endif
}
