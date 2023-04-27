CREATE DATABASE lattes

-- CREATE MAIN TABLES
-- VERIFICAR site, curriculo e pesquisador --
CREATE TABLE site (
    dominio INT NOT NULL,
    nome VARCHAR(100) NOT NULL,
    endereço VARCHAR (100) NOT NULL,

    PRIMARY KEY (dominio)
);

CREATE TABLE curriculo (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(100) NOT NULL,

    PRIMARY KEY (codigo)
);

CREATE TABLE pesquisador (
    id VARCHAR(10) NOT NULL,
    nome VARCHAR(100) NOT NULL,

    PRIMARY KEY (ID)
);

CREATE TABLE producao (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(100) NOT NULL,
    descricao TEXT NOT NULL,
    data DATE NOT NULL,
    orientador VARCHAR(50) NOT NULL,
    localPublicacao VARCHAR(100) NOT NULL,
    
    PRIMARY KEY (codigo)
);

CREATE TABLE producao_bibliografica (
    codigoProducao VARCHAR(10) NOT NULL,
    area VARCHAR(50) NOT NULL,
    tipo VARCHAR(30) NOT NULL,

    PRIMARY KEY (codigoProducao),
    FOREIGN KEY (codigoProducao) REFERENCES producao (codigo)
);

CREATE TABLE producao_tecnica (
    codigoProducao VARCHAR(10) NOT NULL,
    estilo VARCHAR(100) NOT NULL,
    material TEXT NOT NULL,
    tipo VARCHAR(30) NOT NULL,

    PRIMARY KEY (codigoProducao),
    FOREIGN KEY (codigoProducao) REFERENCES producao (codigo)
);

CREATE TABLE producao_cultural (
    codigoProducao VARCHAR(10) NOT NULL,
    autores TEXT NOT NULL,
    editora VARCHAR(100),
    isbn VARCHAR(13) NOT NULL,
    tipo VARCHAR(30) NOT NULL,

    PRIMARY KEY (codigoProducao),
    FOREIGN KEY (codigoProducao) REFERENCES producao (codigo)
);

CREATE TABLE evento (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(100) NOT NULL,
    data DATE NOT NULL,

    PRIMARY KEY (codigo)
);

CREATE TABLE patente (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(100) NOT NULL,
    descricao TEXT NOT NULL,
    data DATE NOT NULL,

    PRIMARY KEY (codigo)
);

CREATE TABLE projeto (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(100) NOT NULL,
    descricao TEXT NOT NULL,
    orientador VARCHAR(50) NOT NULL,
    qtdeAlunos INT,

    PRIMARY KEY (codigo)
);

CREATE TABLE banca (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(100) NOT NULL,
    descricao TEXT NOT NULL,
    data DATE NOT NULL,
    tipo VARCHAR(30),

    PRIMARY KEY (codigo)
);

CREATE TABLE formacao (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(100) NOT NULL,
    dataInicio DATE NOT NULL,
    dataFim DATE,
    tipo VARCHAR(30) NOT NULL,

    PRIMARY KEY (codigo)
);

CREATE TABLE atuacao (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(100) NOT NULL,
    dataInicio DATE NOT NULL,
    dataFim DATE,
    tipo VARCHAR(30) NOT NULL,

    PRIMARY KEY (codigo)
);

CREATE TABLE instituicao (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(100) NOT NULL,

    PRIMARY KEY (codigo)
);

CREATE TABLE endereco (
    codigo VARCHAR(10) NOT NULL,
    cidade VARCHAR(100) NOT NULL,
    bairro VARCHAR(100) NOT NULL,
    numero VARCHAR(10) NOT NULL,
    estado VARCHAR(20) NOT NULL,
    cep VARCHAR(8) NOT NULL,

    PRIMARY KEY (codigo)
);


-- CREATE CONNECTION TABLES
CREATE TABLE pesquisador_producao (
    idPesquisador VARCHAR(10) NOT NULL,
    codigoProducao VARCHAR(10) NOT NULL,

    PRIMARY KEY (idPesquisador, codigoProducao),
    FOREIGN KEY (idPesquisador) REFERENCES pesquisador (id),
    FOREIGN KEY (codigoProducao) REFERENCES producao (codigo)
);

