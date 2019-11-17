#include "utils.h"

extern struct Evento
{
  int id;
  char nome[150];
  int vagas;
  float preco;
  char hora[5];
  char data[10];
} Evento;

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
  struct Evento eventos[2] = {{1, "evento 1", 15, 25.5, "13:00", "20/05/20"}, {2, "evento 2", 30, 10, "17:00", "12/12/20"}};
  
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
