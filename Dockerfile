FROM gcc:latest AS builder

WORKDIR /app

COPY . .

FROM alpine:latest

WORKDIR /app

CMD ["/app/app"]