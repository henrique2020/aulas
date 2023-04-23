package model;

public class Turma {
	
	private int codigo;
	private String nome;
	//private Professor professor;
	//private Aluno[] alunos_matriculados = new Aluno[256];
	private Aluno[] alunos_matriculados;
	private int qtdeAlunos = 0;
	
	//public Turma() {}
	
	public Turma(int codigo, String nome, int vagas_disponiveis) {
		this.codigo = codigo;
		this.nome = nome;
		this.alunos_matriculados = new Aluno[vagas_disponiveis];
	}

	public int getCodigo() {
		return codigo;
	}
	public void setCodigo(int codigo) {
		this.codigo = codigo;
	}

	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}

	/*public Aluno[] getAlunos() {
		return alunos_matriculados;
	}
	public void setAlunos(Aluno[] alunos) {
		this.alunos_matriculados = alunos;
	}*/

	public int getQtdeAlunos() {
		return qtdeAlunos;
	}
	public void setQtdeAlunos(int qtdeAlunos) {
		this.qtdeAlunos = qtdeAlunos;
	}
	
	
	public void matricular(Aluno aluno) {
		alunos_matriculados[qtdeAlunos++] = aluno;
	}
	
	/*public void listar_alunos_matriculados() {
		if(this.qtdeAlunos > 0) {
			System.out.printf("Alunos cadastrados da turma de %s\n", this.nome);
			for (int i = 0; i < this.qtdeAlunos; i++) {
				System.out.printf("Nome: %s | CPF: %s\n", alunos_matriculados[i].getNome(), alunos_matriculados[i].getCpf());
			}
		}
	}*/
	
	public String[][] listar_alunos() {
		String[][] aux = new String[this.qtdeAlunos][2];
		for (int i = 0; i < this.qtdeAlunos; i++) {
			aux[i][0] = alunos_matriculados[i].getNome();
			aux[i][1] = alunos_matriculados[i].getCpf();
		}
		return aux;
	}
}
