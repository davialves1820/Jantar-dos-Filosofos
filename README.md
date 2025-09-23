# 📌 Projeto Final – Sistemas Operacionais (2025.1)

## 👥 Integrantes

- Davi Alves Rodrigues
- Ryan Caetano Cesar de Araújo
- Larissa de Carvalho Donato

---

## 📖 Descrição do Projeto

Este repositório contém a implementação do projeto final da disciplina de **Sistemas Operacionais**.

Proposto por Edsger W. Dijkstra em 1965, o Jantar dos Filósofos é um problema clássico de sincronização em sistemas operacionais.
Ele descreve cinco filósofos sentados ao redor de uma mesa circular que alternam entre pensar e comer, necessitando de dois hashis (um à esquerda e outro à direita) para se alimentar.

O principal desafio é evitar condições de deadlock (quando todos pegam um hashi e ficam bloqueados esperando o outro) e starvation (quando um filósofo nunca consegue acesso aos dois hashis para comer).

O objetivo da solução é projetar algoritmos que coordenem o acesso a recursos compartilhados, garantindo que todos os filósofos possam eventualmente comer, sem impasses nem inanição.
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## 🛠️ Tecnologias Utilizadas

- **Linguagens:** C;
- **Sistema Operacional:** Linux (Ubuntu);
- **Ferramentas adicionais:** Makefile, GitHub, Docker.

### Link Dockerhub

https://hub.docker.com/r/davialves1820/jantar_filosofos

---

## 🗂️ Organização

- Pasta **src**: Contém os arquivos-fonte(.c);
- Pasta **include**: Contém os cabeçalho dos arquivos (.h);
- Pasta **build**: Contém os arquivos binários (.o) gerados durante a compilação;
- Arquivo **app**: Arquivo executável.
- Arquivo **Makefile**: Arquivo com as instruções para compilação do projeto.

## ⚙️ Como Compilar e Executar

Clone o repositório e acesse a pasta do projeto:

```bash
git clone https://github.com/davialves1820/Jantar-dos-Filosofos.git
cd Jantar-dos-Filosofos
```

### Compilação

```bash
make
```

### Execução

```bash
./app
```

---

## 💻 Instruções de Uso

Ao iniciar, o programa exibirá um menu para que você escolha qual solução do problema dos filósofos deseja executar:

```bash
1- DEADLOCK
2- MONITOR
3- SEMAFORO
4- SEMAFORO COM CONTROLE
0- SAIR
Opcao:
```

Digite o número correspondente à solução desejada e pressione <kbd>Enter</kbd>.

### Observação:

- **Opções 2, 3 e 4** rodarão até o fim e exibirão as métricas de desempenho.
- **Opção 1 (Deadlock)** foi projetada para travar. Após os filósofos pegarem o primeiro garfo, a simulação irá parar, e você precisará encerrá-la manualmente com <kbd>Ctrl</kbd>+<kbd>C</kbd>.

---

# 📊 Avaliação de Desempenho

## Para a avaliação de desempenho serão comparadas os seguintes parâmetros para cada execução:

- Tempo de espera individual para pegar permissão do garçom: quanto tempo cada filósofo teve que esperar antes de conseguir acesso ao recurso compartilhado, ou seja, antes de começar a pegar os garfos e comer;
- Número de bloqueios: sinaliza quantas vezes uma thread (filósofo) tentou acessar um recurso crítico (como garfos ou semáforos) e teve que esperar porque o recurso estava ocupado;
- Tempo total da execução do programa.

## Foram testadas três abordagens diferentes:

### 1. Solução com Monitor
**Princípio:** Utiliza um monitor baseado em `pthread_mutex_t` e `pthread_cond_t` para controlar o acesso aos garfos e evitar condições de corrida.

**Funcionamento:**
- Cada filósofo tem um estado: **PENSANDO**, **FAMINTO** ou **COMENDO**.
- Quando um filósofo fica faminto, ele entra em uma seção crítica protegida pelo mutex do monitor.
- A função `teste()` verifica se os filósofos vizinhos estão comendo; caso contrário, permite que o filósofo faminto coma.
- Enquanto não for possível comer, o filósofo fica bloqueado em uma condição (`pthread_cond_wait`) até ser sinalizado que pode pegar os garfos.
- Após comer, o filósofo devolve os garfos, muda seu estado para PENSANDO e sinaliza os vizinhos para que possam comer.

**Vantagem:** Garante exclusão mútua e evita deadlocks usando um monitor centralizado.

---

### 2. Solução com Semáforo (Garçom)
**Princípio:** Usa um semáforo (`sem_t garcom`) para limitar a quantidade de filósofos que podem tentar comer simultaneamente.

