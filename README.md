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
- **Linguagens:** C 
- **Sistema Operacional:** Linux (Recomendado: Ambiente WSL ou nativo basedo em Debian/Ubuntu)
- **Ferramentas adicionais:** Makefile, GitHub, Docker (opcional)  

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


---

## 📊 Avaliação de Desempenho
Para a avaliação de desempenho serão comparadas os seguintes parâmetros para cada execução:
- Tempo de espera individual para pegar permissão do garçom;
- Número de bloqueios;
- Tempo total da execução do programa.

---

## 🖼️ Demonstração

---

## 📌 Divisão de Tarefas
