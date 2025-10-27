#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

struct pergunta{
    char nivel;
    char descricao[200];
    char alt[4][30];
    char alt_correta;
};

typedef struct pergunta Pergunta;

// Função pergunta: exibe uma pergunta e retorna se acertou ou não
int perguntar(Pergunta p, int *pulos, int *ajuda_plateia, int *ajuda_universitarios, int *ajuda_cartas, int valor_ganho, int contador_pergunta) {
    char resposta;
    char letras[] = {'a', 'b', 'c', 'd'};

    printf("== --------------------------------------------------------\n");
    printf("== Nivel %d\n", p.nivel);
    printf("== Pergunta %d\n", contador_pergunta);
    printf("== Voce possui um total acumulado de R$ %d ==\n", valor_ganho);
    printf("\n%s\n", p.descricao);

    for (int j = 0; j < 4; j++) {
        printf("%c) %s\n", letras[j], p.alt[j]);
    }

    printf("\n-- Ajuda --\n");
    printf("[1] Pular Pergunta (%dx)\n", *pulos);
    printf("[2] Pedir ajuda a plateia (%dx)\n", *ajuda_plateia);
    printf("[3] Pedir ajuda aos universitarios (%dx)\n", *ajuda_universitarios);
    printf("[4] Pedir ajuda as cartas (%dx)\n", *ajuda_cartas);
    printf("[5] Parar\n");
    printf("~~~~~~~~~~~~~~~~~\n");

    printf("\nEntre com a sua opcao: ");
    scanf(" %c", &resposta);
    resposta = tolower(resposta);

    if (resposta == '1') {
        if (*pulos > 0) {
            *pulos = *pulos - 1;
            printf("\nPergunta pulada!\n\n");
            return 5;
        } 
        else {
            printf("Voce nao tem mais pulos!\n");
            return 2;
        }
    } 
    else if (resposta == '2') {
        if (*ajuda_plateia > 0) {
            *ajuda_plateia = *ajuda_plateia - 1;

            int votos[4] = {0};
            int indice_correto = p.alt_correta - 'a';

            for (int i = 0; i < 30; i++) {
                int chance = rand() % 100;

                if (chance < 40) {
                    votos[indice_correto]++;
                }
                else if (chance < 60) {
                    votos[(indice_correto + 1) % 4]++;
                }
                else if (chance < 80) {
                    votos[(indice_correto + 2) % 4]++;
                }
                else {
                    votos[(indice_correto + 3) % 4]++;
                }
            }

            printf("\nA plateia diz que:\n\n");
            for (int i = 0; i < 4; i++) {
                printf("alternativa %c) e a correta com %d votos\n", letras[i], votos[i]);
            }
        } 
        else {
            printf("Voce nao tem mais ajudas da plateia!\n");
        }
        return 2;
    } 
    else if (resposta == '3') {
        if (*ajuda_universitarios > 0) {
            *ajuda_universitarios = *ajuda_universitarios - 1;

            int votos[4] = {0};
            int indice_correto = p.alt_correta - 'a';

            for (int i = 0; i < 3; i++) {
                int chance = rand() % 10;

                if (chance < 7) {
                    votos[indice_correto]++;
                }
                else if (chance < 8) {
                    votos[(indice_correto + 1) % 4]++;
                }
                else if (chance < 9) {
                    votos[(indice_correto + 2) % 4]++;
                }
                else {
                    votos[(indice_correto + 3) % 4]++;
                }
            }

            printf("\nOs universitarios dizem que:\n\n");
            for (int i = 0; i < 4; i++) {
                printf("alternativa %c) e a correta com %d votos\n", letras[i], votos[i]);
            }
        } 
        else {
            printf("Voce nao tem mais ajudas dos universitarios!\n");
        }
        return 2;
    } 
    else if (resposta == '4') {
        if (*ajuda_cartas > 0) {
            *ajuda_cartas = *ajuda_cartas - 1;

            int indice_correto = p.alt_correta - 'a';
            int eliminadas[4] = {0};
            int eliminadas_count = 0;

            while (eliminadas_count < 2) {
                int indice = rand() % 4;
                if (indice != indice_correto && eliminadas[indice] == 0) {
                    eliminadas[indice] = 1;
                    eliminadas_count++;
                }
            }

            printf("\nAjuda das cartas:\n");
            for (int i = 0; i < 4; i++) {
                if (eliminadas[i] == 1){
                    printf("%c) [ELIMINADA]\n", letras[i]);
                }
                else {
                    printf("%c) %s\n", letras[i], p.alt[i]);
                }
            }
        } 
        else {
            printf("Voce nao tem mais ajudas das cartas!\n");
        }
        return 2;
    }

    if (resposta == '5') {
        return 4;
    }
    if (resposta == p.alt_correta) {
        return 1;
    }

    return 0;
}

