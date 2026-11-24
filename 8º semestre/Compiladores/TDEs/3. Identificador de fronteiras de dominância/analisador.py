import os
import sys

def calcular_fronteiras(n_nodos, pred):
    """
    Recebe o número de nodos e a lista de predecessores.
    Calcula os dominadores, idom e retorna a Fronteira de Dominância (FD).
    """
    # 1. Cálculo dos Dominadores (Algoritmo Iterativo)
    todos_nodos = set(range(1, n_nodos + 1))
    dom = [set(todos_nodos) for _ in range(n_nodos + 1)]
    dom[1] = {1}
    dom[0] = set() # Índice 0 não utilizado no grafo

    mudou = True
    while mudou:
        mudou = False
        for i in range(2, n_nodos + 1):
            if not pred[i]:
                novo_dom = {i}
            else:
                intersecao = set(todos_nodos)
                for p in pred[i]:
                    intersecao = intersecao.intersection(dom[p])
                novo_dom = {i}.union(intersecao)

            if novo_dom != dom[i]:
                dom[i] = novo_dom
                mudou = True

    # 2. Determinação do Dominador Imediato (idom)
    idom = [0] * (n_nodos + 1)
    for i in range(2, n_nodos + 1):
        sdom = dom[i] - {i}
        if sdom:
            # Pega o dominador estrito que está "mais abaixo" (maior len)
            idom[i] = max(sdom, key=lambda x: len(dom[x]))

    # 3. Lógica para Fronteira de Dominância (FD)
    FD = [set() for _ in range(n_nodos + 1)]
    
    for b in range(1, n_nodos + 1):
        if len(pred[b]) >= 2:
            for p in pred[b]:
                runner = p
                # Proteção 'runner != 0' adicionada caso atinja a raiz
                while runner != idom[b] and runner != 0:
                    FD[runner].add(b)
                    runner = idom[runner]
                    
    return FD    


if __name__ == "__main__":
    # Verifica a quantidade de parâmetros passados
    # sys.argv[0] é o próprio nome do script
    if len(sys.argv) == 1:
        entrada = "grafo.txt"
        saida = "saida.txt"
    elif len(sys.argv) == 3:
        entrada = sys.argv[1]
        saida = sys.argv[2]
    else:
        print("Esperava-se nenhum ou dois parâmetros")
        print("\tpython analisador.py")
        print("\tpython analisador.py <arquivo_entrada> <arquivo_saida>")
        sys.exit(1)
    
    #Valida se o arquivo de entrada existe e se não está vazio
    if not os.path.exists(entrada):
        print(f"Erro: O arquivo '{entrada}' não foi encontrado.")
        sys.exit(1)
        
    with open(entrada, 'r') as f:
            linhas = [linha.strip() for linha in f if linha.strip()]
    
    if not linhas:
        print(f"Arquivo '{entrada}' está vazio.")
        sys.exit(1)

    # Processa a entrada e gera a saída
    n_nodos = int(linhas[0].strip())    # Primeira linha: número de nodos
    pred = [[] for _ in range(n_nodos + 1)]
    for i in range(2, n_nodos + 1):     # A partir da 2ª linha, preenche do nodo 2 em diante
        idx_linha = i - 1
        if idx_linha < len(linhas) and linhas[idx_linha].strip():
            partes = linhas[idx_linha].strip().split()
            pred[i] = [int(x) for x in partes]

    # Processa a entrada e gera a saída
    FD = calcular_fronteiras(n_nodos, pred)
    with open(saida, 'w') as f:
        for i in range(1, n_nodos + 1):
            nodos_ordenados = sorted(list(FD[i]))
            str_nodos = " ".join(map(str, nodos_ordenados))
            f.write(f"{i}: {str_nodos}\n")