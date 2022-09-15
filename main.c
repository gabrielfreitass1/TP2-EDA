#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
  int  numero;
  struct No *esquerda;
  struct No *direita;
}No;
//Percorre o arquivo e armazena dados na memoria
void PreVetArq(FILE *vArqEnt,airline *vetor){
  int s=0,c=0;
  vArqEnt = fopen("Airlines.csv", "r");
  if (ValArq(vArqEnt)){
    //Percorre o Arquivo
    while (!feof(vArqEnt)){
      //Pular o Cabeçalho
      if (s==0){
        for (c = getc(vArqEnt); c != EOF; c = getc(vArqEnt))
          if (c == '\n')
            break;
      }
      //Preencher o vetor com os dados da DataBase.
      if (!fscanf(vArqEnt,"%d,%[^,],%d",&vetor[s].id,vetor[s].airlineCode, &vetor[s].delay)){
        printf("Erro ao Scanear o arquivo.");
        break;
      }
      s++;
    }
    fclose(vArqEnt);
  }
}

//Verificar se o arquivo existe
int ValArq(FILE *fp){
  if (fp == NULL){
      printf("Nao foi possivel abrir o arquivo.");
      return 0;
    }
  return 1;
}
void PreVetArq(FILE *vArqEnt,airline *vetor){
  int s=0,c=0;
  vArqEnt = fopen("Airlines.csv", "r");
  if (ValArq(vArqEnt)){
    //Percorre o Arquivo
    while (!feof(vArqEnt)){
      //Pular o Cabeçalho
      if (s==0){
        for (c = getc(vArqEnt); c != EOF; c = getc(vArqEnt))
          if (c == '\n')
            break;
      }
      //Preencher o vetor com os dados da DataBase.
      if (!fscanf(vArqEnt,"%d,%[^,],%d",&vetor[s].id,vetor[s].airlineCode, &vetor[s].delay)){
        printf("Erro ao Scanear o arquivo.");
        break;
      }
      s++;
    }
    fclose(vArqEnt);
  }
}

void CriArqCsv(sub_airline *VetAir,int QtdAir){
  int e=0,f=0;
  FILE *arquivosaida;
  arquivosaida = fopen("AirlinesSaida.csv","w+");
  if (arquivosaida == NULL){
      printf("Erro na criação do arquivo de saida!");
        exit(1);
    }
    else{
      fprintf(arquivosaida,"Airline,Media\n");
      for(e=0; e<QtdAir; e++){
        fprintf(arquivosaida, "%s,%f\n", VetAir[e].airlineCode, VetAir[e].media);
      }
      fclose(arquivosaida);
    }
}

int main()
{
    int menu = 0;
    char nome_arquivo[20];
    FILE *fp;

    do{
    printf("Escolha uma opçao do menu\n");
    printf("1 - Carregar arquivo de Dados\n");
    printf("2 - Emitir Relatorio\n");
    printf("3 - Sair\n");
    scanf("%d",&menu);
    system("cls");

    switch (menu){

    case 1:
    printf("Digite o nome do arquivo a ser lido\n");
    printf("EX:Breast_cancer.csv\n");
    gets(nome_arquivo);
    ValArq(fp);

    break;

    case 2:
    break;

    case 3:
    menu = 3;
    break;

    default :
    printf ("Insira uma opçao valida!!\n");
    }
    }while(menu != 3);

    return 0;
}
