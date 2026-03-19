import os
from time import time

DEBUG = False
TAMANHO = 3

# =====================================================
# Classe Puzzle-8
# =====================================================
class Puzzle8:
    
    movimentos = {
        '↑': (-1, 0),
        '↓': (1, 0),
        '←': (0, -1),
        '→': (0, 1)
    }

    objetivo = [
        [0, 1, 2],
        [3, 4, 5],
        [6, 7, 8]
    ]

    def __init__(self, inicio: list, limite: int):
        self.tabuleiro = inicio
        self.limite = limite

    def encontrar_zero(self, tabuleiro: list = None) -> list[int]:
        tabuleiro = tabuleiro or self.tabuleiro
        for i in range(TAMANHO):
            for j in range(TAMANHO):
                if tabuleiro[i][j] == 0:
                    return i, j

    def mover(self, tabuleiro: list, mov: str) -> list|None:
        i, j = self.encontrar_zero(tabuleiro)
        di, dj = Puzzle8.movimentos[mov]
        ni, nj = i + di, j + dj
        if 0 <= ni < TAMANHO and 0 <= nj < TAMANHO:
            novo = [linha[:] for linha in tabuleiro]
            novo[i][j], novo[ni][nj] = novo[ni][nj], novo[i][j]
            return novo
        return None

    def resolvido(self, tabuleiro: list = None) -> bool:
        return (tabuleiro or self.tabuleiro) == Puzzle8.objetivo

    def solucao(self, caminho: list) -> None:
        print(f"Solução encontrada em {len(caminho)} movimentos")
        print(f"Sequência de movimentos: {''.join(caminho)}")

        anterior = atual = [linha[:] for linha in self.tabuleiro]
        for mov in caminho:
            atual = self.mover(atual, mov)
            print(f'{anterior[0]}   {atual[0]}')
            print(f'{anterior[1]} {mov} {atual[1]}')
            print(f'{anterior[2]}   {atual[2]}')
            print()
            anterior = atual

    def erro_insoluvel(self, caminho: list) -> None:
        print("Não foi possível resolver esse Puzzle.", f"Foram realizados {len(caminho)}/{self.limite} movimentos.", sep = '\n')
    
    def erro_limite(self) -> None:
        print(f"Não foi possível resolver dentro do de {self.limite} movimentos.")


# =====================================================
# Classe Backtracking (DFS)
# =====================================================
class Backtracking:
    def __init__(self, puzzle: Puzzle8):
        self.puzzle = puzzle

    def resolver(self) -> None:
        caminho = self._dfs(self.puzzle.tabuleiro, set(), [], self.puzzle.limite)
        if caminho:
            self.puzzle.solucao(caminho)
        else:
            self.puzzle.erro_limite()

    def _dfs(self, tabuleiro: list, visitados: list, caminho: list, limite: int) -> list:
        if self.puzzle.resolvido(tabuleiro):
            return caminho
        if len(caminho) > limite:
            return None

        estado = tuple(num for linha in tabuleiro for num in linha)
        visitados.add(estado)

        for mov in Puzzle8.movimentos:
            if DEBUG: print(f'{len(caminho)}: {mov} {self.puzzle.encontrar_zero(tabuleiro)}')
            novo = self.puzzle.mover(tabuleiro, mov)
            if novo:
                novo_estado = tuple(num for linha in novo for num in linha)
                if novo_estado not in visitados:
                    resultado = self._dfs(novo, visitados, caminho + [mov], limite)
                    if resultado:
                        return resultado
                
        return None


# =====================================================
# Classe BFS
# =====================================================
class BFS:
    def __init__(self, puzzle: Puzzle8):
        self.puzzle = puzzle

    def resolver(self) -> None:
        fila = [(self.puzzle.tabuleiro, [])]
        visitados = {tuple(num for linha in self.puzzle.tabuleiro for num in linha)}

        while fila:
            tabuleiro, caminho = fila.pop(0)

            if self.puzzle.resolvido(tabuleiro):
                self.puzzle.solucao(caminho)
                return

            if len(caminho) >= self.puzzle.limite:
                continue

            for mov in Puzzle8.movimentos:
                if DEBUG: print(f'{len(caminho)}: {mov} {self.puzzle.encontrar_zero(tabuleiro)}')
                novo = self.puzzle.mover(tabuleiro, mov)
                if novo:
                    estado = tuple(num for linha in novo for num in linha)
                    if estado not in visitados:
                        visitados.add(estado)
                        fila.append((novo, caminho + [mov]))

        self.puzzle.erro_limite()


# =====================================================
# Funções auxiliares
# =====================================================
def clear() -> None:
    """Limpa o terminal"""
    os.system('cls' if os.name == 'nt' else 'clear')
    
def pegaMetodo() -> int:
    print("Escolha o método de resolução:")
    print("1 - Backtracking (DFS)")
    print("2 - Busca em Largura (BFS)")
    try:
        op = int(input("Opção: "))
        if 1 <= op <= 2:
            return op
    except:
        pass
    return pegaMetodo()

def pegaLinha() -> list:
    try:
        linha = list(map(int, input().split()))
        if len(linha) == TAMANHO:
            return linha
    except:
        pass
    return pegaLinha()

def pegaLimite() -> int:
    try:
        return int(input("Digite o número máximo de movimentos: "))
    except:
        return pegaLimite()

def continuar() -> bool:
    while True:
        op = input("Deseja continuar (S/N)? ").lower()
        if op in ('s', 'sim', 'y', 'yes'):
            return True
        elif op in ('n', 'nao', 'não', 'no'):
            return False


# =====================================================
# Função principal
# =====================================================
while True:
    metodo = pegaMetodo()
    clear()

    print(f"Digite o tabuleiro inicial ({TAMANHO} linhas com {TAMANHO} números separados por espaço):")
    inicio = [pegaLinha() for _ in range(TAMANHO)]
    clear()

    limite = pegaLimite()
    clear()

    print(
        f"| Método: {'Backtracking' if metodo == 1 else 'BFS'}",
        f"| Limite: {limite}",
        f"| Tabuleiro inicial: ",
        "".join([f'\t{linha}\n' for linha in inicio]),
        sep="\n"
    )

    puzzle = Puzzle8(inicio, limite)    
    if metodo == 1:
        resolvedor = Backtracking(puzzle)
    else:
        resolvedor = BFS(puzzle)

    ini = time()
    resolvedor.resolver()
    print(f"Tempo: {time() - ini:.2f}s")

    if not continuar():
        print("Saindo...")
        break
    
    clear()