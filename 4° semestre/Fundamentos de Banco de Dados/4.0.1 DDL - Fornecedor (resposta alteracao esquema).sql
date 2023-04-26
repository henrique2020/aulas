drop table instituicao cascade;

CREATE TABLE cidade
(
   ccod integer NOT NULL, 
   cnome varchar (40) NOT NULL, 
   uf character(2) NOT NULL, 
   CONSTRAINT pk_cidade PRIMARY KEY (ccod)
);

alter table fornecedor
drop cidade, 
add ccod integer not null,
add fone integer not null,
add constraint fk_fornecedor foreign key (ccod) references cidade(ccod);

alter table peca
drop cidade,
add ccod integer not null,
add constraint fk_peca1 foreign key (ccod) references cidade(ccod);

alter table fornecimento
drop icod;

alter table projeto
drop cidade,
drop icod,
add ccod integer not null,
add constraint pk_projeto1 foreign key (ccod) references cidade(ccod),
add primary key(prcod);

alter table fornecimento
add primary key(fcod, pcod, prcod),
add constraint fk_fornecimento4 foreign key (prcod) references projeto(prcod);


insert into cidade (ccod, cnome, uf) values (1, 'caxias do sul', 'rs');
insert into cidade (ccod, cnome, uf) values (4, 'bento gonçalves', 'rs');
insert into cidade (ccod, cnome, uf) values (5, 'farroupilha', 'rs');
insert into fornecedor (fcod, fnome, status, ccod, fone) values (1, 'agropecuaria clarice', 'n', 1, 123);
insert into fornecedor (fcod, fnome, status, ccod, fone) values (2, 'agropecuaria fofoao', 'n', 4, 456);
insert into fornecedor (fcod, fnome, status, ccod, fone) values (3, 'agropecuaria notari', 'n', 5, 789);
insert into peca (pcod, pnome, cor, peso, ccod) values (1, 'vaso grande', 'preto', 100, 1);
insert into peca (pcod, pnome, cor, peso, ccod) values (2, 'cachepo', 'branco', 200, 4);
insert into peca (pcod, pnome, cor, peso, ccod) values (3, 'corrente', 'amarelo', 300, 5);
insert into peca (pcod, pnome, cor, peso, ccod) values (4, 'prato', 'branco', 200, 4);
insert into peca (pcod, pnome, cor, peso, ccod) values (5, 'pá', 'amarelo', 300, 5);
insert into projeto (prcod, prnome, ccod) values (1, 'plantacao repolho', 1);
insert into projeto (prcod, prnome, ccod) values (2, 'plantacao maça', 4);
insert into projeto (prcod, prnome, ccod) values (3, 'plantacao abacaxi', 5);	
insert into fornecimento (fcod, pcod, prcod, quantidade) values (1, 1, 1, 100);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (1, 1, 2, 200);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (1, 1, 3, 300);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (1, 2, 1, 400);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (1, 2, 2, 500);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (1, 2, 3, 600);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (1, 3, 1, 700);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (1, 3, 2, 800);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (1, 3, 3, 900);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (2, 1, 1, 100);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (2, 1, 2, 200);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (2, 1, 3, 300);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (2, 2, 1, 400);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (2, 2, 2, 500);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (2, 2, 3, 600);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (2, 3, 1, 700);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (2, 3, 2, 800);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (2, 3, 3, 900);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (3, 1, 1, 100);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (3, 1, 2, 200);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (3, 1, 3, 300);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (3, 2, 1, 400);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (3, 2, 2, 500);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (3, 2, 3, 600);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (3, 3, 1, 700);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (3, 3, 2, 800);
insert into fornecimento (fcod, pcod, prcod, quantidade) values (3, 3, 3, 900);
