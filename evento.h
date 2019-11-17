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
  struct Evento eventos[2] = {{1, "evento 1", 25, 25.5, "13:00", "20/05/20", {' ', '0', '1', '2', '3', '4','0', '-', '-', '-', '-', '-','1', '-', '-', '-', '-', '-','2', '-', '-', '-', '-', '-','3', '-', '-', '-', '-', '-','4', '-', '-', '-', '-', '-'}}, {2, "evento 2", 25, 10, "17:00", "12/12/20", {' ', '0', '1', '2', '3', '4','0', '-', '-', '-', '-', '-','1', '-', '-', '-', '-', '-','2', '-', '-', '-', '-', '-','3', '-', '-', '-', '-', '-','4', '-', '-', '-', '-', '-'}}};
  
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
  printf("============\n");
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
  printf("============\n");
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

extern void venderIngresso() {
      struct Evento e;
      struct Poltrona poltrona;
      int opcao;
      system("clear");
      listarEventos();
      e = escolherEvento();
      system("clear");
      imprimirDetalheEvento(e);
      printf("\n ---- Deseja comprar ingresso? ----\n1) Sim\n2) Nao\n");
      scanf("%d", &opcao);
      if (opcao == 1) {
        system("clear");
        poltrona = escolherPoltronaAleatoria(e);
        e = marcarPoltrona(e, poltrona);
        mostrarVagas(e.mapaSala, poltrona);
        diminuirVaga(e);
        imprimirDetalheEvento(buscarEvento(e.id));
        printf("\n ---- Venda efetuada com sucesso! ----\n\n");
      }
}