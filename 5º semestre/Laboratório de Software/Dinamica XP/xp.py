import csv
import os

def formataData(data):
    if not data:
        return data
    
    data = data.zfill(8)
    return f"{data[4:8]}-{data[2:4]}-{data[0:2]}"

def verificaDados(linha):
    for pos in range(len(linha)):
        if not linha[pos] or linha[pos].isspace():
            linha[pos] = None
            
    return linha

def insereCliente(linha, dicionario):
    id_usuario, cpf, data_nascimento, telefone, cliente, _ = linha
    id_usuario = int(id_usuario)
    data_nascimento = formataData(data_nascimento)
    dicionario[id_usuario] = {
        "cpf": cpf,
        "data_nascimento": data_nascimento,
        "telefone": telefone,
        "nome": cliente,
        "compras": []
    }

def inserePagamento(linha, dicionario):
    id_usuario, data_compra, parcelas, valor_compra, pago, _ = linha
    id_usuario = int(id_usuario)
    data_compra = formataData(data_compra)
    parcelas = int(parcelas)
    valor_compra = float(valor_compra)
    pago = True if pago == 't' else False
    
    if(not id_usuario in dicionario.keys()):
        print(f"Usuário de ID {id_usuario} não encontrado na tabela clientes")
        return
        
    dicionario[id_usuario]['compras'].append(
        {
           "data_compra": data_compra,
           "parcelas": parcelas,
           "valor_compra": valor_compra,
           "pago": pago, 
        }
    )

def lerArquivo(arquivo, fnc, dicionario = None):
    if not dicionario: dicionario = {}
    
    with open(arquivo) as file:
        linhas = csv.reader(file, delimiter=';')
        next(linhas)    #Ignora o cabeçalho
        for linha in linhas:
            fnc(verificaDados(linha), dicionario)
    
    return dicionario

def geraRelatorio(arquivo, dados):
    file = open(arquivo, 'w')
    file.write("idCliente;cpfCliente;nomeCliente;valorPago;valorDevido\n");
    for id_usuario, dicionario in dados.items():
        valor_pago = 0
        valor_devido = 0
        for compra in dicionario['compras']:
            if compra['pago']:
                valor_pago += compra['valor_compra']
            else:
                valor_devido += compra['valor_compra']
               
        valor_pago = round(valor_pago, 2)
        valor_devido = round(valor_devido, 2)
        file.write(f"{id_usuario};{dicionario['cpf']};{dicionario['nome']};{valor_pago};{valor_devido}\n");
    file.close()

def exibeRelatorioGeral(dados):
    print("\n\n\n")
    print("Exibindo informações gerais")
    
    for id_usuario, dicionario in dados.items():
        print(f"ID {id_usuario:03d}")
        for k, v in dicionario.items():
            if not type(v) is list:
                print(f"{k.upper()}: {v.upper() if type(v) is str else v}")
            else:
                print(f"| {k.upper()}: ")
                for vl in v:
                    print(f"| | {vl}")
        print("-"*100)

def exibeRelatorioFluxoDeCaixa(dados):
    print("\n\n\n")
    print("Exibindo Fuxo de Caixa")
    
    lista = {}
    for cliente in dados.values():
        for compra in cliente['compras']:
            dtc = compra['data_compra']
            if not dtc in lista.keys():
                lista[dtc] = {'pago': 0, 'devido': 0}
            
            if compra['pago']:
                lista[dtc]['pago'] += compra['valor_compra']
            else:
                lista[dtc]['devido'] += compra['valor_compra']
    
    lista_ordenada = dict(sorted(lista.items()))    # Lista ordenada por chave (data)
    for k, v in lista_ordenada.items():
        print(f"{k} | {f"Recebido: R$ {v['pago']:.2f}":21} | {f"A receber: R$ {v['devido']:.2f}":21}")

def exibeRelatorioPendencias(dados):
    print("\n\n\n")
    print("Exibindo pendencias dos clientes")
    print(f"{"id":4} | {"CPF":11} | {"Nome":20} | {"Pago":13} | {"Devido":13}")
    print("-"*73)
    for id_usuario, dicionario in dados.items():
        valor_pago = 0
        valor_devido = 0
        for compra in dicionario['compras']:
            if compra['pago']:
                valor_pago += compra['valor_compra']
            else:
                valor_devido += compra['valor_compra']
        
        valor_pago = round(valor_pago, 2)
        valor_devido = round(valor_devido, 2)
        print(f"{id_usuario:4} | {dicionario['cpf'] if dicionario['cpf'] else '':11} | {dicionario['nome']:20} | R$ {valor_pago:10} | R$ {valor_devido:10}");


# Pega o caminho absoluto da pasta            
folder = fr'{os.getcwd()}\arquivos'

# Verifica se os arquivos existem
if not os.path.isfile(fr'{folder}\1428624292050_clientes.txt'):
    raise SystemExit("Arquivo de clientes não encontrado")

if not os.path.isfile(fr'{folder}\1428624292736_pagamentos.txt'):
    raise SystemExit("Arquivo de pagamentos não encontrado")

# Importa os arquivos
dados = lerArquivo(fr'{folder}\1428624292050_clientes.txt', insereCliente)
dados = lerArquivo(fr'{folder}\1428624292736_pagamentos.txt', inserePagamento, dados)

# Exibe as informações
exibeRelatorioGeral(dados)
exibeRelatorioFluxoDeCaixa(dados)
exibeRelatorioPendencias(dados)

# Gera o relatório
geraRelatorio(fr'{folder}\relatorio.csv', dados)