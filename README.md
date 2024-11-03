# Analisando Jogos de Civilizações Antigas - Solução com Programação Dinâmica

## Descrição Geral
Este projeto implementa uma solução otimizada utilizando programação dinâmica para resolver o problema de equilibrar as somas das partes superior e inferior de um conjunto de placas, possivelmente descartando uma placa. A solução transforma o problema em uma variação do **Subset Sum Problem**, buscando um subconjunto de placas cuja soma das diferenças permita equilibrar as somas. Para otimizar o espaço de estado, utiliza-se um `unordered_map`, permitindo lidar com até 400 placas de forma eficiente.

## Integrantes da Dupla

- Vitor
- Luiz

## Compilação e Execução

### Pré-requisitos

- Compilador C++ (suporta C++11 ou superior)
- Sistema operacional compatível com o compilador (Windows, Linux, macOS)

### Compilação

Abra o terminal na pasta onde estão os arquivos e execute:

```bash
g++ -std=c++11 -o sol_1 sol_1.cpp
```

### Execução

Após a compilação, execute:

```bash
./sol_1 < test_cases/entrada
```

Substitua entrada pelo arquivo que contém os casos de teste de entrada.