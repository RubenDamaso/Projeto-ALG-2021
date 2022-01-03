/*
    * @Nome: Banco Alves dos Reis

    * @Descrição:
        O objetivo deste projeto é desenvolver uma pequena aplicação em consola, utilizando a linguagem
        C ANSI e a abordagem procedimental e modular, por forma a implementar um sistema de gestão bancário.

    * @Autores:
        Tiago Guerreiro
        Ruben Dâmaso

    *@VERSÃO 0.1

    *DATA : 03/01/2021


*/

//BIBLOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
//FICHEIROS HEADER
/* Onde estão guardadas as estruturas fundamentais do Programa*/
#include "CONTA.h"
#include "CLIENTE.h"
#include "DATA.h"
//CONSTANTES
/* Onde estão guardadas variaveis que são utlizadas muito frequentemente*/
#define MAXCONTAS 100
#define MAXTITULARES 5
#define MAXHISTORICO 3

void abrirConta(Conta *cont){

    //Variaveis
    char opc;
    char OPCmodalidade;
    float saldoInicial;
    char OPCsaldo;
    char naoIsento[100]="normal";
    char isento[100]="isento";

    system("cls");
    printf("||| ABERTURA DE CONTA |||\n\n");

    printf("----TITULAR----\n");
    for(int i=0;i<MAXTITULARES;i++){

       printf("\nNome:");
       scanf("%s" , &cont->titular[i].nomeCliente);

        printf("\nIntroduza a sua data de nascimento no formato dd/mm/aa :\n");
        scanf("%d/%d/%d",&cont->titular[i].dataNascimeto.dia,&cont->titular[i].dataNascimeto.mes,&cont->titular[i].dataNascimeto.ano);

        printf("\nIntroduza o NIF :");
        scanf("%d",&cont->titular[i].nifTitular);

       printf("\nPretende adicionar outro titular? S/N");
       scanf(" %c", &opc);
       if (opc=='n' || opc=='N'){

        break;
       }
       else{
        continue;
       }
    }

    printf("----CONTA:----\n");
    printf("\n Nº da conta :");
    scanf("%d",&cont->numeroConta);

    do{
         printf("\n Modalidade \( N - Normal ou I - isento\)");
        scanf(" %c",&OPCmodalidade);
        fflush(stdin);
        if(OPCmodalidade=='n'|| OPCmodalidade=='N'){
            strcpy(cont->modalidade, naoIsento);
        }
        else if (OPCmodalidade=='i'|| OPCmodalidade=='I'){
              strcpy(cont->modalidade, isento);
        }
    }while(OPCmodalidade != 'n' && OPCmodalidade !='N' && OPCmodalidade != 'i' && OPCmodalidade !='I');


    do{
        printf("\n\nSaldo:");
        scanf("%f",&saldoInicial);
        if(saldoInicial<150){
           printf("\nMONTANTE ABAIXO DO NECESSARIO PARA ABERTURA DE CONTA \(Valor minimo 150 euros\)");
           OPCsaldo='n';
        }
        else{
            OPCsaldo='s';
            cont->saldoAtual=saldoInicial;
        }
    }while(OPCsaldo !='s');



    //HISTORICO DE VALORES DO SALDO
    /* Como a Conta é criada agora não existe movimento anterior ,então é passado o valor de 0 para o historico dos ulimos 3 valores */
    for(int i=0; i<3 ;i++){
    cont->historico[i]= 0;
    }

    printf("\nIntroduza a data de criação da conta  no formato dd/mm/aa  :");
    scanf("%d/%d/%d",&cont->dataAbertura.dia,&cont->dataAbertura.mes,&cont->dataAbertura.ano);
}



void ListarTodasasContas(Conta cont[MAXCONTAS], int NcontasAtualmente){
system("cls");
printf("---TODAS AS CONTAS---");

    for(int i=0 ; i<NcontasAtualmente; i++){
        printf("\n---------- Nº CONTA: %d ----------",cont[i].numeroConta);
            for(int j=0; j<MAXTITULARES;j++){
                printf("\nTitular/es: %s",cont[i].titular[j].nomeCliente);
                printf("\nData de Nascimento: %0.2d/%0.2d/%0.4d",cont[i].titular[j].dataNascimeto.dia,cont[i].titular[j].dataNascimeto.mes,cont[i].titular[j].dataNascimeto.ano);
                printf("\nNIF: %d",cont[i].titular[j].nifTitular);
            }
        printf("-----------\n");
        printf("\nModalidade da conta:%s\n",cont[i].modalidade);
        printf("SALDO ATUAL: %.2f\n",cont[i].saldoAtual);
        printf("\nHistorico:\n");
            for(int j=0 ; j<MAXHISTORICO ; j++){
                printf("%dº valor : %.2f\n\n",j+1 ,cont[i].historico[j]);
            }
        printf("Data de Abertura da conta : %0.2d/%0.2d/%0.4d\n\n",cont[i].dataAbertura.dia,cont[i].dataAbertura.mes,cont[i].dataAbertura.ano);
    }

}

