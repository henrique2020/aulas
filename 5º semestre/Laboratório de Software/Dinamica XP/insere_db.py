import csv
import os
from database import conecta, desconecta

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

def insereCliente(linha, cursor):
    id_usuario, cpf, data_nascimento, telefone, cliente, _ = linha
    id_usuario = int(id_usuario)
    data_nascimento = formataData(data_nascimento)
    
    conexao, cursor = conecta()
    cursor.execute("INSERT INTO clientes(id, cpf, data_nascimento, telefone, nome) VALUES (?, ?, ?, ?, ?)", id_usuario, cpf, data_nascimento, telefone, cliente)
    cursor.commit()

def inserePagamento(linha, cursor):
    id_usuario, data_compra, parcelas, valor_compra, pago, _ = linha
    id_usuario = int(id_usuario)
    data_compra = formataData(data_compra)
    parcelas = int(parcelas)
    valor_compra = float(valor_compra)
    pago = True if pago == 't' else False
    
    try:
        cursor.execute("INSERT INTO pagamento(id_cliente, data_compra, parcelas, valor_compra, pago) VALUES (?, ?, ?, ?, ?)", id_usuario, data_compra, parcelas, valor_compra, pago)
        cursor.commit()
    except Exception as e:
        print(e)

def lerArquivo(arquivo, fnc, cursor):
    with open(arquivo) as file:
        linhas = csv.reader(file, delimiter=';')
        next(linhas)    #Ignora o cabeçalho
        for linha in linhas:
            fnc(verificaDados(linha), cursor)


# Pega o caminho absoluto da pasta            
folder = fr'{os.getcwd()}\arquivos'

# Verifica se os arquivos existem
if not os.path.isfile(fr'{folder}\1428624292050_clientes.txt'):
    raise SystemExit("Arquivo de clientes não encontrado")

if not os.path.isfile(fr'{folder}\1428624292736_pagamentos.txt'):
    raise SystemExit("Arquivo de pagamentos não encontrado")

# Importa os arquivos
conexao, cursor = conecta()

print("Realizando inserção dos clientes...")
lerArquivo(fr'{folder}\1428624292050_clientes.txt', insereCliente, cursor)

print("Realizando inserção dos pagamentos...")
lerArquivo(fr'{folder}\1428624292736_pagamentos.txt', inserePagamento, cursor)

print("Tudo certo")

desconecta(conexao)