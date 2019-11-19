#include <string.h>
#include "utils.h"

extern struct Evento
{
  int id;
  char nome[150];
  int vagas;
  float preco;
  char hora[5];
  char data[10];
  char mapaSala[6][6];
} Evento;

extern struct Poltrona {
  int x;
  int y;
} Poltrona;

struct Cliente {
    int id;
    int idade;
    char profissao[150];
} Cliente;

extern void salvarEvento(struct Evento evento, char *arquivo)
{
    FILE *file;
    file = abrirArquivo(arquivo, "ab");
    fwrite(&evento, sizeof(struct Evento), 1, file);
    fecharArquivo(file);
}

// Essa funcao salva eventos em um arquivo
extern void iniciarEventos()
{
  int i;
  struct Evento eventos[2] = {{1, "evento 1", 25, 25.5, "13:00", "20/05/20", {' ', '0', '1', '2', '3', '4','A', '-', '-', '-', '-', '-','B', '-', '-', '-', '-', '-','C', '-', '-', '-', '-', '-','D', '-', '-', '-', '-', '-','E', '-', '-', '-', '-', '-'}}, {2, "evento 2", 25, 10, "17:00", "12/12/20", {' ', '0', '1', '2', '3', '4','A', '-', '-', '-', '-', '-','B', '-', '-', '-', '-', '-','C', '-', '-', '-', '-', '-','D', '-', '-', '-', '-', '-','E', '-', '-', '-', '-', '-'}}};
  
  for (i=0; i<2; i++) {
    salvarEvento(eventos[i], "database/eventos");
  }

}

extern struct Evento buscarEvento(int idEvento) {
  struct Evento evento;
	FILE *file;
	int origem;
	file = abrirArquivo("database/eventos","r");
	origem = ((idEvento-1) * sizeof(struct Evento));
	fseek(file, origem, SEEK_SET);
	fread(&evento, sizeof(struct Evento), 1, file);
	fecharArquivo(file);
  return evento;
}

extern char obterCodigo (struct Poltrona p) {
  char c = ' ';
  if (p.x == 1) {
    c = 'A';
  }
  if (p.x == 2) {
    c = 'B';
  }
  if (p.x == 3) {
    c = 'C';
  }
  if (p.x == 4) {
    c = 'D';
  }
  return c;
}

extern void imprimirDetalheEvento(struct Evento e) {
  printf("+---------------------------------------------------------------+\n");
  printf("| ID: %d       | Nome: %s\n", e.id, e.nome);
  printf("+---------------------------------------------------------------+\n");
  printf("| Hora: %s   | Data: %s | Vagas Disponiveis: %d\n", e.hora, e.data, e.vagas);
  printf("+---------------------------------------------------------------+\n");
  printf("| Precos                                                        |\n");
  printf("+---------------------------------------------------------------+\n");
  printf("| Integral:              %8.2f\n", e.preco);
  printf("| Meia entrada:          %8.2f\n", e.preco / 2);
  printf("| Infatil Rede publica:  %8.2f\n", e.preco * 0);
  printf("+---------------------------------------------------------------+\n\n");
}

extern void imprimirIngresso(struct Evento e, struct Poltrona p, float precoIngresso) {
  printf("+---------------------------------------------------------------+\n");
  printf("| ID: %d       | Nome: %s\n", e.id, e.nome);
  printf("+---------------------------------------------------------------+\n");
  printf("| Hora: %s   | Data: %s | Vagas Disponiveis: %d\n", e.hora, e.data, e.vagas);
  printf("+---------------------------------------------------------------+\n");
  printf("| Poltrona: %c%d                                                 |\n", obterCodigo(p), p.y - 1);
  printf("| PRECO: %.2f                                                  |\n", precoIngresso);
  printf("+---------------------------------------------------------------+\n");
}

extern void imprimirEvento (struct Evento e) {
  printf("+---------------------------------------------------------------+\n");
  printf("| ID: %d       | Vagas: %d | Nome: %s\n", e.id, e.vagas, e.nome);
  printf("+---------------------------------------------------------------+\n");
}

extern int escolherEstrutura(int opcao){
	int tamanho;
	if(opcao == 0){
		tamanho = sizeof(struct Evento);
	}
	return tamanho;
}

extern int incrementarIdEvento(char *arquivo){
	int id, t;
	id = retornarTamanho(arquivo);
	t = escolherEstrutura(0);
	id = (id/t) + 1;
	return id;
}

extern void listarEventos(){
	int size, i;
	size =  incrementarIdEvento("database/eventos") - 1;
	struct Evento evento;
	for(i=0; i<size; i++){
    imprimirEvento(buscarEvento(i+1));
	}
}

