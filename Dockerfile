FROM ubuntu:22.04

RUN apt-get update && apt-get install -y g++ && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN g++ Langtons_ant.cpp -o Langtons_ant

CMD ["./Langtons_ant"]