import pyodbc

def conecta():
    server = "localhost"
    database = "tdd"
    port=3306
    username = "root"
    password = ""
    driver = "{MySQL ODBC 9.2 ANSI Driver}"
    
    conexao = pyodbc.connect(f'DRIVER={driver};SERVER={server};PORT={port};DATABASE={database};UID={username};PWD={password}')
    cursor = conexao.cursor()
    
    return conexao, cursor


def desconecta(conexao):
    conexao.close()