extern struct Evento escolherEvento() {
  int opcao;
  printf("Escolha o ID do evento que deseja vender: ");
  scanf("%d", &opcao);
  return buscarEvento(opcao);
}

extern void diminuirVaga(struct Evento n){
	int size, i, origem = 0;
	size = incrementarIdEvento("database/eventos") - 1;
	struct Evento a[size];
	FILE *file = abrirArquivo("database/eventos","r");
	for(i=0; i<size; i++){
		fseek(file,origem,SEEK_SET);
		origem = origem + sizeof(struct Evento);
		fread(&a[i],sizeof(struct Evento),1,file);
		if(n.id == a[i].id){
      n.vagas = n.vagas - 1;
			fecharArquivo(file);
			file = abrirArquivo("database/eventos","wb");
			origem = origem - sizeof(struct Evento);
			fseek(file,origem,SEEK_SET);
			fwrite(&n, sizeof(struct Evento), 1, file);
		}
	}
	fecharArquivo(file);
}

void mostrarVagas(char poltronas[6][6], struct Poltrona poltrona) {
  int i, j;
  printf("============== MAPA DA SALA ===============\n");
  for (i = 0; i < 6; i++)
  {
    for (j = 0; j < 6; j++)
    {
      if (poltrona.x == i && poltrona.y == j) {
       printf("[%c] ", poltronas[i][j]);
      } else {
       printf(" %c  ", poltronas[i][j]); 
      }
    }
    printf("\n");
  }
  printf("============== MAPA DA SALA ===============\n");
}

extern struct Poltrona escolherPoltronaAleatoria (struct Evento evento) {
  struct Poltrona poltrona;
  int x, y, sair = 0;

  do {
    x = rand() % 5;
    y = rand() % 5;
    if ((x > 0 && y > 0)) {
      if (evento.mapaSala[x][y] == '-') {
        poltrona.x = x;
        poltrona.y = y;
        sair = 1;
      }
    }
  } while(sair == 0);

  return poltrona;
} 

extern struct Evento marcarPoltrona (struct Evento evento, struct Poltrona poltrona) {
  evento.mapaSala[poltrona.x][poltrona.y] = 'X';
  return evento;
}

extern int temIdadePrivilegiada (int idade) {
  if ((idade > 1 && idade < 13) || (idade >= 60)) {
    return 1;
  }
  return 0;
}

extern int estudanteRedePublica (struct Cliente cliente) {
  char profissao[150] = "Estudante Rede Publica";
  if (strcmp(cliente.profissao, profissao) == 0) {
    return 1;
  }
  return 0;
}

extern int aplicarMeiaEntrada (struct Cliente cliente) {
  if ((temIdadePrivilegiada(cliente.idade)) || (strcmp(cliente.profissao, "Professor (Rede Publica)") == 0)) {
    return 1;
  }
  return 0;
}

extern struct Cliente* listarClientes () {
  int i;
  struct Cliente * pClientes;
  struct Cliente c[] = {{1, 8, "Estudante Rede Publica" }, { 2, 69, "Adulto"}, {3, 25, "Professor (Rede Publica)" }};
  for (i=0; i < 3; i++) {
    printf("#%d -- Idade: %d ----- Nome: %s \n", c[i].id, c[i].idade, c[i].profissao);
  }
  pClientes = c;
  return pClientes;
}

extern float obterValorEntrada (struct Evento evento) {
  int idCliente;
  float precoEntrada = evento.preco;
  struct Cliente * c = listarClientes();
  printf("Qual o ID do cliente?\n");
  scanf("%d", &idCliente);

  if (aplicarMeiaEntrada(c[idCliente - 1]) == 1) {
    precoEntrada = precoEntrada / 2;
  } 
  if (estudanteRedePublica(c[idCliente - 1]) == 1) {
    precoEntrada = precoEntrada * 0;
  }

  return precoEntrada;
}

extern void venderIngresso() {
      struct Evento e;
      struct Poltrona poltrona;
      int opcao;
      int tipoCliente;
      float precoIngresso;
      system("clear");
      listarEventos();
      e = escolherEvento();
      system("clear");
      imprimirDetalheEvento(e);
      printf("\n ---- Deseja comprar ingresso? ----\n1) Sim\n2) Nao\n");
      scanf("%d", &opcao);
      if (opcao == 1) {
        system("clear");
        precoIngresso = obterValorEntrada(e);
        poltrona = escolherPoltronaAleatoria(e);
        e = marcarPoltrona(e, poltrona);
        mostrarVagas(e.mapaSala, poltrona);
        diminuirVaga(e);
        // imprimirDetalheEvento(buscarEvento(e.id));
        imprimirIngresso(buscarEvento(e.id), poltrona, precoIngresso);
        printf("\n ---- Venda efetuada com sucesso! ----\n\n");
      }
}