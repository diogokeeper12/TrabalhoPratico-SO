#!/bin/bash

# Comando 1
echo "Executando o comando 1..."
./bin/orchestrator SJF execute 5 -u ls


# Comando 2
echo "Executando o comando 2..."
./bin/orchestrator SJF execute 10 -u echo "Hello, world!"

echo "Executando o comando  5..."
./bin/orchestrator SJF execute 20 -u cat

# Comando 3
echo "Executando o comando 3..."
./bin/orchestrator SJF execute 8 -u sleep 3

#Comando 4
echo "Executando o comando 4..."
./bin/orchestrator SJF execute 10 -u ls -l


echo "Todos os comandos foram executados."