# Primeira etapa: 'builder'
FROM gcc:latest AS builder
WORKDIR /app
COPY . .
RUN make

# Segunda etapa: 'final'
FROM alpine:latest
WORKDIR /app
# Copia o executável 'app' da raiz do diretório do builder
COPY --from=builder /app/app /app/app

# Comando a ser executado quando o contêiner iniciar
CMD ["/app/app"]
