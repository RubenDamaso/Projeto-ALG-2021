/*
    * @Nome: Banco Alves dos Reis

    * @Descrição:
        O objetivo deste projeto é desenvolver uma pequena aplicação em consola, utilizando a linguagem
        C ANSI e a abordagem procedimental e modular, por forma a implementar um sistema de gestão bancário.

    * @Autores:
        Tiago Guerreiro
        Ruben Dâmaso

    *@VERSÃO 0.4

    *DATA : 07/01/2021


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






//FUNÇÃO AbrirConta
/*Esta Função permite-nos Criar uma conta e guardar a sua informação no array contas que se encontra no 'main'*/
void abrirConta(Conta *cont){

    //Variaveis
    char opc;
    char OPCmodalidade;
    float saldoInicial;
    int nifInicial;
    char OPCsaldo;
    char OPCnif;
    char naoIsento[100]="normal";
    char isento[100]="isento";

    system("cls");
    printf("||| ABERTURA DE CONTA |||\n\n");

    printf("----TITULAR----\n");
    /*

    Neste ciclo 'for' vamos recolher a informação relativa ao numero de titulares para
    cada conta, este têm um limite de 5 titulares por conta aberta (Dado fornecido pela
    constante MAXTITULARES definida com o valor '5')

    */
    for(int i=0;i<MAXTITULARES;i++){
        printf("\nNome:");
        scanf("%s" , &cont->titular[i].nomeCliente);

        printf("\nIntroduza a sua data de nascimento no formato dd/mm/aa :");
        scanf("%d/%d/%d",&cont->titular[i].dataNascimeto.dia,&cont->titular[i].dataNascimeto.mes,&cont->titular[i].dataNascimeto.ano);

        do{
            printf("\nIntroduza o NIF :");
            scanf("%d",&nifInicial);
            if(nifInicial==0){
                printf("\n!!!ERRO NIF NÃO PODE SER 0 TENTE NOVAMENTE!!!");
                OPCnif='n';
            }
            else{
                OPCnif='s';
                cont->titular[i].nifTitular=nifInicial;
            }
        }while(OPCnif !='s');

        printf("\nPretende adicionar outro titular? S - Sim / N - Não");
        printf("\nOpção:");
        scanf(" %c", &opc);
            //Se o utilizador não quiser introduzar mais titulares o ciclo interrompe e avança para a proxima recolha de informação relativa à conta propriamente dita.
            if (opc=='n' || opc=='N'){
                break;
            }
            //Caso o utilizador queira continuar o ciclo continua.
            else{
                continue;
            }
    }
    /*

    Neste ciclo 'for' vamos recolher a informação relativa à conta propriamente dita , tais como:

    -O numero da Conta
    -A modalidade (Normal ou Isento)
    -Saldo

    */
    printf("----CONTA:----\n");

    //Atribuição do numero da conta:
    printf("\n Nº da conta :");
    scanf("%d",&cont->numeroConta);

    //Atribuição da Modalidade da conta:
    do{
        printf("\n Modalidade \( N - Normal ou I - isento\)");
        printf("\nOpção:");
        scanf(" %c",&OPCmodalidade);
        fflush(stdin);
        /*
        Caso o utilizador selecionar a opção 'n' ou 'N' correspondendo à modalidade
        normal iremos utilizar  uma função da biblioteca das strings , 'strcpy' , para
        copiar o valor da modalidade 'normal' que é guardada atraves da variavel 'naoisento'.

        Caso o utilizador selecionar a opção 'i' ou 'I' correspondendo à modalidade
        isento iremos utilizar  uma função da biblioteca das strings , 'strcpy' , para
        copiar o valor da modalidade 'isento' que é guardada atraves da variavel 'isento'.

        */
        if(OPCmodalidade=='n'|| OPCmodalidade=='N'){
            strcpy(cont->modalidade, naoIsento);
        }

        else if (OPCmodalidade=='i'|| OPCmodalidade=='I'){
              strcpy(cont->modalidade, isento);
        }
    }while(OPCmodalidade != 'n' && OPCmodalidade !='N' && OPCmodalidade != 'i' && OPCmodalidade !='I');

    //Atribuição do saldo da Conta:
    do{
        printf("\n\nSaldo:");
        scanf("%f",&saldoInicial);
        /*
        Antes de Atribuirmos o saldo à conta teremos de verificar uma das condições impostas (Pois o montante necessário para abertura de conta é de 150 euros)
        O valor terá de ser superior a 150 euros.
        Caso o mesmo não se verifique o utilizador não sairá do ciclo até introduzir o valor correto.
        */
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
    //Atribuição da data de criação da conta
    printf("\nIntroduza a data de criação da conta  no formato dd/mm/aa  :");
    scanf("%d/%d/%d",&cont->dataAbertura.dia,&cont->dataAbertura.mes,&cont->dataAbertura.ano);
}

//FUNÇÃO ListarTodasasContas
/*Esta Função permite-nos mostrar todas as contas atualmente criadas */
void ListarTodasasContas(Conta cont[MAXCONTAS], int NcontasAtualmente){
system("cls");

printf("---TODAS AS CONTAS---\n\n\n");
    if (NcontasAtualmente==0){
        printf("\n!!! NÃO EXISTEM CONTAS ATUALMENTE !!!\n");
    }
    for(int i=0 ; i<NcontasAtualmente; i++){
        printf("\n---------- Nº CONTA: %d ----------",cont[i].numeroConta);
            for(int j=0; j<MAXTITULARES;j++){
                if (cont[i].titular[j].nifTitular == 0){
                    break;
                }
                printf("\nTitular/es: %s",cont[i].titular[j].nomeCliente);
                printf("\nData de Nascimento: %0.2d/%0.2d/%0.4d",cont[i].titular[j].dataNascimeto.dia,cont[i].titular[j].dataNascimeto.mes,cont[i].titular[j].dataNascimeto.ano);
                printf("\nNIF: %d\n",cont[i].titular[j].nifTitular);
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

//FUNÇÃO ListarTodasasContasNiF
/*Esta Função permite-nos mostrar todas as contas atualmente criadas com a perticularidade de somente mostrar aquelas associadas a determinado NIF*/
void ListarTodasasContasNiF(Conta cont[MAXCONTAS], int NcontasAtualmente){
system("cls");
//variaveis
int nifPretendido=0;
    /*Verificar se atualmente existem contas , se não existirem é apresentado uma mensagem ao utilizador*/
    if (NcontasAtualmente==0){
        printf("\n!!! NÃO EXISTEM CONTAS ATUALMENTE !!!\n");
    }
    /*Caso existam contas:*/
    else{
    /*Recolher o Nif pretendido*/
    printf("\nNIF Pretendido:");
    scanf("%d",&nifPretendido);
    printf("---TODAS AS CONTAS---");
        /*Neste ciclo percorremos todas as contas*/
        for(int i=0 ; i<NcontasAtualmente; i++){
            /*Neste ciclo percorremos todos os titulares presentes em cada conta*/
            for(int j=0;j<MAXTITULARES;j++){
                /*
                Verificamos para titular se o seu nif é o nif pretendido na procura e se for será apresentado todos os dados da conta
                */
                if (cont[i].titular[j].nifTitular == nifPretendido){
                    printf("\n---------- Nº CONTA: %d ----------",cont[i].numeroConta);
                    for(int j=0; j<MAXTITULARES;j++){
                         /*
                        Realizamos esta verificação para apresentar o numero correto de
                        titulares, ou seja , caso não exista nif o utilizador não existe
                        logo podemos para o ciclo pois já mostramos todos os titulares
                        */
                        if (cont[i].titular[j].nifTitular == 0){
                            break;
                        }
                        printf("\nTitular/es: %s",cont[i].titular[j].nomeCliente);
                        printf("\nData de Nascimento: %0.2d/%0.2d/%0.4d",cont[i].titular[j].dataNascimeto.dia,cont[i].titular[j].dataNascimeto.mes,cont[i].titular[j].dataNascimeto.ano);
                        printf("\nNIF: %d\n",cont[i].titular[j].nifTitular);
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
}

//FUNÇÃO ListarTodasasContasNumeroConta
/*Esta Função permite-nos mostrar todas as contas atualmente criadas com a perticularidade de somente mostrar aquelas associadas a determinado numero de conta*/
void ListarTodasasContasNumeroConta(Conta cont[MAXCONTAS], int NcontasAtualmente){
system("cls");
//variaveis
int nContaPretendido=0;

  /*Verificar se atualmente existem contas , se não existirem é apresentado uma mensagem ao utilizador*/
    if (NcontasAtualmente==0){
        printf("\n!!! NÃO EXISTEM CONTAS ATUALMENTE !!!\n");
    }
    else{
        /*Recolher o numero da conta pretendida*/
        printf("\nNumero da conta:");
        scanf("%d",&nContaPretendido);
        printf("---CONTA %d---", nContaPretendido);
            /*Neste ciclo percorremos todas as contas*/
            for(int i=0 ; i<NcontasAtualmente; i++){
                     /*
                    Verificamos se o numero da conta é o mesmo que a conta pretendida
                    */
                    if (cont[i].numeroConta == nContaPretendido){
                        /*Neste ciclo percorremos todos os titulares presentes na conta encontrada*/
                        for(int j=0; j<MAXTITULARES;j++){
                            /*
                            Realizamos esta verificação para apresentar o numero correto de
                            titulares, ou seja , caso não exista nif o utilizador não existe
                            logo podemos para o ciclo pois já mostramos todos os titulares
                            */
                            if (cont[i].titular[j].nifTitular == 0){
                                break;
                            }
                            printf("\nTitular/es: %s",cont[i].titular[j].nomeCliente);
                            printf("\nData de Nascimento: %0.2d/%0.2d/%0.4d",cont[i].titular[j].dataNascimeto.dia,cont[i].titular[j].dataNascimeto.mes,cont[i].titular[j].dataNascimeto.ano);
                            printf("\nNIF: %d\n",cont[i].titular[j].nifTitular);
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

//FUNÇÃO Depositar
/*Esta Função permite-nos depositar algum valor numa determinada conta*/
void Depositar(Conta cont[MAXCONTAS], int NcontasAtualmente){
system("cls");
//variaveis
int nContaPretendido=0;
float valorDeposito=0;
float ultimoMovimento;
float PnultimoMovimento;
float AntePnultimoMovimento;
    /*Verificar se atualmente existem contas , se não existirem é apresentado uma mensagem ao utilizador*/
    if (NcontasAtualmente==0){
        printf("\n!!! NÃO EXISTEM CONTAS ATUALMENTE !!!\n");
    }
    else{
        /*Recolher o numero da conta pretendida*/
        printf("\nNumero da conta Pretendida:");
        scanf("%d",&nContaPretendido);
            /*Neste ciclo percorremos todas as contas*/
            for(int i=0 ; i<NcontasAtualmente; i++){
                /*
                Verificamos se o numero da conta é o mesmo que a conta pretendida
                */
                if (cont[i].numeroConta == nContaPretendido){
                    /*Recolher valor do deposito pretendido*/
                    printf("\nValor do Deposito:");
                    scanf("%f",&valorDeposito);

                        //REALIZAÇÃO DO HISTORICO
                        /*
                        Recolhemos os ultimos 3 movimentos do utilizador.
                        De seguida fazemos uma substituição dos valores, ou seja:

                        ultimoMovimento -> PnultimoMovimento -> AntePnultimoMovimento

                        após a substituição será

                        Valor do Saldo antes do deposito -> ultimoMovimento -> PnultimoMovimento

                        Desta forma conseguimos sempre manter atualizado os movimentos do saldo.
                        */
                        //Recolha dos valores
                        ultimoMovimento       = cont[i].historico[2];
                        PnultimoMovimento     = cont[i].historico[1];
                        AntePnultimoMovimento = cont[i].historico[0];
                        //Substituição dos valores
                        cont[i].historico[2] = cont[i].saldoAtual;
                        cont[i].historico[1] = ultimoMovimento;
                        cont[i].historico[0] = PnultimoMovimento;

                    /*Atualização do saldo somando o valor do deposito*/
                    cont[i].saldoAtual=  cont[i].saldoAtual + valorDeposito;
                    printf("\n---DEPOSITO EFETUADO COM SUCESSO , OBRIGADO !---\n");
                    printf("\n\nSALDO ATUAL: %.2f\n",cont[i].saldoAtual);
                    break;
                }
            }
    }
}

//FUNÇÃO Levantar
/*Esta Função permite-nos levantar algum valor numa determinada conta*/
void Levantar(Conta cont[MAXCONTAS], int NcontasAtualmente){
system("cls");

//variaveis
int nContaPretendido=0;
float valorLevantar=0;
float ultimoMovimento;
float PnultimoMovimento;
float AntePnultimoMovimento;
char normal[100]="normal";
int verdadeiro=0;

    /*Verificar se atualmente existem contas , se não existirem é apresentado uma mensagem ao utilizador*/
    if (NcontasAtualmente==0){
        printf("\n!!! NÃO EXISTEM CONTAS ATUALMENTE !!!\n");
    }
    else{
     /*Recolha do numero da conta pretendida*/
     printf("\nNumero da conta Pretendida:");
     scanf("%d",&nContaPretendido);
        /*Neste ciclo percorremos todas as contas e verificamos se a conta é a mesma que procuramos*/
        for(int i=0 ; i<NcontasAtualmente; i++){
            if (cont[i].numeroConta == nContaPretendido){
                /*Caso o utilizado esteja com o saldo abaixo de 0 não pode levantar dinheiro*/
                if(cont[i].saldoAtual <= 0){
                    printf("\n!!! SALDO ENIXESTENTE !!!\n");
                    break;
                }
                else{
                /*Recolha do valor a levantar da conta*/
                printf("\nValor que deseja levantar:");
                scanf("%f",&valorLevantar);
                    /*
                      //REALIZAÇÃO DO HISTORICO
                    Recolhemos os ultimos 3 movimentos do utilizador.
                    De seguida fazemos uma substituição dos valores, ou seja:

                    ultimoMovimento -> PnultimoMovimento -> AntePnultimoMovimento

                    após a substituição será

                    Valor do Saldo antes do deposito -> ultimoMovimento -> PnultimoMovimento

                    Desta forma conseguimos sempre manter atualizado os movimentos do saldo.
                    */
                    //Recolha dos valores
                    ultimoMovimento       = cont[i].historico[2];
                    PnultimoMovimento     = cont[i].historico[1];
                    AntePnultimoMovimento = cont[i].historico[0];
                    //Substituição dos valores
                    cont[i].historico[2] = cont[i].saldoAtual;
                    cont[i].historico[1] = ultimoMovimento;
                    cont[i].historico[0] = PnultimoMovimento;
                    /*
                        //Verificação da modalidade

                        Antes de se realizar a transferencia teremos de verificar a modalidade da conta.
                        Para isso percorremos a string 'modalidade[100]' e comparamos com a string 'nomal[100]'.
                        Se o mesmo for verdadeiro quer dizer que a conta tem a modalidade normal e dessa forma será
                        descontado mais 5euros na conta.
                    */
                    for(int j = 0 ; j<100 ; j++){
                       if(cont[i].modalidade[j]==normal[j]){
                        verdadeiro=1;
                       }
                       else{
                        verdadeiro=0;
                        break;
                       }
                    }
                if( verdadeiro==1){
                    cont[i].saldoAtual  =  cont[i].saldoAtual - (valorLevantar + 5);
                }
                else{
                    cont[i].saldoAtual  =  cont[i].saldoAtual - valorLevantar ;
                }
            }
            printf("\n---LEVANTAMENTO EFETUADO COM SUCESSO , OBRIGADO !---\n");
            printf("\n\nSALDO ATUAL: %.2f\n",cont[i].saldoAtual);
            break;
            }
        }
    }
}

//FUNÇÃO Transferir
/*Esta Função permite-nos levantar algum valor numa determinada conta*/
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
char normal[100]="normal";
int verdadeiro=0;
int contasExistem=0;
    /*Verificar se atualmente existem contas , se não existirem é apresentado uma mensagem ao utilizador*/
    if (NcontasAtualmente==0){
        printf("\n!!! NÃO EXISTEM CONTAS ATUALMENTE !!!\n");
    }
    else{
        /*Recolher o Numero da Conta de origem(Conta que envia o dinheiro)*/
        printf("\nNumero da conta Origem:");
        scanf("%d",&nContaEnviar);
       /*Recolher o Numero da Conta de destino(Conta que recebe o dinheiro)*/
        printf("\nNumero da conta Destino:");
        scanf("%d",&nContaReceber);

            /*Percorrer todas as contas e encontrar a conta de origem*/
            for(int i=0 ; i<NcontasAtualmente; i++){
                if (cont[i].numeroConta == nContaEnviar){
                  posicaoContaEnviar = i;
                  contasExistem=1;
                }
                else{
                 contasExistem=0;
                }
            }
            /*Percorrer todas as contas e encontrar a conta de destino*/
            for(int i=0 ; i<NcontasAtualmente; i++){
                if (cont[i].numeroConta == nContaReceber){
                  posicaoContaReceber = i;
                  contasExistem=1;
                }
                else{
                contasExistem=0;
                }
            }




        if(contasExistem == 1){

            //Valor a ser transferido
            printf("Introduza o valor a transferir da conta nº%d para a conta nº%d : ",cont[posicaoContaEnviar].numeroConta,cont[posicaoContaReceber].numeroConta);
            scanf("%f",&valorTransferir);
                /*
                  //REALIZAÇÃO DO HISTORICO
                Recolhemos os ultimos 3 movimentos do utilizador.
                De seguida fazemos uma substituição dos valores, ou seja:
                ultimoMovimento -> PnultimoMovimento -> AntePnultimoMovimento
                após a substituição será
                Valor do Saldo antes do deposito -> ultimoMovimento -> PnultimoMovimento
                Desta forma conseguimos sempre manter atualizado os movimentos do saldo.
                */

                //REALIZAÇÃO DO HISTORICO PARA A CONTA DE ORIGEM
                 //Recolha dos valores
                ultimoMovimento       = cont[posicaoContaEnviar].historico[2];
                PnultimoMovimento     = cont[posicaoContaEnviar].historico[1];
                AntePnultimoMovimento = cont[posicaoContaEnviar].historico[0];
                //Substituição dos valores
                cont[posicaoContaEnviar].historico[2] = cont[posicaoContaEnviar].saldoAtual;
                cont[posicaoContaEnviar].historico[1] = ultimoMovimento;
                cont[posicaoContaEnviar].historico[0] = PnultimoMovimento;

                //REALIZAÇÃO DO HISTORICO PARA A CONTA DE DESTINO
                //Recolha dos valores
                ultimoMovimento       = cont[posicaoContaReceber].historico[2];
                PnultimoMovimento     = cont[posicaoContaReceber].historico[1];
                AntePnultimoMovimento = cont[posicaoContaReceber].historico[0];
                //Substituição dos valores
                cont[posicaoContaReceber].historico[2] = cont[posicaoContaReceber].saldoAtual;
                cont[posicaoContaReceber].historico[1] = ultimoMovimento;
                cont[posicaoContaReceber].historico[0] = PnultimoMovimento;

                 /*
                        //Verificação da modalidade
                        Antes de se realizar a transferencia teremos de verificar a modalidade da conta.
                        Para isso percorremos a string 'modalidade[100]' e comparamos com a string 'nomal[100]'.
                        Se o mesmo for verdadeiro quer dizer que a conta tem a modalidade normal e dessa forma será
                        descontado mais 5euros na conta.
                    */
                for(int j = 0 ; j<100 ; j++){
                   if(cont[posicaoContaEnviar].modalidade[j]==normal[j]){
                    verdadeiro=1;
                   }
                   else{
                    verdadeiro=0;
                    break;
                   }
                }
                if( verdadeiro==1){
               cont[posicaoContaEnviar].saldoAtual=cont[posicaoContaEnviar].saldoAtual-(valorTransferir+5);
                }
                else{
                 cont[posicaoContaEnviar].saldoAtual=cont[posicaoContaEnviar].saldoAtual-valorTransferir;
                }
        cont[posicaoContaReceber].saldoAtual=cont[posicaoContaReceber].saldoAtual+valorTransferir;
        printf("\n---TRANSFERENCIA EFETUADA COM SUCESSO , OBRIGADO !---\n");
        }
        else{
            printf("\n!!! UMA DAS CONTAS INSERIDAS NÃO EXISTE , TENTE NOVAMENTE \n!!!");
        }
    }
    }


//FUNÇÃO EditarTipoDeConta
/*Esta Função permite-nos levantar algum valor numa determinada conta*/
void EditarTipoDeConta(Conta cont[MAXCONTAS], int NcontasAtualmente){
system("cls");
//variaveis
int nContaPretendido=0;
float valorLevantar=0;
char OPCmodalidade;
char naoIsento[100]="normal";
char isento[100]="isento";
    /*Verificar se atualmente existem contas , se não existirem é apresentado uma mensagem ao utilizador*/
    if (NcontasAtualmente==0){
        printf("\n!!! NÃO EXISTEM CONTAS ATUALMENTE !!!\n");
    }
    else{
    /*Pedir ao utilizador da conta pretendida*/
    printf("\nNumero da conta Pretendida:");
    scanf("%d",&nContaPretendido);
        /*Percorrer todas as contas e encontrar a pretendida*/
        for(int i=0 ; i<NcontasAtualmente; i++){
            if (cont[i].numeroConta == nContaPretendido){
                /*Substituir a modalidade*/

                /*
                Caso o utilizador selecionar a opção 'n' ou 'N' correspondendo à modalidade
                normal iremos utilizar  uma função da biblioteca das strings , 'strcpy' , para
                copiar o valor da modalidade 'normal' que é guardada atraves da variavel 'naoisento'.

                Caso o utilizador selecionar a opção 'i' ou 'I' correspondendo à modalidade
                isento iremos utilizar  uma função da biblioteca das strings , 'strcpy' , para
                copiar o valor da modalidade 'isento' que é guardada atraves da variavel 'isento'.
                */

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
}

//FUNÇÃO AdicionarTitular
/*Esta Função permite-nos mostrar Adicionar um titular a uma determinada conta*/
 void AdicionarTitular(Conta cont[MAXCONTAS], int NcontasAtualmente){
system("cls");
printf("||| Adicionar Titular |||\n\n");

//variaveis
int nContaPretendido=0;
int contador=0;
    /*Verificar se atualmente existem contas , se não existirem é apresentado uma mensagem ao utilizador*/
    if (NcontasAtualmente==0){
        printf("\n!!! NÃO EXISTEM CONTAS ATUALMENTE !!!\n");
    }
    else{
    /*Pedir ao utilizador da conta pretendida*/
    printf("\nNumero da conta:");
    scanf("%d",&nContaPretendido);
    printf("---CONTA %d---", nContaPretendido);
        /*Percorrer todas as contas e encontrar a pretendida*/
        for(int i=0 ; i<NcontasAtualmente; i++){
                if (cont[i].numeroConta == nContaPretendido){
                   /*
                    Neste ciclo 'for' vamos recolher a informação relativa ao numero de titulares para
                    cada conta, este têm um limite de 5 titulares por conta aberta (Dado fornecido pela
                    constante MAXTITULARES definida com o valor '5')
                    */
                    for(int j=0; j<MAXTITULARES;j++){
                        /*Caso esteja vazio popular esta posição*/
                        if (cont[i].titular[j].nifTitular == 0){
                           printf("\nNome:");
                           scanf("%s" , &cont->titular[j].nomeCliente);

                            printf("\nIntroduza a sua data de nascimento no formato dd/mm/aa :\n");
                            scanf("%d/%d/%d",&cont->titular[j].dataNascimeto.dia,&cont->titular[j].dataNascimeto.mes,&cont->titular[j].dataNascimeto.ano);

                            printf("\nIntroduza o NIF :");
                            scanf("%d",&cont->titular[j].nifTitular);
                            printf("\n\nTitular Adicionado com sucesso!\n\n");
                            break;
                        }
                        /*Contador para guardar o total de titulares preenchidos*/
                        else{contador++;}

                    }
                }
        }
        /*Se o contador for 5 quer dizer que o total de titulares foi atingido*/
        if ( contador== 5 ){
            printf("\n!!!NUMERO MAXIMO DE TITULARES ATINGIDO!!!\n");

        }
    }
}

//FUNÇÃO EliminarConta
/*Esta Função permite-nos Eliminar uma conta */
void EliminarConta(Conta cont[MAXCONTAS], int NcontasAtualmente){

//variaveis
int nContaPretendido=0;
int contador=MAXCONTAS;
printf("\nNumero da conta:");
scanf("%d",&nContaPretendido);
     for(int i=0 ; i<NcontasAtualmente; i++){
                 if (cont[i].numeroConta == nContaPretendido){
                    for(int j = i-1; i<contador-1; i++)
                    {
                    cont[i] = cont[i + 1];
                    }
                    contador--;
                 }
    }
}

//FUNÇÃO GravarFicheitoTexto
/*Esta Função permite-nos guardar os dados relativos a todas as contas num ficheiro de texto (.txt)*/
void GravarFicheitoTexto(Conta cont[MAXCONTAS], int NcontasAtualmente){


FILE *f;

f=fopen("contas.txt","w");
if(f == NULL){
    printf("ERRO! FICHEIRO INEXISTENTE\n");
    return;
}
for(int i=0 ; i<NcontasAtualmente; i++){
        fprintf(f,"\n---------- Nº CONTA: %d ----------",cont[i].numeroConta);
            for(int j=0; j<MAXTITULARES;j++){
                 if (cont[i].titular[j].nifTitular == 0){
                    break;
                }
                fprintf(f,"\nTitular/es: %s",cont[i].titular[j].nomeCliente);
                fprintf(f,"\nData de Nascimento: %0.2d/%0.2d/%0.4d",cont[i].titular[j].dataNascimeto.dia,cont[i].titular[j].dataNascimeto.mes,cont[i].titular[j].dataNascimeto.ano);
                fprintf(f,"\nNIF: %d\n",cont[i].titular[j].nifTitular);
            }
        fprintf(f,"---------------------------------\n");
        fprintf(f,"\nModalidade da conta:%s\n",cont[i].modalidade);
        fprintf(f,"SALDO ATUAL: %.2f\n",cont[i].saldoAtual);
        fprintf(f,"\nHistorico:\n");
            for(int j=0 ; j<MAXHISTORICO ; j++){
                fprintf(f,"%dº valor : %.2f\n\n",j+1 ,cont[i].historico[j]);
            }
        fprintf(f,"Data de Abertura da conta : %0.2d/%0.2d/%0.4d\n\n",cont[i].dataAbertura.dia,cont[i].dataAbertura.mes,cont[i].dataAbertura.ano);
    }

fclose(f);
 printf("\n\n!! Contas Gravadas no ficheiro !!\n\n");

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
            EliminarConta(contas, numeroContas);
        break;
         case 9:
           GravarFicheitoTexto(contas, numeroContas);
        break;
        case 10:
        return 0;
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
