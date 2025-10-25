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

// Função que exibe uma pergunta e retorna se acertou ou não
int perguntar(Pergunta p, int *pulos, int *ajudas) {
    char resposta;
    char letras[] = {'a', 'b', 'c', 'd'};

    printf("\nNivel %c\n", p.nivel);
    printf("%s\n", p.descricao);

    for (int j = 0; j < 4; j++) {
        printf("%c) %s\n", letras[j], p.alt[j]);
    }

    printf("\n--Ajuda--\n");
    printf("[1] Pular Pergunta (%d restantes)\n", *pulos);
    printf("[2] Pedir ajuda da plateia (%d restantes)\n", *ajudas);
    printf("[3] Pedir ajuda as cartas (%d restantes)\n", *ajudas);
    printf("[4] Pular ajuda as cartas\n");

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

    if (resposta == '2' || resposta == '3') {
        if (*ajudas > 0) {
            (*ajudas)--;
            printf("Ajuda utilizada! Ajudas restantes: %d\n", *ajudas);
        } else {
            printf("Você não tem mais ajudas!\n");
        }
        return 2; 
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

            // Escolhe pergunta aleatória que ainda não foi usada
            do {
                ind_pergunta = inicio + rand() % (fim - inicio + 1);
            } while (repete[ind_pergunta]);

            int resultado;
            do {
                resultado = perguntar(perguntas[ind_pergunta], &pulos, &ajudas);
            } while (resultado == 2); // repetir se foi pulada ou pediu ajuda

            repete[ind_pergunta] = 1; 

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
            } else {
                printf("Resposta errada! Você perdeu.\n");
                return 1;
            }
        }
    }

    printf("Fim do jogo! Total ganho: R$ %d\n", valor_ganho);
    return 0;
}
