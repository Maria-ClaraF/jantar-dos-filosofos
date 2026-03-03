#!/bin/bash

# Compila o projeto usando o Makefile
echo "Compilando o projeto..."
make

echo "------------------------------------------------"
echo "Iniciando teste de 10 segundos com 5 filósofos..."
echo "------------------------------------------------"

# Executa o programa corrigido por 10 segundos e salva a saída em um log
# O comando 'timeout' encerra o programa após o tempo definido
time timeout 10s ./corrigido 5 > teste_resultado.txt

echo "Teste concluído!"
echo "A saída dos filósofos foi salva em: teste_resultado.txt"
echo "O tempo de execução acima (real, user, sys) deve ser usado no relatório."

