
# Pokemon Fila simulator (mudar isso aqui)

Um mini jogo simulador de batalhas Pokemon 5 vs 5 


## Para executar o jogo (melhorar depois)

Em ambiente linux, instale e configure o SFML 3. Após isso, basta utilizar o comando

```bash
  make run
```

para compilar e executar o jogo.

## Regras básicas do jogo (melhorar depois)

- O jogador deverá escolher entre 5 Pokemons para compor seu time;
- O time escolhido pelo jogador lutará contra 5 Pokemons do computador, escolhidos aleatoriamente;
- Antes de escolher o seu time, o jogador poderá ver o time do computador pelo tempo que desejar;
- Nas balhas, a lógica dos enfrentamentos é a seguinte:
  - O n-ésimo Pokemon o jogador, enfrenta o n-ésimo Pokemon do computador, até que todos os Pokemons tenha batalhado exatamente 1 vez;
  - Para determinar o vencerdor, se utiliza a lógica de superefetividade dos tipos dos Pokemons:
    - PLANTA vence ÁGUA;
    - ÁGUA vence FOGO;
    - FOGO vence PLANTA;
  - Cada vitória adiciona 1 ponto ao time do Pokemon vencedor, e em caso de empate ou derrota, 0 pontos são adicionados;
- Vence o time que tiver mais pontos. Há a possibilidade do empate.


## Estruturação do projeto

O projeto possui três divisões de diretórios principais:

| Diretório | Descrição |
| --- | --- |
| **src** | Arquivos relacionados à lógica do jogo e à estrutura de dados |
| **imagens** | Contém todas as imagens utilizadas no projeto |
| **Raiz** | Contém arquivo main e instruções de execução |

### Arquivos no diretório src

| Arquivo | Descrição |
| --- | --- |
| `arial.ttf` | Fonte utilizada nos textos |
| `EFINITIONS.hpp` | Definições utilizadas para as imagens e tamanhos das filas |
| `Fila.hpp` / `Fila.cpp` | Definições e implementações da fila |
| `PokemonEntity.hpp` / `PokemonEntity.cpp` | Definições e implementações do PokemonEntity, usado como Node na fila |
| `funcs_jogo.hpp` / `funcs_jogo.cpp` | Definições e implementações de estruturas e funções utilizadas para a lógica do jogo |


## Funcionalidades


### Estrutura Fila

O jogo se baseia no uso de filas para o armazenamento temporários dos Pokemons, tanto do time do jogador quanto do time do computador.

A fila foi implementada como uma classe em arquivos dedicados, `Fila.h` e `Fila.cpp`, implementando as seguintes operações:

| Operação | O que realiza: |
|---|---|
| `enfileira(PokemonEntity p, bool *ok)` | Enfileira o Pokemon p; `ok` sinaliza o sucesso da operação |
| `desenfileira(PokemonEntity *p, bool *ok)` | Desenfileira o Pokemon em p; `ok` sinaliza o sucesso da operação |
| `cheia()` | retorna `true` se a fila estiver cheia, `false` caso contrário |
| `vazia()` | retorna `true` se a fila estiver vazia, `false` caso contrário |
| `get_tamanho()` | retorna o tamanho atual da fila |
| `pegaPrimeiro(PokemonEntity &p)` | retorna o primeiro Pokemon da fila em p, sem removê-lo |

### Gerenciamento dos estados do jogo

Foi utilizada uma classe enum Estado para controlar o progresso dos estados do jogo. Os estados do jogo são os seguintes:

| Estado | Descrição |
| --- | --- |
| TELA_INICIAL | Primeira tela do jogo | 
| MENU | Estado onde o jogador aperta o botão `Play` | 
| VER_TIME_PC | Jogador vê o time do computador até apertar o botão de continuar | 
| ESCOLHA | Jogador escolhe os Pokemons do seu time | 
| BATALHA | Pokemons do jogador batalham com os Pokemons do computador | 
| TELA_FINAL | Tela que exibe o resultado final da batalha |
