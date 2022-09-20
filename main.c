#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct CanMam
{
    int  idade;
    char Etnia[6];
    char EstCivil[9];
    char EstT[3];
    char EstN[3];
    char SextoEst[5];
    char TipDifer[27];
    char Nota[12];
    char EstA[9];
    int  tumor;
    char StaEst[9];
    char StAPro[9];
    int  NodExaminado;
    int  NodPositivo;
    int  MesVida;
    char Status[6];
    int linha;
}CanMam;

typedef struct Dados{
    int idade;
    int tumor;
    int linha;
}Dados;

typedef struct CanMam2{
    Dados DadStr;
    struct CanMan2 *Esquerda,*Direita;
}CanMam2;

int ValArq(FILE *fp){
  if (fp == NULL){
    printf("Nao foi possivel abrir o arquivo.");
    return 0;
  }
  return 1;
}

int ContaArv(CanMam2 *ArvBin){
  if(ArvBin == NULL)
    return 0;
  else
    return 1 + ContaArv(ArvBin->Esquerda) + ContaArv(ArvBin->Direita);
}

CanMam2* CriaArvVaz(){
  return NULL;
}

void CriArqCsv(CanMam *StruDad,Dados DadTum,int QtdDad){
  int c=0,f=0;
  FILE *arquivosaida;  
  arquivosaida = fopen("ArquivoSaida.csv","a+");
  if (arquivosaida == NULL){
      printf("Erro na criação do arquivo de saida!");
        exit(1);
    }
    else{
      for (c = 0; c < QtdDad; c++){
        if (DadTum.idade == StruDad[c].idade && DadTum.tumor == StruDad[c].tumor){
          fprintf(arquivosaida,"%d,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%s,%d,%d,%d,%s\n",
                  StruDad[c].idade,StruDad[c].Etnia,StruDad[c].EstCivil,StruDad[c].EstT,StruDad[c].EstN,StruDad[c].SextoEst,StruDad[c].TipDifer,StruDad[c].Nota,StruDad[c].EstA,StruDad[c].tumor,StruDad[c].StaEst,StruDad[c].StAPro,StruDad[c].NodExaminado,StruDad[c].NodPositivo,StruDad[c].MesVida,StruDad[c].Status);
          printf("%d,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%s,%d,%d,%d,%s\n",
                 StruDad[c].idade,StruDad[c].Etnia,StruDad[c].EstCivil,StruDad[c].EstT,StruDad[c].EstN,StruDad[c].SextoEst,StruDad[c].TipDifer,StruDad[c].Nota,StruDad[c].EstA,StruDad[c].tumor,StruDad[c].StaEst,StruDad[c].StAPro,StruDad[c].NodExaminado,StruDad[c].NodPositivo,StruDad[c].MesVida,StruDad[c].Status); 
        }
      }
      fclose(arquivosaida);
    }
}

void PrintaArv(CanMam *StruDad,CanMam2 *ArvBin,int QtdDad){ 
  if(ArvBin){
    PrintaArv(StruDad,ArvBin->Esquerda,QtdDad);
    CriArqCsv(StruDad,ArvBin->DadStr,QtdDad);
    PrintaArv(StruDad,ArvBin->Direita,QtdDad);
  }
}

CanMam2* InsArv(CanMam2 *ArvBin,int idadearq,int tamtumarq,int linha)
{
  if (ArvBin == NULL){
    CanMam2 *NovArv=(CanMam2*)malloc(sizeof(CanMam2));
	  NovArv->DadStr.idade=idadearq;
    NovArv->DadStr.tumor=tamtumarq;
    NovArv->DadStr.linha=linha;
    NovArv->Esquerda=NULL;
	  NovArv->Direita=NULL;
    return NovArv;
	}
	else{
		if (idadearq<ArvBin->DadStr.idade){
      ArvBin->Esquerda = InsArv(ArvBin->Esquerda,idadearq,tamtumarq,linha);
		}
		if (idadearq>ArvBin->DadStr.idade){
      ArvBin->Direita = InsArv(ArvBin->Direita,idadearq,tamtumarq,linha);
		}
    if (idadearq==ArvBin->DadStr.idade){
      if (tamtumarq<ArvBin->DadStr.tumor)
      {
        ArvBin->Esquerda = InsArv(ArvBin->Esquerda,idadearq,tamtumarq,linha);  
      }
      if (tamtumarq>ArvBin->DadStr.tumor){
        ArvBin->Direita = InsArv(ArvBin->Direita,idadearq,tamtumarq,linha);
      }
    }
    return ArvBin;
	}
}

