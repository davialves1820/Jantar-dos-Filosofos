# Primeira etapa: 'builder'
# Usa a imagem oficial do GCC, que contém as ferramentas necessárias para compilar o código C.
FROM gcc:latest AS builder

# Define o diretório de trabalho dentro do contêiner.
WORKDIR /app

# Copia todos os arquivos do diretório atual para o diretório /app no contêiner.
# A imagem que você carregou mostra que o código-fonte está em 'src' e os headers em 'include'.
# O 'Makefile' também está no diretório raiz.
COPY . .

# Compila o programa usando o Makefile.
# Isso é mais robusto e reproduzível do que usar 'gcc' diretamente,
# especialmente para projetos maiores com múltiplas fontes e dependências.
RUN make

# Segunda etapa: 'final'
# Usa a imagem 'alpine', que é uma distribuição Linux minimalista e muito leve, ideal para imagens finais.
FROM alpine:latest

# Define o diretório de trabalho para a imagem final.
WORKDIR /app

# Copia somente o executável 'app' compilado da etapa 'builder' para a imagem final.
# O 'app' foi criado na etapa 'builder' quando você executou o comando 'make'.
# É por isso que você não precisa de bibliotecas de desenvolvimento aqui.
COPY --from=builder /app/app /app/app

# Comando a ser executado quando o contêiner iniciar.
CMD ["/app/app"]
