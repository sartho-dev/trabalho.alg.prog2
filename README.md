# 🎮 Jogo de Perguntas e Respostas (Estilo Show do Milhão)

Este projeto é um **jogo de perguntas e respostas em C**, inspirado no formato do *Show do Milhão*.  
O jogador avança por níveis de dificuldade, responde perguntas, utiliza ajudas estratégicas e pode parar a qualquer momento para garantir o prêmio acumulado.

---

## 📌 Funcionalidades

- Sistema de **níveis de dificuldade**
- Perguntas carregadas a partir de um **arquivo binário**
- Alternativas de múltipla escolha (A, B, C, D)
- Sistema de **ajudas**:
  - Pular pergunta
  - Ajuda da plateia
  - Ajuda dos universitários
  - Ajuda das cartas
- Sistema de **premiação progressiva**
- Controle de perguntas repetidas
- Finalização voluntária ou automática (vitória/derrota)

---

## 🧠 Estrutura do Jogo

O jogo é dividido em **4 níveis**:

| Nível | Perguntas | Valor Máximo |
|------|----------|--------------|
| 1    | 5        | R$ 5.000     |
| 2    | 5        | R$ 50.000    |
| 3    | 5        | R$ 500.000   |
| 4    | 1        | R$ 1.000.000 |

Ao avançar de nível, o jogador garante um **valor mínimo acumulado**, mesmo que erre posteriormente.

---

## 🆘 Sistema de Ajudas

Cada ajuda pode ser utilizada **até 3 vezes** durante o jogo:

- **Pular Pergunta**  
  Ignora a pergunta atual sem penalidade.

- **Ajuda da Plateia**  
  Simula votos do público com maior probabilidade de acerto.

- **Ajuda dos Universitários**  
  Três votos com alta chance da alternativa correta.

- **Ajuda das Cartas**  
  Elimina duas alternativas incorretas aleatoriamente.

---

## 🗂 Estrutura de Dados

### Estrutura `Pergunta`

```c
struct pergunta {
    char nivel;
    char descricao[200];
    char alt[4][30];
    char alt_correta;
};
