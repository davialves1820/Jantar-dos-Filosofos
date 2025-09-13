# 📌 Projeto Final – Sistemas Operacionais (2025.1)

## 👥 Integrantes
- Davi Alves Rodrigues
- Ryan Caetano Cesar de Araújo
- Larissa de Carvalho Donato

---

## 📖 Descrição do Projeto
Este repositório contém a implementação do projeto final da disciplina de **Sistemas Operacionais**.  
O objetivo é aplicar na prática os conceitos vistos em sala de aula, por meio do desenvolvimento de um projeto em **C no Linux**.  

O problema escolhido para o projeto foi o The Dining-Philosophers Problem( Jantar dos Filósofos):

O Jantar dos Filósofos, proposto por Edsger W. Dijkstra em 1965, é um problema clássico de sincronização em sistemas operacionais. Ele descreve cinco filósofos sentados em uma mesa circular que alternam entre pensar e comer, precisando de dois hashis (um à esquerda e outro à direita) para se alimentar.

O desafio está em evitar problemas de deadlock (quando todos pegam um hashi e ficam bloqueados esperando o outro, sem progresso) e starvation (quando um filósofo tenta repetidamente pegar os hashis mas nunca consegue comer).

O objetivo do problema é projetar algoritmos que coordenem o uso dos recursos compartilhados (hashis), garantindo que todos os filósofos possam eventualmente comer, sem impasse nem inanição.

Durante a apresentação final, será feita uma **demonstração prática** do funcionamento do sistema, bem como uma **análise de desempenho** comparando diferentes casos de uso.

---

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
- Arquivo **Makefile**: Árquivo com as instruções para compilação do projeto.

## ⚙️ Como Compilar e Executar

Clone o repositório e acesse a pasta do projeto:
```bash
git clone https://github.com/davialves1820/Trabalho-SO.git
cd Trabalho-SO
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

## 📊 Avaliação de Desempenho
Para a avaliação de desempenho serão comparadas os seguintes parâmetros para cada execução:
- Tempo de espera individual para pegar permissão do garçom: quanto tempo cada filósofo teve que esperar antes de conseguir acesso ao recurso compartilhado, ou seja, antes de começar a pegar os garfos e comer;
- Número de bloqueios: sinaliza quantas vezes uma thread (filósofo) tentou acessar um recurso crítico (como garfos ou semáforos) e teve que esperar porque o recurso estava ocupado;
- Tempo total da execução do programa.

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
