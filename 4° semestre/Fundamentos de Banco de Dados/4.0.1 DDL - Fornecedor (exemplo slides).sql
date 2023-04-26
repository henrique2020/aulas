--drop table fornecimento;
--drop table projeto;
--drop table peca;
--drop table fornecedor;
--drop table cidade;

CREATE TABLE fornecedor
(
  fcod integer NOT NULL,
  fnome varchar(40) NOT NULL,
  status char(1) NOT NULL DEFAULT 'S',
  cidade varchar(40) NOT NULL,
  CONSTRAINT pk_fornecedor PRIMARY KEY (fcod)
);

CREATE TABLE peca
(
  pcod integer NOT NULL,
  pnome varchar(40) NOT NULL,
  cor char(12) NOT NULL,
  peso float NOT NULL,
  cidade varchar(40) NOT NULL,
  CONSTRAINT pk_peca PRIMARY KEY (pcod)
);

CREATE TABLE instituicao
(
  icod integer NOT NULL,
  nome varchar(40) NOT NULL,
  CONSTRAINT pk_instituicao PRIMARY KEY (icod)
);

CREATE TABLE projeto
(
  prcod integer NOT NULL,
  icod integer NOT NULL,
  prnome varchar(40) NOT NULL,
  cidade varchar(40) NOT NULL,
  CONSTRAINT pk_projeto PRIMARY KEY (prcod, icod),
  CONSTRAINT fk_projeto FOREIGN KEY (icod) REFERENCES instituicao(icod)
);

CREATE TABLE fornecimento
(
  fcod integer NOT NULL,
  pcod integer NOT NULL,
  prcod integer NOT NULL,
  icod integer NOT NULL,
  quantidade integer NOT NULL,
  CONSTRAINT pk_fornecimento PRIMARY KEY (fcod, pcod, prcod, icod),
  CONSTRAINT fk_fornecimento1 FOREIGN KEY (fcod)
      REFERENCES fornecedor (fcod),
  CONSTRAINT fk_fornecimento2 FOREIGN KEY (pcod)
      REFERENCES peca (pcod),
  CONSTRAINT fk_fornecimento3 FOREIGN KEY (prcod,icod)  REFERENCES projeto(prcod, icod) ON DELETE CASCADE
);

