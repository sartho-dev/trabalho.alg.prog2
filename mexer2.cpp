#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

typedef struct {
    char nivel;
    char descricao[200];
    char alt[4][30];
    char alt_correta;
} Pergunta;

// exibe uma pergunta e retorna se acertou ou não
int perguntar(Pergunta p, int *pulos, int *ajudas) {
    char resposta;
    char letras[] = {'a', 'b', 'c', 'd'};

    printf("\nNivel %d\n", p.nivel);
    printf("%s\n", p.descricao);

    for (int j = 0; j < 4; j++) {
        printf("%c) %s\n", letras[j], p.alt[j]);
    }

    printf("\n--Ajuda--\n");
    printf("[1] Pular Pergunta (%d restantes)\n", *pulos);
    printf("[2] Pedir ajuda da plateia (%d restantes)\n", *ajudas);
    printf("[3] Pedir ajuda aos universitários (%d restantes)\n", *ajudas);
    printf("[4] Pedir ajuda as cartas (%d restantes)\n", *ajudas);
    printf("[5] Parar\n");

    printf("\nDigite a alternativa: ");
    scanf(" %c", &resposta);
    resposta = tolower(resposta);

   
    if (resposta == '1') {
        if (*pulos > 0) {
            (*pulos)--;
            printf("Pergunta pulada! Pulso(s) restantes: %d\n", *pulos);
            return 2; 
        } else {
            printf("Você não tem mais pulos!\n");
            return 2; 
        }
    }

    else if (resposta == '2') {
        if (*ajudas > 0) {
            (*ajudas)--;

            int votos[4] = {0};
            int indice_correto = p.alt_correta - 'a';

            for (int i = 0; i < 30; i++)
            {
                int chance = rand() % 100; 

                if(chance < 40){
                    votos[indice_correto]++;
                }
                else if(chance < 60){
                    votos[(indice_correto + 1) % 4]++;
                }
                else if(chance < 80){
                    votos[(indice_correto + 2) % 4]++;
                }else{
                    votos[(indice_correto + 3) % 4]++;
                }
            }

            printf("A plateia diz que:\n");
            for (int i = 0; i < 4; i++)
            {
                printf("alternativa %c) é a correta com %d votos\n", letras[i], votos[i]);
            }

            
            
            printf("Ajuda utilizada! Ajudas restantes: %d\n", *ajudas);
        } else {
            printf("Você não tem mais ajudas!\n");
        }
        return 2; 
    }

    else if(resposta == '3'){

        if(*(ajudas) > 0){
            
            *(ajudas)--;

            int votos[4] = {0};
            int indice_correto = p.alt_correta - 'a';

            for (int i = 0; i < 3; i++)
            {
                int chance = rand() % 10;

                if(chance < 7){
                    votos[indice_correto]++;
                }
                else if(chance < 8){
                    votos[(indice_correto+ 1) % 4]++;
                }
                else if(chance < 9){
                    votos[(indice_correto + 2) % 4]++;
                }
                else{
                    votos[(indice_correto + 3) % 4]++;
                }

            }
            
            printf("\nOs universitarios dizem que:\n\n");
            for (int i = 0; i < 4; i++)
            {
                printf("alternativa %c) é a correta com %d votos\n", letras[i], votos[i]);
            }

            printf("\nAjuda utilizada! Ajudas restantes: %d\n", *ajudas);

        }else{
            printf("Você não tem mais ajudas!\n");
        }
        return 2; 
    }

    else if(resposta == '4'){
        if(*(ajudas) > 0){
            *(ajudas)--;

            int indice_correto = p.alt_correta - 'a';
            int eliminadas[4] = {0};

            int eliminadas_count = 0;

            while(eliminadas_count < 2){
                int indice = rand() % 4;

                if(indice != indice_correto && eliminadas[indice] == 0){
                    eliminadas[indice] = 1;
                    eliminadas_count++;
                }
            }
            

            printf("\nAjuda das cartas:\n");

            for (int i = 0; i < 4; i++)
            {
                if(eliminadas[i] == 1){
                    printf("%c) [ELIMINADA]\n", letras[i]);
                }else{
                    printf("%c) %s\n", letras[i], p.alt[i]);
                }
            }
            
        }else{
            printf("Você não tem mais ajudas!\n");
        }
        return 2; 
    }   
        

    if(resposta == '5'){
        return 0;
    }

    if (resposta == p.alt_correta) {
        return 1;
    } else {
        return 0; 
    }
}

int main() {
    Pergunta perguntas[70];
    FILE *ptr_f;
    int total_perguntas = 0;
    int valor_ganho = 0;
    int pulos = 3;
    int ajudas = 3;
    int repete[70] = {0};
    int qtd_perguntas =0;

    srand(time(NULL));

    ptr_f = fopen("perguntas.dat", "rb");
    if (ptr_f == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    total_perguntas = fread(perguntas, sizeof(Pergunta), 70, ptr_f);
    fclose(ptr_f);

    if (total_perguntas == 0) {
        printf("Nenhuma pergunta foi encontrada no arquivo\n");
        return 0;
    }

    // Loop por níveis
    for (int nivel = 1; nivel <= 4; nivel++) {
        int inicio, fim;

        if (nivel == 1) { inicio = 0; fim = 19; }
        else if (nivel == 2) { inicio = 20; fim = 39; }
        else if (nivel == 3) { inicio = 40; fim = 59; }
        else { inicio = 60; fim = 69; }

        if(nivel != 4){
            qtd_perguntas = 5;
        }else{
            qtd_perguntas = 1;
        }

        for (int i = 0; i < qtd_perguntas; i++) {
            int ind_pergunta;

            do {
                ind_pergunta = inicio + rand() % (fim - inicio + 1);
            } while (repete[ind_pergunta]);

            int resultado;

            while (1) {
                resultado = perguntar(perguntas[ind_pergunta], &pulos, &ajudas);

                if (resultado == 1) {
                // acerto
                switch (nivel) {
                    case 1: valor_ganho += 1000; break;
                    case 2: valor_ganho += 10000; break;
                    case 3: valor_ganho += 100000; break;
                    case 4: valor_ganho = 1000000; 
                            printf("Parabéns! Você venceu o jogo!\n");
                            printf("Total prêmio: R$ %d\n", valor_ganho);
                            return 0;
                }
                printf("Correto! Total até agora: R$ %d\n", valor_ganho);
                repete[ind_pergunta] = 1; // pergunta usada
                break; // vai para próxima pergunta
                } 
                else if (resultado == 0) {
                // Usuário parou ou errou
                    printf("Você decidiu parar ou errou a pergunta.\n");
                    return 1;
                } 
                else if (resultado == 2) {
                // Pergunta pulada ou ajuda usada
                    if (pulos > 0) { // se tiver pulos cai aqui
                        
                        repete[ind_pergunta] = 1; // marca como usada
                        break; // vai para próxima pergunta
                    }
                // se só foi ajuda ou nao tem mais pulos, repete a pergunta
                }
            }
            
        }
    }

    printf("Fim do jogo! Total ganho: R$ %d\n", valor_ganho);
    return 0;
}