void ListarTodasasContasNiF(Conta cont[MAXCONTAS], int NcontasAtualmente){
system("cls");

//variaveis
int nifPretendido=0;

printf("\nNIF Pretendido:");
scanf("%d",&nifPretendido);
printf("---TODAS AS CONTAS---");
    for(int i=0 ; i<NcontasAtualmente; i++){
        for(int j=0;j<MAXTITULARES;j++){
            if (cont[i].titular[j].nifTitular == nifPretendido){
                printf("\n---------- Nº CONTA: %d ----------",cont[i].numeroConta);
                for(int j=0; j<MAXTITULARES;j++){
                    printf("\nTitular/es: %s",cont[i].titular[j].nomeCliente);
                    printf("\nData de Nascimento: %0.2d/%0.2d/%0.4d",cont[i].titular[j].dataNascimeto.dia,cont[i].titular[j].dataNascimeto.mes,cont[i].titular[j].dataNascimeto.ano);
                    printf("\nNIF: %d",cont[i].titular[j].nifTitular);
                }
                printf("-----------\n");
                printf("\nModalidade da conta:%s\n",cont[i].modalidade);
                printf("SALDO ATUAL: %.2f\n",cont[i].saldoAtual);
                printf("\nHistorico:\n");
                for(int j=0 ; j<MAXHISTORICO ; j++){
                    printf("%dº valor : %.2f\n\n",j+1 ,cont[i].historico[j]);
                }
                printf("Data de Abertura da conta : %0.2d/%0.2d/%0.4d\n\n",cont[i].dataAbertura.dia,cont[i].dataAbertura.mes,cont[i].dataAbertura.ano);
            }
        }
    }
}



void ListarTodasasContasNumeroConta(Conta cont[MAXCONTAS], int NcontasAtualmente){
system("cls");

//variaveis
int nContaPretendido=0;

printf("\nNumero da conta:");
scanf("%d",&nContaPretendido);
printf("---CONTA %d---", nContaPretendido);
    for(int i=0 ; i<NcontasAtualmente; i++){
            if (cont[i].numeroConta == nContaPretendido){
                for(int j=0; j<MAXTITULARES;j++){
                    printf("\nTitular/es: %s",cont[i].titular[j].nomeCliente);
                    printf("\nData de Nascimento: %0.2d/%0.2d/%0.4d",cont[i].titular[j].dataNascimeto.dia,cont[i].titular[j].dataNascimeto.mes,cont[i].titular[j].dataNascimeto.ano);
                    printf("\nNIF: %d",cont[i].titular[j].nifTitular);
                }
                printf("-----------\n");
                printf("\nModalidade da conta:%s\n",cont[i].modalidade);
                printf("SALDO ATUAL: %.2f\n",cont[i].saldoAtual);
                printf("\nHistorico:\n");
                for(int j=0 ; j<MAXHISTORICO ; j++){
                    printf("%dº valor : %.2f\n\n",j+1 ,cont[i].historico[j]);
                }
                printf("Data de Abertura da conta : %0.2d/%0.2d/%0.4d\n\n",cont[i].dataAbertura.dia,cont[i].dataAbertura.mes,cont[i].dataAbertura.ano);
            }
    }
}

