--DROP TABLE livroautor;
--DROP TABLE edicao;
--DROP TABLE livros;
--DROP TABLE autor;

CREATE TABLE autor
(
  codigo numeric(10,0) NOT NULL,
  nome character varying(35) NOT NULL,
  CONSTRAINT pk_autor PRIMARY KEY (codigo)
);

CREATE TABLE livros
(
  codigo numeric(10,0) NOT NULL,
  titulo character varying(45) NOT NULL,
  CONSTRAINT pk_livros PRIMARY KEY (codigo)
);

CREATE TABLE edicao
(
  codigolivro numeric(10,0) NOT NULL,
  numero character(1) NOT NULL,
  ano integer NOT NULL,
  CONSTRAINT pk_edicao PRIMARY KEY (codigolivro, numero),
  CONSTRAINT fk_edicao FOREIGN KEY (codigolivro)
      REFERENCES livros (codigo) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
);

CREATE TABLE livroautor
(
  codigolivro numeric(10,0) NOT NULL,
  codigoautor numeric(10,0) NOT NULL,
  CONSTRAINT pk_livroautor PRIMARY KEY (codigolivro, codigoautor),
  CONSTRAINT fk_livroautor FOREIGN KEY (codigolivro)
      REFERENCES livros (codigo) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT fk_livroautor1 FOREIGN KEY (codigoautor)
      REFERENCES autor (codigo) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
);