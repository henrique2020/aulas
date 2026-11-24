import os
import sys

def tradutor(linhas:list) -> list:
    '''
    Traduz o código de três endereços (C3E) para uma estrutura do grafo de fluxo de controle (CFG)
    '''

    mapa_labels = {linha[:-1]: i for i, linha in enumerate(linhas) if linha.endswith(':')}
    
    # 1. Identificação de líderes
    lideres = [False] * len(linhas)
    lideres[0] = True 

    def extrair_alvo(instrucao):
        for kw in ["goto", "gofalse", "gotrue", "if"]:
            if kw in instrucao:
                return instrucao.split(kw)[-1].strip().rstrip(';')
        return None

    for i, inst in enumerate(linhas):
        if inst.endswith(':'):
            lideres[i] = True 
            
        alvo = extrair_alvo(inst)
        if alvo in mapa_labels:
            lideres[mapa_labels[alvo]] = True 
            if i + 1 < len(linhas):
                lideres[i + 1] = True 

    # 2. Construção dos blocos básicos
    blocos = []
    bloco_atual = None
    linha_para_bloco = {}

    for i, inst in enumerate(linhas):
        if lideres[i] or bloco_atual is None:
            if bloco_atual:
                blocos.append(bloco_atual)
            bloco_atual = {'id': len(blocos) + 1, 'instrucoes': [], 'sucessores': []}
            
        bloco_atual['instrucoes'].append(inst)
        linha_para_bloco[i] = bloco_atual['id']
        
    if bloco_atual:
        blocos.append(bloco_atual)

    # 3. Mapeamento de sucessores e Substituição de Labels
    for b, bloco in enumerate(blocos):
        ultima_inst = bloco['instrucoes'][-1]
        condicional = any(kw in ultima_inst for kw in ["if", "gofalse", "gotrue"])
        alvo = extrair_alvo(ultima_inst)

        # Desvio (alvo) primeiro
        if alvo in mapa_labels:
            bloco['sucessores'].append(linha_para_bloco[mapa_labels[alvo]])

        # Fluxo natural (fallthrough) em seguida
        if (condicional or not alvo) and b + 1 < len(blocos):
            bloco['sucessores'].append(blocos[b + 1]['id'])

        # Substituição dos labels nas instruções
        instrucoes_limpas = []
        for inst in bloco['instrucoes']:
            if inst.endswith(':'):
                continue
                
            alvo_inst = extrair_alvo(inst)
            if alvo_inst in mapa_labels:
                id_destino = linha_para_bloco[mapa_labels[alvo_inst]]
                inst = inst.replace(alvo_inst, f"bb{id_destino}")
                
            instrucoes_limpas.append(inst)
            
        bloco['instrucoes'] = instrucoes_limpas

    return blocos
    

if __name__ == "__main__":
    # Verifica a quantidade de parâmetros passados
    # sys.argv[0] é o próprio nome do script
    if len(sys.argv) == 1:
        entrada = "entrada.cod"
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
    cfg = tradutor(linhas)
    with open(saida, 'w') as f:
        for bloco in cfg:
            succs_unicos = list(dict.fromkeys(bloco['sucessores']))
            succs_str = " ".join(str(s) for s in succs_unicos)
            f.write(f"Bloco {bloco['id']}: succs {{ {succs_str} }}\n")
        
        f.write("\n")
            
        for bloco in cfg:
            f.write(f"<bb {bloco['id']}>:\n")
            for inst in bloco['instrucoes']:
                f.write(f"{inst}\n")