void Depositar(Conta cont[MAXCONTAS], int NcontasAtualmente){
system("cls");
//variaveis
int nContaPretendido=0;
float valorDeposito=0;
float ultimoMovimento;
float PnultimoMovimento;
float AntePnultimoMovimento;

printf("\nNumero da conta Pretendida:");
scanf("%d",&nContaPretendido);

    for(int i=0 ; i<NcontasAtualmente; i++){
        if (cont[i].numeroConta == nContaPretendido){
            printf("\nValor do Deposito:");
            scanf("%f",&valorDeposito);

                    //REALIZAÇÃO DO HISTORICO
                ultimoMovimento       = cont[i].historico[2];
                PnultimoMovimento     = cont[i].historico[1];
                AntePnultimoMovimento = cont[i].historico[0];
                cont[i].historico[2] = cont[i].saldoAtual;
                cont[i].historico[1] = ultimoMovimento;
                cont[i].historico[0] = PnultimoMovimento;


            cont[i].saldoAtual=  cont[i].saldoAtual + valorDeposito;
        }
        printf("\n---DEPOSITO EFETUADO COM SUCESSO , OBRIGADO !---\n");
        printf("\n\nSALDO ATUAL: %.2f\n",cont[i].saldoAtual);
    }
}

void Levantar(Conta cont[MAXCONTAS], int NcontasAtualmente){
system("cls");
//variaveis
int nContaPretendido=0;
float valorLevantar=0;
float ultimoMovimento;
float PnultimoMovimento;
float AntePnultimoMovimento;
printf("\nNumero da conta Pretendida:");
scanf("%d",&nContaPretendido);

    for(int i=0 ; i<NcontasAtualmente; i++){
        if (cont[i].numeroConta == nContaPretendido){
            printf("\nValor que deseja levantar:");
            scanf("%f",&valorLevantar);
                //REALIZAÇÃO DO HISTORICO
                ultimoMovimento       = cont[i].historico[2];
                PnultimoMovimento     = cont[i].historico[1];
                AntePnultimoMovimento = cont[i].historico[0];
                cont[i].historico[2] = cont[i].saldoAtual;
                cont[i].historico[1] = ultimoMovimento;
                cont[i].historico[0] = PnultimoMovimento;

            cont[i].saldoAtual=  cont[i].saldoAtual - (valorLevantar + 5);
        }
        printf("\n---LEVANTAMENTO EFETUADO COM SUCESSO , OBRIGADO !---\n");
        printf("\n\nSALDO ATUAL: %.2f\n",cont[i].saldoAtual);
    }
}


void Transferir(Conta cont[MAXCONTAS], int NcontasAtualmente){

system("cls");
//variaveis
int nContaPretendido=0;
float valorTransferir=0;
int nContaEnviar=0;
int nContaReceber=0;
int posicaoContaEnviar=0;
int posicaoContaReceber=0;
float ultimoMovimento;
float PnultimoMovimento;
float AntePnultimoMovimento;

printf("\nNumero da conta Origem:");
scanf("%d",&nContaEnviar);

printf("\nNumero da conta Destino:");
scanf("%d",&nContaReceber);


    for(int i=0 ; i<NcontasAtualmente; i++){
        if (cont[i].numeroConta == nContaEnviar){
          posicaoContaEnviar = i;
        }
    }
    for(int i=0 ; i<NcontasAtualmente; i++){
        if (cont[i].numeroConta == nContaReceber){
          posicaoContaReceber = i;
        }
    }
    printf("Introduza o valor a transferir da conta nº%d para a conta nº%d : ",cont[posicaoContaEnviar].numeroConta,cont[posicaoContaReceber].numeroConta);
    scanf("%f",&valorTransferir);
                //REALIZAÇÃO DO HISTORICO PARA A CONTA DE ORIGEM
                ultimoMovimento       = cont[posicaoContaEnviar].historico[2];
                PnultimoMovimento     = cont[posicaoContaEnviar].historico[1];
                AntePnultimoMovimento = cont[posicaoContaEnviar].historico[0];
                cont[posicaoContaEnviar].historico[2] = cont[posicaoContaEnviar].saldoAtual;
                cont[posicaoContaEnviar].historico[1] = ultimoMovimento;
                cont[posicaoContaEnviar].historico[0] = PnultimoMovimento;

                //REALIZAÇÃO DO HISTORICO PARA A CONTA DE DESTINO
                ultimoMovimento       = cont[posicaoContaReceber].historico[2];
                PnultimoMovimento     = cont[posicaoContaReceber].historico[1];
                AntePnultimoMovimento = cont[posicaoContaReceber].historico[0];
                cont[posicaoContaReceber].historico[2] = cont[posicaoContaReceber].saldoAtual;
                cont[posicaoContaReceber].historico[1] = ultimoMovimento;
                cont[posicaoContaReceber].historico[0] = PnultimoMovimento;

    cont[posicaoContaEnviar].saldoAtual-(valorTransferir+5);
    cont[posicaoContaReceber].saldoAtual+valorTransferir;

    printf("\n---TRANSFERENCIA EFETUADA COM SUCESSO , OBRIGADO !---\n");
}