CREATE TABLE pesquisador_evento (
    idPesquisador VARCHAR(10) NOT NULL,
    codigoEvento VARCHAR(10) NOT NULL,

    PRIMARY KEY (idPesquisador, codigoEvento),
    FOREIGN KEY (idPesquisador) REFERENCES pesquisador (id),
    FOREIGN KEY (codigoEvento) REFERENCES evento (codigo)
);

CREATE TABLE pesquisador_patente (
    idPesquisador VARCHAR(10) NOT NULL,
    codigoPatente VARCHAR(10) NOT NULL,

    PRIMARY KEY (idPesquisador, codigoPatente),
    FOREIGN KEY (idPesquisador) REFERENCES pesquisador (id),
    FOREIGN KEY (codigoPatente) REFERENCES patente (codigo)
);

CREATE TABLE pesquisador_projeto (
    idPesquisador VARCHAR(10) NOT NULL,
    codigoProjeto VARCHAR(10) NOT NULL,

    PRIMARY KEY (idPesquisador, codigoProjeto),
    FOREIGN KEY (idPesquisador) REFERENCES pesquisador (id),
    FOREIGN KEY (codigoProjeto) REFERENCES projeto (codigo)
);

CREATE TABLE pesquisador_banca (
    idPesquisador VARCHAR(10) NOT NULL,
    codigoBanca VARCHAR(10) NOT NULL,

    PRIMARY KEY (idPesquisador, codigoBanca),
    FOREIGN KEY (idPesquisador) REFERENCES pesquisador (id),
    FOREIGN KEY (codigoBanca) REFERENCES banca (codigo)
);

CREATE TABLE pesquisador_formacao (
    idPesquisador VARCHAR(10) NOT NULL,
    codigoFormacao VARCHAR(10) NOT NULL,

    PRIMARY KEY (idPesquisador, codigoFormacao),
    FOREIGN KEY (idPesquisador) REFERENCES pesquisador (id),
    FOREIGN KEY (codigoFormacao) REFERENCES formacao (codigo)
);

CREATE TABLE pesquisador_atuacao (
    idPesquisador VARCHAR(10) NOT NULL,
    codigoAtuacao VARCHAR(10) NOT NULL,

    PRIMARY KEY (idPesquisador, codigoAtuacao),
    FOREIGN KEY (idPesquisador) REFERENCES pesquisador (id),
    FOREIGN KEY (codigoAtuacao) REFERENCES atuacao (codigo)
);

CREATE TABLE instituicao_banca (
    codigoInstituicao VARCHAR(10) NOT NULL,
    codigoBanca VARCHAR(10) NOT NULL,

    PRIMARY KEY (codigoInstituicao, codigoBanca),
    FOREIGN KEY (codigoInstituicao) REFERENCES instituicao (codigo),
    FOREIGN KEY (codigoBanca) REFERENCES banca (codigo)
);

CREATE TABLE instituicao_formacao (
    codigoInstituicao VARCHAR(10) NOT NULL,
    codigoFormacao VARCHAR(10) NOT NULL,

    PRIMARY KEY (codigoInstituicao, codigoFormacao),
    FOREIGN KEY (codigoInstituicao) REFERENCES instituicao (codigo),
    FOREIGN KEY (codigoFormacao) REFERENCES formacao (codigo)
);

CREATE TABLE instituicao_atuacao (
    codigoInstituicao VARCHAR(10) NOT NULL,
    codigoAtuacao VARCHAR(10) NOT NULL,

    PRIMARY KEY (codigoInstituicao, codigoAtuacao),
    FOREIGN KEY (codigoInstituicao) REFERENCES instituicao (codigo),
    FOREIGN KEY (codigoAtuacao) REFERENCES atuacao (codigo)
);

CREATE TABLE instituicao_endereco (
    codigoInstituicao VARCHAR(10) NOT NULL,
    codigoEndereco VARCHAR(10) NOT NULL,

    PRIMARY KEY (codigoInstituicao, codigoEndereco),
    FOREIGN KEY (codigoInstituicao) REFERENCES instituicao (codigo),
    FOREIGN KEY (codigoEndereco) REFERENCES endereco (codigo)
);
