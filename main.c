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

void abrirConta(Conta *cont){

    //Variaveis
    char opc;
    char OPCmodalidade;
    int saldoInicial;
    char OPCsaldo;
    system("cls");
    printf("||| ABERTURA DE CONTA |||\n\n");

    printf("----TITULAR----\n");
    for(int i=0;i<MAXTITULARES;i++){
       printf("\nNome:");
       scanf("%s" , &cont->titular->nomeCliente);
       printf("\nPretende adicionar outro titular? S/N");
       scanf(" %c", &opc);
       if (opc=='n' || opc=='N'){
        break;
       }
       else{
        continue;
       }
    }
    printf("\nIntroduza a sua data de nascimento no formato dd/mm/aa :\n");
    scanf("%d/%d/%d",&cont->titular->dataNascimeto.dia,&cont->titular->dataNascimeto.mes,&cont->titular->dataNascimeto.ano);

    printf("\nIntroduza o NIF :");
    scanf("%d",&cont->titular->nifTitular);

    printf("----CONTA:----\n");
    printf("\n Nº da conta :");
    scanf("%d",&cont->numeroConta);

    do{
         printf("\n Modalidade \( N - Normal ou I - isento\)");
        scanf(" %c",&OPCmodalidade);
        if(OPCmodalidade=='n'|| OPCmodalidade=='N'){
            *cont->modalidade="normal";
        }
        else if (OPCmodalidade=='i'|| OPCmodalidade=='I'){
             *cont->modalidade="isento";
        }
    }while(OPCmodalidade != 'n' && OPCmodalidade !='N' && OPCmodalidade != 'i' && OPCmodalidade !='I');


    do{
        printf("\n\nSaldo:");
        scanf("%d",&saldoInicial);
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

printf("---TODAS AS CONTAS---");
for(int i=0 ; i<NcontasAtualmente; i++){
    printf("\nNº CONTA: %d",cont[i].numeroConta);
    for(int j=0; j<MAXTITULARES;j++){
        printf("\nTitular/es: %s",cont[i].titular[j]);
    }


}



}





int main()
{

 setlocale(LC_CTYPE, "");

//VARIAVEIS
int op;
int opcao = 0;
int OPClistagem=0;
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
            printf("----LISTAGEM----\n\n");
            printf(" 1 - Listar todas as Contas");
            printf(" 2 - Listar pelo NIF");
            scanf("%d",&OPClistagem);

            switch(OPClistagem){
             case 1:
                 ListarTodasasContas(contas, numeroContas);
                 break;


             default:printf("Opção Inválida!\n");
            }
        break;



         default:printf("Opção Inválida!\n");
     }
     system("pause");
 }while (opcao != 8);
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

     printf("8. Sair.\n");
     printf("\n\nIntroduza a sua opção: ");
     scanf("%d", &op);
     printf("\n\n");
     return op;
}