EditarTipoDeConta(Conta cont[MAXCONTAS], int NcontasAtualmente){
system("cls");
//variaveis
int nContaPretendido=0;
float valorLevantar=0;
char OPCmodalidade;
char naoIsento[100]="normal";
char isento[100]="isento";

printf("\nNumero da conta Pretendida:");
scanf("%d",&nContaPretendido);

    for(int i=0 ; i<NcontasAtualmente; i++){
        if (cont[i].numeroConta == nContaPretendido){
            do{
                printf("\n Modalidade \( N - Normal ou I - isento\)");
                scanf(" %c",&OPCmodalidade);
                fflush(stdin);
                if(OPCmodalidade=='n'|| OPCmodalidade=='N'){
                    strcpy(cont[i].modalidade, naoIsento);
                }
                else if (OPCmodalidade=='i'|| OPCmodalidade=='I'){
                    strcpy(cont[i].modalidade, isento);
                }
            }while(OPCmodalidade != 'n' && OPCmodalidade !='N' && OPCmodalidade != 'i' && OPCmodalidade !='I');
        }
    }
}

 AdicionarTitular(Conta cont[MAXCONTAS], int NcontasAtualmente){

printf("||| Adicionar Titular |||\n\n");

 }

int main()
{
 setlocale(LC_CTYPE, "");
//VARIAVEIS
int op;
int opcao = 0;
int OPClistagem=0;
int OPCeditar=0;
//Vetor 'contas' que guarda todas as contas do banco
Conta contas[MAXCONTAS];
//Variavel 'numeroContas' que guarda o numero total de contas presentes no banco no momento
int numeroContas=0;



 do{
     //Apresentar o menu atraves da função 'apresentaMenu'
     opcao = apresentaMenu();
     switch(opcao){

        //Abrir uma conta no banco , utilizando a função 'abrirConta'
        case 1:
            abrirConta(&contas[numeroContas]);
            numeroContas++;//Incrementa +1 sempre que uma conta for criada
        break;
        case 2:
            system("cls");
            printf("----LISTAGEM----\n\n");
            printf(" 1 - Listar todas as Contas\n");
            printf(" 2 - Listar pelo NIF\n");
            scanf("%d",&OPClistagem);

            switch(OPClistagem){
                 case 1:
                 ListarTodasasContas(contas, numeroContas);
                 break;

                 case 2:
                    ListarTodasasContasNiF(contas, numeroContas);
                 break;


             default:printf("Opção Inválida!\n");
            }
        break;
        case 3:
            ListarTodasasContasNumeroConta(contas, numeroContas);
        break;
        case 4:
            Depositar(contas, numeroContas);
        break;
        case 5:
            Levantar(contas, numeroContas);
        break;
        case 6:
            Transferir(contas, numeroContas);
        break;

        case 7:
            system("cls");
            printf("----EDITAR CONTA----\n\n");
            printf(" 1 - Editar Tipo de Conta\n");
            printf(" 2 - Adicionar Titular\n");
            scanf("%d",&OPCeditar);
              switch(OPCeditar){
                 case 1:
                 EditarTipoDeConta(contas, numeroContas);
                 break;
                case 2:
                    AdicionarTitular(contas, numeroContas);
                 break;



             default:printf("Opção Inválida!\n");
            }

        break;
        case 8:

        break;

         default:printf("Opção Inválida!\n");
     }
     system("pause");
 }while (opcao != 10);
 return 0;

}

int apresentaMenu(){
     int op;
     system("cls");

    printf("|||| Banco Alves dos Reis ||||\n\n");

     printf("\n1. Abrir uma conta \n");

     printf("2. Listar contas existentes\n");

     printf("3. Consultar detalhes de uma conta\n");

     printf("4. Depositar dinheiro numa conta\n");

     printf("5. Levantar dinheiro de uma conta\n");

     printf("6. Transferir dinheiro entre contas\n");

     printf("7. Editar informação de  uma conta\n");

     printf("8. Eliminar uma conta\n");

     printf("9. Gravar listagem de contas para ficheiro texto\n");

     printf("10. Sair.\n");
     printf("\n\nIntroduza a sua opção: ");
     scanf("%d", &op);
     printf("\n\n");
     return op;
}
