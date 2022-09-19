#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct CanMam
{
    int  Idade;
    char Etnia[6];
    char EstCivil[9];
    char EstT[3];
    char EstN[3];
    char SextoEst[5];
    char TipDifer[27];
    int  Nota;
    char EstA[9];
    int  TamTumor;
    char StaEst[9];
    char StAPro[9];
    int  NodExaminado;
    int  NodPositivo;
    int  MesVida;
    char Status[6];
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

int ContaArv(CanMam *ArvBin){
   if(ArvBin == NULL)
        return 0;
   else
        return 1 + ContaArv(ArvBin->Esquerda) + ContaArv(ArvBin->Direita);
}

CanMam* CriaArvVaz(){
  return NULL;
}
CanMam* InsArv(CanMam *ArvBin,int IdadeArq,char EtniaArq[6],char EstCivilArq[9],char EstTArq[3],char EstNArq[3],char SexEstArq[5],char TipDifArq[27],char NotaArq[12],char EstAArq[9],
               int TamTumArq,char StaEstArq[9],char StaProArq[9],int NodExaArq,int NodPosArq,int MesVidArq,char StaArq[6])
{
  if (ArvBin == NULL){
    ArvBin=(CanMam*)malloc(sizeof(CanMam));
	  ArvBin->Idade=IdadeArq;
    strcpy(ArvBin->Etnia,EtniaArq);
    strcpy(ArvBin->EstCivil,EstCivilArq);
    strcpy(ArvBin->EstT,EstTArq);
    strcpy(ArvBin->EstN,EstNArq);
    strcpy(ArvBin->SextoEst,SexEstArq);
    strcpy(ArvBin->TipDifer,TipDifArq);
    strcpy(ArvBin->Nota,NotaArq);
    strcpy(ArvBin->EstA,EstAArq);
    ArvBin->TamTumor=TamTumArq;
    strcpy(ArvBin->StaEst,StaEstArq);
    strcpy(ArvBin->StAPro,StaProArq);
    ArvBin->NodExaminado=NodExaArq;
    ArvBin->NodPositivo=NodPosArq;
    ArvBin->MesVida=MesVidArq;
    strcpy(ArvBin->Status,StaArq);
    ArvBin->Esquerda=NULL;
	  ArvBin->Direita=NULL;
	}
	else{
		if (IdadeArq<ArvBin->Idade){
      printf("Teste-3");
      ArvBin = InsArv(ArvBin->Esquerda,IdadeArq,EtniaArq,EstCivilArq,EstTArq,EstNArq,SexEstArq,TipDifArq,NotaArq,EstAArq,
                      TamTumArq,StaEstArq,StaProArq,NodExaArq,NodPosArq,MesVidArq,StaArq);
		}
		if (IdadeArq>ArvBin->Idade){
      printf("Teste-4");
      ArvBin = InsArv(ArvBin->Direita,IdadeArq,EtniaArq,EstCivilArq,EstTArq,EstNArq,SexEstArq,TipDifArq,NotaArq,EstAArq,
                      TamTumArq,StaEstArq,StaProArq,NodExaArq,NodPosArq,MesVidArq,StaArq);
		}
    /*
    if (IdadeArq==ArvBin->Idade){
      
    }
    */
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
      if (!fscanf(vArqEnt,"%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%d,%d,%[^\n]",
                  &IdadeArq,EtniaArq,EstCivilArq,EstTArq,EstNArq,SexEstArq,TipDifArq,NotaArq,EstAArq,&TamTumArq,StaEstArq,StaProArq,&NodExaArq,&NodPosArq,&MesVidArq,StaArq)){
        printf("Erro ao Scanear o arquivo na linha %d.\n",s+1); 
        break;
      }
      //Printf para acompanhar
      //printf("%d,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%s,%d,%d,%d,%s\n",IdadeArq,EtniaArq,EstCivilArq,EstTArq,EstNArq,SexEstArq,TipDifArq,NotaArq,EstAArq,TamTumArq,StaEstArq,StaProArq,&NodExaArq,&NodPosArq,&MesVidArq,StaArq);
      
      //Inserir na árvore ordenando por idade e tamanho do tumor.
      vetor = InsArv(vetor,IdadeArq,EtniaArq,EstCivilArq,EstTArq,EstNArq,SexEstArq,TipDifArq,NotaArq,EstAArq,
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
    printf("Escolha uma opcao do menu\n");
    printf("1 - Carregar arquivo de Dados\n");
    printf("2 - Emitir Relatorio\n");
    printf("3 - Sair\n");
    scanf("%d",&menu);
    system("cls");
    fflush(stdin);
	  
    switch (menu){
      case 1:
        printf("Digite o nome do arquivo a ser lido (Ex: Breast_Cancer.csv).\n");
        scanf("%s",nome_arquivo);
	fflush(stdin);
		    
        //Preenche e trabalha com as árvores binárias.
        if (nome_arquivo!=NULL)
        {
          ArvBin=(CanMam*)malloc(sizeof(CanMam));
          if (ArvBin==NULL){
            printf("Alocacao da raiz da arvore binária mal sucedida!");
          }
          else{
            AloVet(fp,ArvBin,nome_arquivo);
            //Inclusão direta para teste.
            //ArvBin = InsArv(ArvBin,43,"White","Divorced","T1","N1","IIA","Poorly differentiated","3","Regional",16,"Positive","Positive",2,1,87,"Alive");
            printf("Nos: %d",ContaArv(ArvBin));
            t = clock() - t;
            printf("\nTempo de Execucao Total: %lf",((double)t)/((CLOCKS_PER_SEC/1000)));
            free(ArvBin);
          }
        }
      break;

      case 2:
      break;

      case 3:
	printf("O programa esta sendo encerrado!");	    
        menu = 3;
      break;

      default:
      printf ("Insira uma opcao valida!!\n\n");
    }
  }while(menu != 3);
  return 1;
}
