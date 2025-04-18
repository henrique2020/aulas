import os
from database import conecta, desconecta

def recuperaClientes():
    conexao, cursor = conecta()
    cursor.execute('SELECT id, cpf, data_nascimento, telefone, nome FROM clientes')
    
    clientes = {}
    for linha in cursor.fetchall():
        clientes[linha.id] = {
            "cpf": linha.cpf,
            "data_nascimento": linha.data_nascimento,
            "telefone": linha.telefone,
            "nome": linha.nome,
            "compras": []
        }

    desconecta(conexao)
    return clientes
    
def recuperaPagamentos(dados):
    conexao, cursor = conecta()
    cursor.execute('SELECT id_cliente, data_compra, parcelas, valor_compra, pago FROM pagamento')
    
    for linha in cursor.fetchall():
        if(not linha.id_cliente in dados.keys()):
            print(f"Usuário de ID {linha.id_cliente} não encontrado na tabela clientes")
            return
            
        dados[linha.id_cliente]['compras'].append(
            {
                "data_compra": linha.data_compra,
                "parcelas": linha.parcelas,
                "valor_compra": linha.valor_compra,
                "pago": linha.pago
            }
        )

    desconecta(conexao)
    return dados
    
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

if __name__ == '__main__':
    # Importa os dados
    dados = recuperaClientes()
    dados = recuperaPagamentos(dados)

    # Exibe as informações
    exibeRelatorioGeral(dados)
    exibeRelatorioFluxoDeCaixa(dados)
    exibeRelatorioPendencias(dados)

    # Gera o relatório
    geraRelatorio(fr'{os.getcwd()}\arquivos\relatorio.csv', dados)