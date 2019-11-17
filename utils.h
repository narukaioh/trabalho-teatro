#include<stdio.h>

extern FILE *abrirArquivo(char *address,char *mode){
	FILE *file = fopen(address, mode);
	if(!file){
		printf("\n\n\t\tErro! Problema na abertura do arquivo\n\n");
	}
	return file;
}

extern void fecharArquivo(FILE *file){
	if(fclose(file)){
		printf("\n\n\t\tErro! Problema para fechar o arquivo\n\n");
	}
}

extern int retornarTamanho(char *arquivo){
	int tamanho;
	FILE *file = abrirArquivo(arquivo,"r");
	fseek(file, 0, SEEK_END);
	tamanho = ftell(file);
	fecharArquivo(file);
	return tamanho;
}