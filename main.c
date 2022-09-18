#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct CanMam
{
    int  Idade;
    char Etnia;
    char EstCivil;
    char EstT;
    char EstN;
    char SextoEst;
    char TipDifer;
    char Nota;
    char EstA;
    int  TamTumor;
    char StaEst;
    char StAPro;
    int  NodExaminado;
    int  NodPositivo;
    int  MesVida;
    char Status;
    struct CanMam *Esquerda;
    struct CanMam *Direita;
}CanMam;

int ValArq(FILE *fp){
  if (fp == NULL){
    printf("Nao foi possivel abrir o arquivo.");
    return 0;
  }
  return 1;
}

CanMam* CriaArvVaz(){
  return NULL;
}

CanMam* InsArv(CanMam *ArvBin,int IdadeArq,char EtniaArq,char EstCivilArq,char EstTArq,char EstNArq,char SexEstArq,char TipDifArq,char NotaArq,char EstAArq,
               int TamTumArq,char StaEstArq,char StaProArq,int NodExaArq,int NodPosArq,int MesVidArq,char StaArq)
{
  if (ArvBin == NULL){
    ArvBin=(CanMam*)malloc(sizeof(CanMam));
	  ArvBin->Idade=IdadeArq;
    ArvBin->Etnia=EtniaArq;
    ArvBin->EstCivil=EstCivilArq;
    ArvBin->EstT=EstTArq;
    ArvBin->EstN=EstNArq;
    ArvBin->SextoEst=SexEstArq;
    ArvBin->TipDifer=TipDifArq;
    ArvBin->Nota=NotaArq;
    ArvBin->EstA=EstAArq;
    ArvBin->TamTumor=TamTumArq;
    ArvBin->StaEst=StaEstArq;
    ArvBin->StAPro=StaProArq;
    ArvBin->NodExaminado=NodExaArq;
    ArvBin->NodPositivo=NodPosArq;
    ArvBin->MesVida=MesVidArq;
    ArvBin->Status=StaArq;
    ArvBin->Esquerda=NULL;
	  ArvBin->Direita=NULL;
	}
	else{
		if (IdadeArq<(ArvBin->Idade)){
      InsArv(ArvBin->Esquerda,IdadeArq,EtniaArq,EstCivilArq,EstTArq,EstNArq,SexEstArq,TipDifArq,NotaArq,EstAArq,
             TamTumArq,StaEstArq,StaProArq,NodExaArq,NodPosArq,MesVidArq,StaArq);
		}
		else{
      InsArv(ArvBin->Direita,IdadeArq,EtniaArq,EstCivilArq,EstTArq,EstNArq,SexEstArq,TipDifArq,NotaArq,EstAArq,
             TamTumArq,StaEstArq,StaProArq,NodExaArq,NodPosArq,MesVidArq,StaArq);
		}
	}
  return ArvBin;
}

//Acessa o conteudo do arquivo .csv (DataBase) e trabalha com as árvores binárias.
int AloVet(FILE *vArqEnt,CanMam *vetor,char NomArq[20]){
  int s=0,c=0,IdadeArq=0,TamTumArq=0,NodExaArq=0,NodPosArq=0,MesVidArq=0;
  char EtniaArq[6],EstCivilArq[9],EstTArq[3],EstNArq[3],SexEstArq[5],TipDifArq[27],EstAArq[9],StaEstArq[9],StaProArq[9],StaArq[6],NotaArq[12];
  vArqEnt=fopen(NomArq,"r");
  if (ValArq(vArqEnt)){
    //Percorre o Arquivo
    while (!feof(vArqEnt)){
      //Pular o Cabeçalho
      if (s==0){
        for (c = getc(vArqEnt); c != EOF; c = getc(vArqEnt))
          if (c == '\n') 
            break;
      }  
      //Pega as informações da database.
      if (!fscanf(vArqEnt,"%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%d,%d,%[^\n]",&IdadeArq,EtniaArq,EstCivilArq,EstTArq,EstNArq,SexEstArq,TipDifArq,NotaArq,EstAArq,&TamTumArq,StaEstArq,StaProArq,&NodExaArq,&NodPosArq,&MesVidArq,StaArq)){
        printf("Erro ao Scanear o arquivo na linha %d.\n",s+1); 
        break;
      }
      //Printf para acompanhar
      //printf("%d,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%s,%d,%d,%d,%s\n",IdadeArq,EtniaArq,EstCivilArq,EstTArq,EstNArq,SexEstArq,TipDifArq,NotaArq,EstAArq,TamTumArq,StaEstArq,StaProArq,&NodExaArq,&NodPosArq,&MesVidArq,StaArq);
      
      //Inserir árvores ordenando por idade.
      InsArv(vetor,IdadeArq,EtniaArq,EstCivilArq,EstTArq,EstNArq,SexEstArq,TipDifArq,NotaArq,EstAArq,
             TamTumArq,StaEstArq,StaProArq,NodExaArq,NodPosArq,MesVidArq,StaArq);  
      s++;
    }
    fclose(vArqEnt);
  }
  else{
    return 0;
  }     
  return 1;  
}

int main(){
  //variaveis globais
  clock_t t = clock();
  FILE *fp; 
  CanMam *ArvBin = CriaArvVaz();
  int menu = 0;
  char nome_arquivo[20];

  do{
    printf("Escolha uma opçao do menu\n");
    printf("1 - Carregar arquivo de Dados\n");
    printf("2 - Emitir Relatorio\n");
    printf("3 - Sair\n");
    scanf("%d",&menu);
    system("cls");

    switch (menu){
      case 1:
        printf("Digite o nome do arquivo a ser lido\nEX:Breast_Cancer.csv\n");
        scanf("%s",nome_arquivo);
        //Preenche e trabalha com as árvores binárias.
        if (nome_arquivo!=NULL)
        {
          AloVet(fp,ArvBin,nome_arquivo);
          t = clock() - t;
          printf("\nTempo de Execução Total: %lf",((double)t)/((CLOCKS_PER_SEC/1000)));
          free(ArvBin);
        }
      break;

      case 2:
      break;

      case 3:
        menu = 3;
      break;

      default:
      printf ("Insira uma opçao valida!!\n");
    }
    }while(menu != 3);
  return 1;
}
