#include <stdio.h>
#include <stdlib.h>

#define CADASTRAR_EVENTO 1
#define CADASTRAR_CLIENTE 2
#define VENDER_INGRESSO 3

#include "evento.h"

void imprimirMenu();

int main() {
  imprimirMenu();
  return 0;
}

void imprimirMenu() {
  int opcao;
  int sair = 0;
  while(sair == 0) {
    printf("1) Cadastrar Evento\n2) Cadastrar Cliente\n3) Vender Ingresso\n4) Sair\n");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case CADASTRAR_EVENTO:
      printf("Cadastro de Evento: \n");
      iniciarEventos();
      imprimirEvento(1);
      break;
    case CADASTRAR_CLIENTE:
      printf("Cadastro de Cliente: \n");
      break;
    case VENDER_INGRESSO:
      printf("Venda de Ingressos: \n");
      break;
    default:
      sair = 1;
      break;
    }
  }
}