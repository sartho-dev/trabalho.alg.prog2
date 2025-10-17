#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


typedef struct {
    char nivel;
    char descricao[200];
    char alt[4][30];
    char alt_correta;
}Pergunta;

int main(){

    Pergunta perguntas[70];

    FILE *ptr_f;
    int total_perguntas = 0;
    int inc = 0;
    int controle = 0;
    int limitador = 0;
    char resposta;
    int valor_ganho = 0;


    srand(time(NULL));

    ptr_f = fopen("perguntas.dat", "rb");

    if (ptr_f == NULL){
        perror("Erro ao abrir o arquivo");
        return 1;
    }


    
    total_perguntas = fread(perguntas, sizeof(Pergunta), 70, ptr_f);

    if(total_perguntas == 0){
        printf("Nenhuma pergunta foi encontrada no arquivo");
        return 0;
    }


    int ind_pergunta = rand() % 20;
    int minimo = 0;

    //Percorre array de perguntas
    while(controle < total_perguntas){

        if(perguntas[controle].nivel == 1 || 2 || 3){
            ind_pergunta = + rand() % 20*perguntas[controle].nivel;
        }
        if(controle % 20 == 0){
            
        }

        controle++;
    }
    

    

       
        

   
        

        

        
    

    fclose(ptr_f);
    


}