**Funcionamento:**
- O semáforo é inicializado com `TAM-1`, garantindo que no máximo `TAM-1` filósofos possam tentar pegar garfos ao mesmo tempo.
- Antes de pegar os garfos, cada filósofo faz `sem_wait(&garcom)` para pedir permissão ao garçom.
- Após pegar os garfos e comer, o filósofo faz `sem_post(&garcom)` para liberar a vaga no semáforo.
- O acesso a cada garfo ainda é controlado por mutexes individuais para garantir exclusão mútua.

**Vantagem:** Evita deadlocks de forma simples, permitindo que sempre haja pelo menos um filósofo que consiga pegar os dois garfos.

---

### 3. Solução com Semáforo e Controle de Ordem
**Princípio:** Combina o semáforo do garçom com uma estratégia de controle de ordem para pegar garfos, evitando deadlocks e starvation.

**Funcionamento:**
- O semáforo é inicializado com `TAM-1`, como na solução anterior.
- Os filósofos pares pegam primeiro o garfo da esquerda, depois o da direita; os ímpares fazem o inverso.
- Essa alternância na ordem de pegar os garfos quebra ciclos de espera circular, prevenindo deadlocks.
- Após comer, os filósofos devolvem os garfos na ordem inversa e liberam o semáforo do garçom.

**Vantagem:** Reduz ainda mais o risco de starvation em comparação com a solução apenas com semáforo.


**Observação:** Além disso, também foi considerado o **caso padrão**, no qual ocorre *deadlock*.
Foram considerados os resultados médios das soluções para a comparação dos resultados.
Foi considerado um tempo de execução de 15 segundos para todas as soluções.

---

## 📌 Resultados Individuais

### Solução Monitor

- **Filósofos comendo:** Todos comeram 4 vezes, exceto o Filósofo 3, que comeu apenas 1 vez.
- **Espera média:** Variou de 0.75s a 12.02s.
- **Starvation:** Sim (Filósofo 3).
- **Bloqueios totais:** 15
- **Tempo médio de espera por refeição:** 3.40s

**Observação:** A espera alta e o número reduzido de refeições do Filósofo 3 indicam possível *starvation*.

---

### Solução Semáforo

- **Refeições bem distribuídas:** Variação entre 3 e 4 por filósofo.
- **Espera média:** De 1.28s a 2.60s.
- **Starvation:** Não ocorreu.
- **Bloqueios totais:** 7
- **Tempo médio de espera por refeição:** 1.95s

Melhor distribuição de recursos e ausência de starvation.

---

### Solução Semáforo com Controle

- **Refeições:** Igual à solução anterior (17 totais).
- **Espera média:** De 0.77s a 2.69s.
- **Starvation:** Não ocorreu.
- **Bloqueios totais:** 7
- **Tempo médio de espera por refeição:** 1.97s

Distribuição justa com pequeno controle adicional, mantendo desempenho semelhante ao semáforo puro.

---

## 📄Comparativo Geral

| Métrica                       | Monitor        | Semáforo       | Semáforo com Controle |
|------------------------------|----------------|----------------|------------------------|
| Total de Refeições           | 17             | 17             | 17                     |
| Starvation                   | 1              | 0              | 0                      |
| Bloqueios Totais             | 15             | 7              | 7                      |
| Tempo Médio de Espera        | 3.40 s         | 1.95 s         | 1.97 s                 |
| Desbalanceamento de Refeições| Alto (1 refeição) | Baixo         | Baixo                  |

---

## Observações Finais

- O **caso padrão** levar a *deadlock*, onde todos os filósofos pegam um talher e ficam esperando indefinidamente pelo segundo.
- A **solução com monitor** apresentou maior número de bloqueios e evidência de starvation.
- As **soluções com semáforos**, especialmente com controle, proporcionam uma melhor distribuição de recursos, evitando starvation e deadlocks, com tempos de espera menores e mais uniformes.

---

## 🖼️ Demonstração

---

## 📝 Divisão de Tarefas

| Atividade                                                     | Responsável                                     |
|---------------------------------------------------------------|-------------------------------------------------|
| Pesquisa teórica sobre o problema do Jantar dos Filósofos     | Davi Alves, Ryan Caetano e Larissa de Carvalho |
| Implementação do caso do deadlock     | Davi Alves, Ryan Caetano e Larissa de Carvalho |
| Implementação da solução do  semáfaro     | Davi Alves, Ryan Caetano e Larissa de Carvalho |
| Implementaçaõ da solução do monitor     | Davi Alves, Ryan Caetano e Larissa de Carvalho |
| Criação do Makefile e estrutura de pastas do projeto     | Davi Alves |
| Desenvolvimento dos arquivos `.c` e `.h`     | Davi Alves, Ryan Caetano e Larissa de Carvalho |
| Adição dos parâmetros para comparação de desempenho     | Davi Alves e Larissa de Carvalho |
| Testes e análise de desempenho     | Davi Alves, Ryan Caetano e Larissa de Carvalho |
| Documentação do projeto (README e comentários no código)     | Davi Alves, Ryan Caetano e Larissa de Carvalho |
| Github action/ Docker     | Davi Alves |

