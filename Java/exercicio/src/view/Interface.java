package view;

import java.util.Scanner;
import model.Aluno;
import model.Turma;

public class Interface {

	private Aluno[] alunos = new Aluno[256];
	private int qtdeAlunos = 0;
	private Turma[] turmas = new Turma[256];
	private int qtdeTurmas = 0;
	private Scanner scan = new Scanner(System.in);
	
	private int options() {
		System.out.println("0. Sair");
		System.out.println("1. Cadastrar aluno");
		System.out.println("2. Cadastrar turma");
		System.out.println("3. Matricular aluno");
		System.out.println("4. Desmatricular aluno");
		int op = scan.nextInt();
		scan.nextLine();	//Limpa o scan
		return op;
	}
	
	public void exibeMenu() {
		Aluno tempAluno;
		Turma tempTurma;
		int op, idade, cod, vagas;
		boolean rep = true;
		String nome, cpf, sexo;
		
		while(rep) {
			op = this.options();
			switch(op) {
				case 0:
					rep = false;
					break;
				case 1:
					System.out.print("Nome: ");
					nome = scan.nextLine();
					
					System.out.print("CPF: ");
					cpf = scan.nextLine();
					
					tempAluno = new Aluno(nome, cpf);
					
					System.out.print("Idade: ");
					idade = scan.nextInt();
					scan.nextLine();	//Limpa o scan
					tempAluno.setIdade(idade);
					
					System.out.print("Sexo: ");
					sexo = scan.nextLine();
					tempAluno.setSexo(sexo);
					
					//tempAluno = new Aluno(nome, idade, sexo);
					alunos[qtdeAlunos++] = tempAluno;
					
					break;
					
				case 2:
					cod = qtdeTurmas+1;
					
					System.out.print("Nome: ");
					nome = scan.nextLine();
					
					System.out.print("Quantos alunos podem se matricular? ");
					vagas = scan.nextInt();
					
					tempTurma = new Turma(cod, nome, vagas);
					turmas[qtdeTurmas++] = tempTurma;
					
					break;
					
				case 3:
					System.out.print("Nome do aluno: ");
					nome = scan.nextLine();
					
					tempAluno = null;
					for (int i = 0; i < qtdeAlunos; i++) {
						if(nome.equals(alunos[i].getNome())) {
							tempAluno = alunos[i];
							break;
						}
					}
					if(tempAluno == null) {
						System.out.println("Aluno não cadastrado!");
						break;
					}
					
					System.out.print("Código da turma: ");
					cod = scan.nextInt();
					
					tempTurma = null;
					for (int i = 0; i < qtdeTurmas; i++) {
						if(cod == turmas[i].getCodigo()) {
							tempTurma = turmas[i];
							break;
						}
					}
					if(tempTurma == null) {
						System.out.println("Turma não cadastrada!");
						break;
					}
					
					tempTurma.matricular(tempAluno);
					
					break;
				
				case 5:
					System.out.print("Código da turma: ");
					cod = scan.nextInt();
					
					tempTurma = null;
					for (int i = 0; i < qtdeTurmas; i++) {
						if(cod == turmas[i].getCodigo()) {
							tempTurma = turmas[i];
							break;
						}
					}
					if(tempTurma == null) {
						System.out.println("Turma não cadastrada!");
						break;
					}
					//tempTurma.listar_alunos_matriculados();
					String[][] alunos_turma = tempTurma.listar_alunos();
					if(alunos_turma.length > 0) {
						System.out.printf("Alunos cadastrados da turma de %s:\n", tempTurma.getNome());
						for (int i = 0; i < alunos_turma.length; i++) {
							System.out.printf("Nome: %s | CPF: %s\n", alunos_turma[i][0], alunos_turma[i][1]);
						}
					}
					else { System.out.printf("Nehum aluno cadastrado na turma de %s\n", tempTurma.getNome()); }
					
					break;
			}
			
			System.out.println();
		}
		
		scan.close();
	}
}
