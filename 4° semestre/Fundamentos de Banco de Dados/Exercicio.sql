CREATE TABLE aluno (
    cadastro INT NOT NULL, 
    nome VARCHAR(40) NOT NULL, 
    dataNascimento VARCHAR(12) NOT NULL, 
    rua VARCHAR(40) NOT NULL, 
    numero VARCHAR(40) NOT NULL, 
    bairro VARCHAR(40) NOT NULL, 
    cep CHAR(8) NOT NULL, 
    cidade VARCHAR(40) NOT NULL, 
    estado CHAR(2) NOT NULL, 
    pais CHAR(2) NOT NULL,
    CONSTRAINT pk_cadastro PRIMARY KEY(cadastro)
);

CREATE TABLE curso (
    codigo INT NOT NULL, 
    nome VARCHAR(40) NOT NULL, 
    CONSTRAINT pk_codigo PRIMARY KEY(codigo)
);

CREATE TABLE curriculo (
    codCurso INT NOT NULL, 
    letraCurriculo VARCHAR(1) NOT NULL, 
    ano INT NOT NULL, 
    CONSTRAINT pk_codigo_letraCurriculo PRIMARY KEY(codigo, letraCurriculo),
    CONSTRAINT fk_letraCurriculo FOREIGN KEY(letraCurriculo) REFERENCES curso(letraCurriculo)
);


CREATE TABLE curriculo (
    codigo INT NOT NULL, 
    letraCurriculo VARCHAR(1) NOT NULL, 
    ano INT NOT NULL, 
    CONSTRAINT pk_codigo_letraCurriculo PRIMARY KEY(codigo, letraCurriculo),
    CONSTRAINT fk_letraCurriculo FOREIGN KEY(letraCurriculo) REFERENCES curso(letraCurriculo)
);

CREATE TABLE disciplina (
    codigo INT NOT NULL, 
    nome VARCHAR(100) NOT NULL, 
    créditos INT NOT NULL,
    letraTurma VARCHAR(1) NOT NULL, 
    semestre INT NOT NULL, 
    ano INT NOT NULL, 
    sala VARCHAR(10),
    CONSTRAINT pk_codigo_letraTurma PRIMARY KEY(codigo, letraTurma)
);

CREATE TABLE cursoAluno (
    codAluno INT NOT NULL,
    codCurso INT NOT NULL,
    letraCurriculo VARCHAR(1) NOT NULL, 
    anoIngresso INT NOT NULL, 
    CONSTRAINT pk_codigo_letraCurriculo PRIMARY KEY(codAluno, codCurso),
    CONSTRAINT fk_codAluno FOREIGN KEY(codAluno) REFERENCES aluno(codAluno),
    CONSTRAINT fk_codCurso FOREIGN KEY(codCurso) REFERENCES curso(codCurso),
    CONSTRAINT fk_letraCurriculo FOREIGN KEY(letraCurriculo) REFERENCES curriculo(letraCurriculo)
);

CREATE TABLE cursoAluno (
    codAluno INT NOT NULL,
    codDisc INT NOT NULL,
    letraTurma VARCHAR(1) NOT NULL, 
    CONSTRAINT pk_codigo_letraCurriculo PRIMARY KEY(codAluno, codCurso),
    CONSTRAINT fk_codAluno FOREIGN KEY(codAluno) REFERENCES aluno(cadastro),
    CONSTRAINT fk_codDisc FOREIGN KEY(codDisc) REFERENCES disciplina(codigo),
    CONSTRAINT fk_letraTurma FOREIGN KEY(letraTurma) REFERENCES disciplina(letraTurma)
);
