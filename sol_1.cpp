/*
    Título: Analisando Jogos de Civilizações Antigas - Solução Otimizada com Programação Dinâmica
    Descrição: Implementação de um algoritmo eficiente utilizando programação dinâmica para resolver o problema de equilibrar as somas das partes superior e inferior das placas, possivelmente descartando uma placa.
    Integrantes da dupla:
    - Vitor
    - Luiz

    A solução transforma o problema em uma variação do Subset Sum Problem, buscando um subconjunto de placas cuja soma das diferenças permita equilibrar as somas. Utiliza-se uma abordagem otimizada que reduz significativamente o espaço de estado utilizando um mapa não ordenado (unordered_map) ao invés de um vetor fixo, tornando possível lidar com N até 400 de forma eficiente.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Placa
{
    int x, y;
    int index;
};

// Função para tentar equilibrar as somas sem descartar nenhuma placa
bool tentaEquilibrar(const vector<Placa> &placas, int &somaTotal, vector<bool> &orientacao)
{
    int N = placas.size();
    int somaX = 0, somaY = 0;
    vector<int> delta(N);

    // Calcula as somas totais e as diferenças individuais
    for (int i = 0; i < N; ++i)
    {
        somaX += placas[i].x;
        somaY += placas[i].y;
        delta[i] = placas[i].y - placas[i].x;
    }

    int diff = somaY - somaX;

    // Se a diferença não for par, não é possível equilibrar
    if (diff % 2 != 0)
        return false;

    int target = diff / 2;

    // Utiliza um mapa não ordenado para armazenar os estados alcançáveis
    unordered_map<int, int> dp;
    dp[0] = -1; // Estado inicial

    // Programação dinâmica para encontrar um subconjunto cuja soma das diferenças seja igual ao alvo
    for (int i = 0; i < N; ++i)
    {
        unordered_map<int, int> dp_next = dp;
        for (const auto &entry : dp)
        {
            int s = entry.first;
            int s_new = s + delta[i];
            if (dp_next.find(s_new) == dp_next.end())
            {
                dp_next[s_new] = i;
            }
        }
        dp.swap(dp_next);
    }

    if (dp.find(target) != dp.end())
    {
        // Reconstrói a solução a partir do mapa de estados
        vector<bool> flip(N, false);
        int s = target;
        while (s != 0)
        {
            int idx = dp[s];
            flip[idx] = true;
            s -= delta[idx];
        }

        // Calcula a soma total e a orientação das placas
        somaTotal = 0;
        for (int i = 0; i < N; ++i)
        {
            if (flip[i])
            {
                somaTotal += placas[i].y;
                orientacao[i] = false; // Placa invertida
            }
            else
            {
                somaTotal += placas[i].x;
                orientacao[i] = true; // Orientação original
            }
        }

        return true;
    }

    return false;
}

int main()
{
    int N; // Número de placas

    while (cin >> N && N != 0)
    {
        vector<Placa> placas(N);

        // Leitura das placas
        for (int i = 0; i < N; ++i)
        {
            cin >> placas[i].x >> placas[i].y;
            placas[i].index = i;
        }

        int somaTotal = 0;
        vector<bool> orientacao(N, true); // Orientação das placas: true se não invertida, false se invertida
        bool encontrado = false;

        // Tenta equilibrar sem descartar nenhuma placa
        if (tentaEquilibrar(placas, somaTotal, orientacao))
        {
            encontrado = true;
            cout << somaTotal << " nenhuma placa descartada" << endl;
            continue;
        }

        // Se não for possível, tenta descartar uma placa
        int melhorSoma = -1;
        int menorA = 1001, menorB = 1001;

        for (int d = 0; d < N; ++d)
        {
            vector<Placa> placasSemUma = placas;
            placasSemUma.erase(placasSemUma.begin() + d);
            vector<bool> orientacaoAtual(N - 1, true);
            int somaAtual = 0;

            if (tentaEquilibrar(placasSemUma, somaAtual, orientacaoAtual))
            {
                if (somaAtual > melhorSoma)
                {
                    melhorSoma = somaAtual;
                    int a = min(placas[d].x, placas[d].y);
                    int b = max(placas[d].x, placas[d].y);
                    menorA = a;
                    menorB = b;
                }
                else if (somaAtual == melhorSoma)
                {
                    int a = min(placas[d].x, placas[d].y);
                    int b = max(placas[d].x, placas[d].y);
                    if (a < menorA || (a == menorA && b < menorB))
                    {
                        menorA = a;
                        menorB = b;
                    }
                }
                encontrado = true;
            }
        }

        if (encontrado)
        {
            cout << melhorSoma << " descartada a placa " << menorA << " " << menorB << endl;
        }
        else
        {
            cout << "impossível" << endl;
        }
    }

    return 0;
}
