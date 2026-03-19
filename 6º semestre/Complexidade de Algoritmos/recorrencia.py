def count_ways_fence(n, k):
    """
    Calcula o número de formas de pintar n tábuas com k cores
    usando uma abordagem bottom-up (Programação Dinâmica).
    
    Recorrência: dp[i] = (dp[i-1] + dp[i-2]) * (k - 1)
    """
    
    # Casos triviais
    if n <= 0:
        return 0
    if k <= 0:
        return 0
        
    # --- Casos-Base ---
    if n == 1:
        # countWays(1, k) = k
        return k
        
    if n == 2:
        # countWays(2, k) = k * k
        return k * k

    # --- Abordagem Bottom-Up (Otimizada) ---
    
    # Inicializa os dois valores anteriores com os casos-base
    # Representa dp[i-2], que começa em n=1
    prev_2 = k
    # Representa dp[i-1], que começa em n=2
    prev_1 = k * k
    
    # Itera de 3 até n
    for i in range(3, n + 1):
        # Aplica a recorrência:
        # current = (prev_1 + prev_2) * (k - 1)
        
        # Em Python, os inteiros têm precisão arbitrária,
        # então não precisamos nos preocupar com overflow.
        current = (prev_1 + prev_2) * (k - 1)
        
        # Atualiza os valores anteriores para a próxima iteração
        prev_2 = prev_1
        prev_1 = current
        
    # O resultado final é o último valor calculado
    return prev_1

# --- Exemplo de Uso ---
n_tabuas = 4
k_cores = 3

# n=1: 3
# n=2: 9
# n=3: (9 + 3) * (2) = 24
# n=4: (24 + 9) * (2) = 66

resultado = count_ways_fence(n_tabuas, k_cores)
print(f"Para {n_tabuas} tábuas e {k_cores} cores, existem {resultado} formas.") 

# Exemplo 2
# n=3, k=2
# n=1: 2
# n=2: 4
# n=3: (4 + 2) * (1) = 6
resultado_2 = count_ways_fence(1000, 100)
print(f"Para 3 tábuas e 2 cores, existem {resultado_2} formas.")