🎮 Jogo de Perguntas e Respostas (Estilo Show do Milhão)

Este projeto é um jogo de perguntas e respostas em C, inspirado no formato do Show do Milhão.
O jogador avança por níveis de dificuldade, responde perguntas, utiliza ajudas estratégicas e pode parar a qualquer momento para garantir o prêmio acumulado.

📌 Funcionalidades

  Sistema de níveis de dificuldade

  Perguntas carregadas a partir de um arquivo binário

  Alternativas de múltipla escolha (A, B, C, D)

  Sistema de ajudas:

    Pular pergunta

    Ajuda da plateia

    Ajuda dos universitários

    Ajuda das cartas (elimina alternativas)

    Sistema de premiação progressiva

    Controle de perguntas repetidas

    Finalização voluntária ou automática (vitória/derrota)

🧠 Estrutura do Jogo

O jogo é dividido em 4 níveis:

Nível	Quantidade de Perguntas	Valor Máximo
1	5 perguntas	R$ 5.000
2	5 perguntas	R$ 50.000
3	5 perguntas	R$ 500.000
4	1 pergunta	R$ 1.000.000

Ao passar de nível, o jogador garante um valor mínimo acumulado, mesmo que erre depois.

🆘 Sistema de Ajudas

Cada ajuda pode ser usada até 3 vezes durante o jogo:

  Pular Pergunta: Ignora a pergunta atual sem penalidade.

  Ajuda da Plateia: Simula votos do público, com maior chance da alternativa correta.

  Ajuda dos Universitários: Três votos com alta probabilidade de acerto.

  Ajuda das Cartas: Elimina duas alternativas incorretas aleatoriamente.

🗂 Estrutura de Dados
struct Pergunta
struct pergunta {
    char nivel;
    char descricao[200];
    char alt[4][30];
    char alt_correta;
};


Cada pergunta contém:

  Nível de dificuldade

  Enunciado

  4 alternativas

  Alternativa correta ('a', 'b', 'c' ou 'd')

📂 Arquivo de Perguntas

O jogo lê as perguntas a partir do arquivo binário: perguntas.dat


Esse arquivo deve conter até 70 perguntas, organizadas por nível.

⚠️ Importante:
O arquivo deve estar no mesmo diretório do executável.

▶️ Como Compilar e Executar
Compilação
gcc main.c -o jogo

Execução
./jogo

🎯 Objetivo do Projeto

  Este projeto tem como objetivo:

  Praticar estruturas de dados em C

  Trabalhar com arquivos binários

  Simular regras de negócio

  Aplicar controle de fluxo, aleatoriedade e interação com o usuário

🚀 Possíveis Melhorias Futuras

  Interface gráfica

  Ranking de jogadores

  Sistema de persistência de pontuação

  Leitura de perguntas a partir de arquivos de texto

  Suporte a mais níveis e perguntas dinâmicas

🧑‍💻 Autor

Projeto desenvolvido para fins educacionais, focado no aprendizado da linguagem C e lógica de programação.
