#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <ctype.h>


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
    int qtd_perguntas= 0;

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



    //Percorre array de perguntas
    for (int nivel_show = 1; nivel_show <= 4; nivel_show++){

        int inicio, fim;

        if(nivel_show == 1){ inicio = 0; fim = 19; }
        else if(nivel_show == 2){ inicio = 20; fim = 39; }
        else if(nivel_show == 3){ inicio = 40; fim = 59; }
        else {inicio = 60; fim = 69; }

        if(nivel_show != 4){
            qtd_perguntas = 5;
        }else{
            qtd_perguntas = 1;
        }
        
            for (int i = 0; i < qtd_perguntas; i++)
                {
                    int ind_pergunta = inicio + rand() % (fim - inicio + 1);

                    printf("\nNivel %d\n", perguntas[ind_pergunta].nivel);
                    printf("%s\n", perguntas[ind_pergunta].descricao);

                    char letras[]= {'a', 'b', 'c', 'd'}; 

                    for (int j = 0; j < 4; j++)
                    {
                        printf("%c) %s\n", letras[j], perguntas[ind_pergunta].alt[j]);
                    }       

                    printf("\nDigite a alternativa: ");
                    scanf(" %c", &resposta);

                    printf("%c\n", perguntas[ind_pergunta].alt_correta);
            

                    if (resposta == perguntas[ind_pergunta].alt_correta)
                    {
                        if(nivel_show == 1){
                            valor_ganho += 1000;
                        }else if(nivel_show == 2){
                            valor_ganho += 10000;
                        }else if(nivel_show == 3){
                            valor_ganho += 100000;
                        }else if(nivel_show == 4){
                            printf("Parabens, voce venceu o jogo.\n");
                            valor_ganho = 1000000;
                            printf("Total Prêmio: %d\n", valor_ganho);
                            return 0;
                        }

                        printf("Correto! Total até agora: R$ %d\n", valor_ganho);
                    } 
                    else 
                    {
                        printf("Resposta errada! Você perdeu.\n");
                        return 1;
                    }
            }
        
    

    

       
        

   
    }

        

        
    

    fclose(ptr_f);
    


}