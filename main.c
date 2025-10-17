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
    
    //Percorre array de perguntas
    while(controle < total_perguntas){

        
        //Gera indice aleatorio
        if(perguntas[controle].nivel == 1){
            ind_pergunta = rand() % 20;
            
        }else if(perguntas[controle].nivel == 2){
            ind_pergunta = 20 + rand() % 40;
        
        }else if(perguntas[controle].nivel == 3){
            ind_pergunta = 40 + rand() % 60;
            
        }else if(perguntas[controle].nivel == 4){
            ind_pergunta = 60 + rand() % 70;
            
        }

        //Mostra pergunta do indice aleatorio gerado
        printf("Nivel %d\n", perguntas[ind_pergunta].nivel);
        printf("%s\n", perguntas[ind_pergunta].descricao);
        
        for (int j = 0; j < 4; j++)
        {
            printf("%s\n\n", perguntas[ind_pergunta].alt[j]);
        }
        
        printf("Digite a alternativa:\n");
        scanf("%c\n", &resposta);

        //Verifica resposta do usuario e incrementa valor ganho
        if(resposta == perguntas[ind_pergunta].alt_correta){
            if(perguntas[ind_pergunta].nivel == 1){
                valor_ganho+=1000;
            }else if(perguntas[ind_pergunta].nivel == 2){
                valor_ganho+=10000;
            }else if(perguntas[ind_pergunta].nivel == 3){
                valor_ganho+=100000;
            }else if(perguntas[ind_pergunta].nivel == 4){
                valor_ganho+=100000;
            }
        }else{
            printf("Voce perdeu.");
            break;
        }



        controle++;
    }

    

       
        

   
        

        

        
    

    fclose(ptr_f);
    


}