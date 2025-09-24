# Primeira etapa: 'builder'
# Usa a imagem oficial do GCC para compilação.
FROM gcc:latest AS builder

# Define o diretório de trabalho dentro do contêiner.
WORKDIR /app

# Copia todos os arquivos do seu projeto para o contêiner.
COPY . .

# Executa o Makefile para compilar o programa.
RUN make

# Segunda etapa: 'final'
# Usa uma imagem Ubuntu para rodar o binário, garantindo a compatibilidade.
FROM ubuntu:latest

# Define o diretório de trabalho para a aplicação final.
WORKDIR /app

# Copia somente o binário compilado da etapa 'builder'.
COPY --from=builder /app/app /app/app

# Define o comando que será executado quando o contêiner iniciar.
CMD ["/app/app"]
