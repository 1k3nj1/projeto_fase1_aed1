
# Pokemon Fila emulator (mudar isso aqui)

Um mini jogo simulador de batalhas Pokemon 5 vs 5 


## Para executar o jogo (melhorar depois)

Em ambiente linux, instale e configure o SFML 3. Após isso, basta utilizar o comando

```bash
  make run
```

para compilar e executar o jogo.


### Funcionalidades


#### Estrutura Fila

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

#### Gerenciamento dos estados do jogo

Foi utilizada uma classe enum Estado para controlar o progresso dos estados do jogo. Os estados do jogo são os seguintes:

| Estado | Descrição |
| --- | --- |
| TELA_INICIAL | Primeira tela do jogo | 
| MENU | Estado onde o jogador aperta o botão `Play` | 
| VER_TIME_PC | Jogador vê o time do computador até apertar o botão de continuar | 
| ESCOLHA | Jogador escolhe os Pokemons do seu time | 
| BATALHA | Pokemons do jogador batalham com os Pokemons do computador | 
| TELA_FINAL | Tela que exibe o resultado final da batalha |
