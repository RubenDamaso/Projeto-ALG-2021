#ifndef CONTA_H_INCLUDED
#define CONTA_H_INCLUDED


#include "CLIENTE.h"
#include "DATA.h"

typedef struct{

 int numeroConta;
 Cliente titular[5];
 char modalidade[100];
 float saldoAtual;
 int historico[3];
 data dataAbertura;

}Conta;

#endif // CONTA_H_INCLUDED
