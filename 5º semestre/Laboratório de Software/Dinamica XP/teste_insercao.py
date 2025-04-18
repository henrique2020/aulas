import unittest
from database import conecta, desconecta
from datetime import date

class TesteBanco(unittest.TestCase):

    def setUp(self):
        self.conn, self.cursor = conecta()
        self.assertIsNotNone(self.conn, "Conexão falhou")
        self.conn.autocommit = False

    def tearDown(self):
        self.conn.rollback()
        desconecta(self.conn)

    def test_insercao_cliente_e_pagamento(self):
        # Inserir cliente fictício
        self.cursor.execute("""
            INSERT INTO clientes (id, cpf, data_nascimento, telefone, nome)
            VALUES (999999, '12345678901', '1990-01-01', '11999999999', 'Cliente Teste')
        """)

        # Inserir pagamento para o cliente
        self.cursor.execute("""
            INSERT INTO pagamento (id_cliente, data_compra, parcelas, valor_compra, pago)
            VALUES (999999, '2025-04-10', 3, 150.00, 0)
        """)

        # Verificar se o cliente está no banco
        self.cursor.execute("SELECT * FROM clientes WHERE id = 999999")
        cliente = self.cursor.fetchone()
        self.assertIsNotNone(cliente)
        self.assertEqual(cliente[4], 'Cliente Teste')

        # Verificar se o pagamento foi registrado
        self.cursor.execute("SELECT * FROM pagamento WHERE id_cliente = 999999")
        pagamento = self.cursor.fetchone()
        self.assertIsNotNone(pagamento)
        self.assertEqual(float(pagamento[3]), 150.00)

if __name__ == '__main__':
    unittest.main(verbosity=2)