int main() {
    Pergunta perguntas[70];
    FILE *ptr_f;
    int repete[70] = {0};
    int total_perguntas = 0;
    int valor_ganho = 0;
    int pulos = 3, ajuda_plateia = 3, ajuda_universitarios = 3, ajuda_cartas = 3;
    int qtd_perguntas = 0;
    int contador_pergunta = 1;

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

        if (nivel == 1) { 
            inicio = 0; fim = 19; 
        }
        else if (nivel == 2) { 
            inicio = 20; fim = 39; 
            if (valor_ganho < 10000) valor_ganho = 10000; 
        }
        else if (nivel == 3) { 
            inicio = 40; fim = 59;
            if (valor_ganho < 100000) valor_ganho = 100000;
        }
        else { 
            inicio = 60; fim = 69; 
        }

        qtd_perguntas = (nivel != 4) ? 5 : 1;

        for (int i = 0; i < qtd_perguntas; i++) {
            int ind_pergunta;

            do{
                ind_pergunta = inicio + rand() % (fim - inicio + 1);
            } while (repete[ind_pergunta]);

            int resultado;
            do{
                // Chamando a função pergunta
                resultado = perguntar(perguntas[ind_pergunta], &pulos, &ajuda_plateia, &ajuda_universitarios, &ajuda_cartas, valor_ganho, contador_pergunta);
            } while (resultado == 2); // repetir se pediu ajuda

            repete[ind_pergunta] = 1;

            if (resultado == 1) {
                contador_pergunta++;
                switch (nivel) {
                    case 1:
                        if (i == 0) valor_ganho = 1000;
                        else if (i == 1) valor_ganho = 2000;
                        else if (i == 2) valor_ganho = 3000;
                        else if (i == 3) valor_ganho = 4000;
                        else valor_ganho = 5000;
                        break;

                    case 2:
                        if (i == 0) valor_ganho = 10000;
                        else if (i == 1) valor_ganho = 20000;
                        else if (i == 2) valor_ganho = 30000;
                        else if (i == 3) valor_ganho = 40000;
                        else valor_ganho = 50000;
                        break;

                    case 3:
                        if (i == 0) valor_ganho = 100000;
                        else if (i == 1) valor_ganho = 200000;
                        else if (i == 2) valor_ganho = 300000;
                        else if (i == 3) valor_ganho = 400000;
                        else valor_ganho = 500000;
                        break;

                    case 4:
                        valor_ganho = 1000000;
                        printf("\n\n===== Parabens! Voce venceu o jogo! =====\n");
                        printf("Total premio: R$ %d\n\n", valor_ganho);
                        return 0;
                }
                printf("\n=== Resposta Correta!!! ===\n\n");
            } 
            else if (resultado == 4) {
                printf("\n\n===== Voce decidiu parar =====.\n");
                printf("Voce leva para casa: R$ %d\n\n", valor_ganho);
                return 1;
            } 
            else if (resultado == 5) {
                i--;
            } 
            else {
                printf("\n\n===== Resposta errada! Voce perdeu :( =====\n\n");
                return 1;
            }
        }
    }

    printf("Fim do jogo! Total ganho: R$ %d\n", valor_ganho);

    return 0;
}