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
