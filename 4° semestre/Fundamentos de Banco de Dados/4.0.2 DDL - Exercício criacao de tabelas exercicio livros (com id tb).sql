--DROP TABLE livroautor;
--DROP TABLE edicao;
--DROP TABLE livros;
--DROP TABLE autor;

CREATE TABLE autor
(
  id_autor      serial NOT NULL PRIMARY KEY,
  codigo numeric(10,0) NOT NULL,
  nome character varying(35) NOT NULL,
  CONSTRAINT uk_autor UNIQUE (codigo)
);

CREATE TABLE livros
(
  id_livro      serial NOT NULL PRIMARY KEY,
  codigo numeric(10,0) NOT NULL,
  titulo character varying(45) NOT NULL,
  CONSTRAINT uk_livros UNIQUE (codigo)
);

CREATE TABLE edicao
(
  id_edicao      serial NOT NULL PRIMARY KEY,
  codigolivro numeric(10,0) NOT NULL,
  numero character(1) NOT NULL,
  ano integer NOT NULL,
  CONSTRAINT uk_edicao UNIQUE (codigolivro, numero)
);

CREATE TABLE livroautor
(
  id_livro_autor      serial NOT NULL PRIMARY KEY,
  codigolivro numeric(10,0) NOT NULL,
  codigoautor numeric(10,0) NOT NULL,
  CONSTRAINT uk_livroautor UNIQUE (codigolivro, codigoautor)
);