//Acessa o conteudo do arquivo .csv (DataBase) e trabalha com as árvores binárias.
CanMam2* AloVet(FILE *vArqEnt,CanMam *vetor,char NomArq[20],Dados *vetor2,CanMam2 *ArvBin){
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
                  &vetor[s].idade,vetor[s].Etnia,vetor[s].EstCivil,vetor[s].EstT,vetor[s].EstN,vetor[s].SextoEst,vetor[s].TipDifer,vetor[s].Nota,vetor[s].EstA,&vetor[s].tumor,vetor[s].StaEst,vetor[s].StAPro,&vetor[s].NodExaminado,&vetor[s].NodPositivo,&vetor[s].MesVida,vetor[s].Status)){                  
        printf("Erro ao Scanear o arquivo na linha %d.\n",s+1); 
        break;
      }
      else{
        vetor[s].linha=s+1;  
      }
      //Preencher o vetor secundário que será usado na montagem da árvore.
      vetor2[s].idade = vetor[s].idade;
      vetor2[s].tumor = vetor[s].tumor;
      vetor2[s].linha = s+1;
      //Inserir na árvore ordenando por idade e tamanho do tumor.
      ArvBin = InsArv(ArvBin,vetor2[s].idade,vetor2[s].tumor,vetor2[s].linha);
      s++;
    }
    fclose(vArqEnt);
    return(ArvBin);
  }
  else{
    return NULL;
  }     
}

int main(){
  //variaveis globais
  clock_t t = clock();
  FILE *fp; 
  CanMam2 *ArvBin = CriaArvVaz ();
  CanMam *StrDad;
  Dados *StrSec;
  int menu = 0,QtdLinhas = 0,c = 0;
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
        if (nome_arquivo!=NULL){
          fp=fopen(nome_arquivo,"r");
          if (ValArq(fp)){
            //Verifica a quantidade de linhas para alocação de memória.
            for (c = getc(fp); c != EOF; c = getc(fp))
              if (c == '\n')
              QtdLinhas++;
            fclose(fp);
            StrSec=(Dados*)malloc(QtdLinhas*sizeof(Dados));
            StrDad=(CanMam*)malloc(QtdLinhas*sizeof(CanMam));
            if (StrDad==NULL||StrSec==NULL){
              printf("Alocacao das structs da DataBase não foi possível.");
            }
            else{
              ArvBin = AloVet(fp,StrDad,nome_arquivo,StrSec,ArvBin);
              t = clock() - t;
              printf("Arquivo carregado com sucesso, tempo de execucao total: %lf\n",((double)t)/((CLOCKS_PER_SEC/1000)));
            }
          }
        }
      break;

      case 2:
        if(ArvBin==NULL){
          printf("Carregue um Arquivo primeiro para gerar o relatorio");
        }
        else{
            printf("Age,Race,Marital Status,T Stage ,N Stage,6th Stage,differentiate,Grade,A Stage,Tumor Size,Estrogen Status,Progesterone Status,Regional Node Examined,Reginol Node Positive,Survival Months,Status\n");
            PrintaArv(StrDad,ArvBin,QtdLinhas);
        }
      break;

      case 3:
	      printf("O programa esta sendo encerrado!");	    
        menu = 3;
        free(StrDad);
        free(StrSec);
        free(ArvBin);
      break;

      default:
      printf ("Insira uma opcao valida!!\n\n");
    }
  }while(menu != 3);
  return 1;
}
