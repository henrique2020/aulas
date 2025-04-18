import unittest
from unittest.mock import patch
from leitor_db import (
    recuperaClientes,
    recuperaPagamentos,
    geraRelatorio,
    exibeRelatorioGeral,
    exibeRelatorioFluxoDeCaixa,
    exibeRelatorioPendencias
)
import os

class TestRelatorios(unittest.TestCase):

    def setUp(self):
        # Apenas carrega os dados existentes
        self.dados = recuperaPagamentos(recuperaClientes())

    def test_recuperaClientes(self):
        dados = recuperaClientes()
        self.assertIsInstance(dados, dict)
        self.assertTrue(len(dados) > 0, "Nenhum cliente retornado")

    def test_recuperaPagamentos(self):
        self.assertIsInstance(self.dados, dict)
        self.assertTrue(len(self.dados) > 0, "Nenhum pagamento recuperado")

    def test_geraRelatorio(self):
        relatorio_path = 'relatorio_banco.csv'
        geraRelatorio(relatorio_path, self.dados)
        self.assertTrue(os.path.isfile(relatorio_path))
        with open(relatorio_path, 'r') as f:
            linhas = f.readlines()
            self.assertGreaterEqual(len(linhas), 2)
            self.assertIn('cpfCliente', linhas[0])
        os.remove(relatorio_path)

    def test_exibeRelatorioGeral(self):
        try:
            with patch('builtins.print'):
                exibeRelatorioGeral(self.dados)
        except Exception as e:
            self.fail(f"exibeRelatorioGeral lançou erro: {e}")

    def test_exibeRelatorioFluxoDeCaixa(self):
        try:
            with patch('builtins.print'):
                exibeRelatorioFluxoDeCaixa(self.dados)
        except Exception as e:
            self.fail(f"exibeRelatorioFluxoDeCaixa lançou erro: {e}")

    def test_exibeRelatorioPendencias(self):
        try:
            with patch('builtins.print'):
                exibeRelatorioPendencias(self.dados)
        except Exception as e:
            self.fail(f"exibeRelatorioPendencias lançou erro: {e}")

if __name__ == '__main__':
    unittest.main()
