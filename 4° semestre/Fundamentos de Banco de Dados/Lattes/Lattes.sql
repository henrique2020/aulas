CREATE DATABASE lattes

-- CREATE MAIN TABLES
CREATE TABLE pesquisador (
    cpf VARCHAR(11) NOT NULL,
    nome VARCHAR(150) NOT NULL,
    sexo VARCHAR(15),
    dataNascimento DATE NOT NULL,
    descricao TEXT,

    PRIMARY KEY (cpf)
);

CREATE TABLE site (
    dominio VARCHAR(50) NOT NULL,
    nome VARCHAR(100) NOT NULL,
    endereco VARCHAR(100) NOT NULL,
    cpfPesquisador VARCHAR(11) NOT NULL,

    PRIMARY KEY (dominio, cpfPesquisador),
    FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf)
);

CREATE TABLE producao (
    codigo VARCHAR(10) NOT NULL,
    nome TEXT NOT NULL,
    descricao TEXT NOT NULL,
    data DATE NOT NULL,
    localPublicacao VARCHAR(100) NOT NULL,
    
    PRIMARY KEY (codigo)
);

CREATE TABLE producao_tecnica (
    codigoProducao VARCHAR(10) NOT NULL,
    area VARCHAR(50) NOT NULL,
    tipo VARCHAR(30) NOT NULL,

    PRIMARY KEY (codigoProducao),
    FOREIGN KEY (codigoProducao) REFERENCES producao (codigo)
);

CREATE TABLE producao_cultural (
    codigoProducao VARCHAR(10) NOT NULL,
    estilo VARCHAR(100) NOT NULL,
    material TEXT NOT NULL,
    tipo VARCHAR(30) NOT NULL,

    PRIMARY KEY (codigoProducao),
    FOREIGN KEY (codigoProducao) REFERENCES producao (codigo)
);

CREATE TABLE producao_bibliografica (
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

CREATE TABLE orgao_regulamentador (
    codigo VARCHAR(10) NOT NULL,
    codigoPatente VARCHAR(10) NOT NULL,
    codigoEndereco VARCHAR(10) NOT NULL,
    abangrencia VARCHAR(50) NOT NULL,

    PRIMARY KEY (codigo, codigoPatente, codigoEndereco),
    FOREIGN KEY (codigoPatente) REFERENCES patente (codigo)
    FOREIGN KEY (codigoEndereco) REFERENCES endereco (codigo)
);

CREATE TABLE projeto (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(100) NOT NULL,
    descricao TEXT NOT NULL,
    qtdeAlunos INT,

    PRIMARY KEY (codigo)
);

CREATE TABLE banca (
    codigo VARCHAR(10) NOT NULL,
    nome TEXT NOT NULL,
    descricao TEXT NOT NULL,
    data DATE NOT NULL,
    tipo VARCHAR(50),

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
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoProducao VARCHAR(10) NOT NULL,
    orientador VARCHAR(50) NOT NULL,

    PRIMARY KEY (cpfPesquisador, codigoProducao),
    FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
    FOREIGN KEY (codigoProducao) REFERENCES producao (codigo)
);

CREATE TABLE pesquisador_evento (
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoEvento VARCHAR(10) NOT NULL,

    PRIMARY KEY (cpfPesquisador, codigoEvento),
    FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
    FOREIGN KEY (codigoEvento) REFERENCES evento (codigo)
);

CREATE TABLE pesquisador_patente (
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoPatente VARCHAR(10) NOT NULL,

    PRIMARY KEY (cpfPesquisador, codigoPatente),
    FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
    FOREIGN KEY (codigoPatente) REFERENCES patente (codigo)
);

CREATE TABLE pesquisador_projeto (
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoProjeto VARCHAR(10) NOT NULL,
    orientador VARCHAR(50) NOT NULL,
    

    PRIMARY KEY (cpfPesquisador, codigoProjeto),
    FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
    FOREIGN KEY (codigoProjeto) REFERENCES projeto (codigo)
);

CREATE TABLE pesquisador_banca (
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoBanca VARCHAR(10) NOT NULL,

    PRIMARY KEY (cpfPesquisador, codigoBanca),
    FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
    FOREIGN KEY (codigoBanca) REFERENCES banca (codigo)
);

CREATE TABLE pesquisador_formacao (
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoFormacao VARCHAR(10) NOT NULL,

    PRIMARY KEY (cpfPesquisador, codigoFormacao),
    FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
    FOREIGN KEY (codigoFormacao) REFERENCES formacao (codigo)
);

CREATE TABLE pesquisador_atuacao (
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoAtuacao VARCHAR(10) NOT NULL,

    PRIMARY KEY (cpfPesquisador, codigoAtuacao),
    FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
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


-- INSERT INTO MAIN TABLES
INSERT INTO pesquisador(cpf, nome, sexo, dataNascimento, descricao) VALUES 
    ('61083713663', 'Mateus Joaquim Lima', 'Masculino', '1992-04-19', ''), 
    ('13625365715', 'Nair Tânia Rodrigues', 'Feminino', '1974-02-18', ''), 
    ('08094448792', 'Nicolas Rafael Joaquim Monteiro', 'Masculino', '1969-02-22', ''), 
    ('21675077479', 'Iago Manoel Arthur Figueiredo', 'Masculino', '1991-03-08', ''), 
    ('73483759107', 'Bento César Ruan Novaes', 'Masculino', '1943-03-21', '');

INSERT INTO site(dominio, nome, endereço, cpfPesquisador) VALUES 
    ('cnpq', 'Plataforma Lattes', 'lattes.cnpq.br', '61083713663'),
    ('cnpq', 'Plataforma Lattes', 'lattes.cnpq.br', '13625365715'),
    ('cnpq', 'Plataforma Lattes', 'lattes.cnpq.br', '08094448792'),
    ('cnpq', 'Plataforma Lattes', 'lattes.cnpq.br', '21675077479'),
    ('cnpq', 'Plataforma Lattes', 'lattes.cnpq.br', '73483759107');

INSERT INTO producao(codigo, nome, descricao, data, localPublicacao) VALUES
    ('PROD-00001', 'Análise in silico dos genomas das linhagens selvagem e mutante do fungo Penicillium equinulatum', 'O uso de ferramentas computacionais para o armazenamento e análise de dados permitiu o desenvolvimento da genômica e da proteômica, possibilitando o estudo de sequências de nucleotídeos e de aminoácidos e trazendo novas descobertas nos mais variados domínios.', '2019-01-01', 'Site'),
    ('PROD-00002', 'Lacos Web', 'O projeto Lagoas Costeiras (LACOS) vem sendo executado desde 2007 e seu foco de atuação abrange a região do litoral gaúcho. Dentre seus principais objetivos, estão inclusos estudos sobre as condições ecológicas das lagoas e seu entorno, a situação socioambiental, o uso turístico e a educação ambiental. Durante este período até o presente momento, diversas coletas de dados ecológicos foram realizadas e incorporadas às informações que vêm sendo armazenadas desde meados de 1970', '2019-01-01', 'Site'),
    ('PROD-00003', 'Bacpp', 'Predição de elementos regulatórios da expressão de genes de bactérias gram-negativas com aprimoramento da ferramenta computacional BACPP', '2015-01-01', 'Revista Científica'),
    ('PROD-00004', 'IntergenicDB', 'O IntergenicDB é um banco de dados que contém sequências de DNA conhecidas como regiões intergênicas (ou promotores) de seres procariotos. O website IntergenicDB é uma ferramenta que prove uma forma simples de efetuar pesquisar e enviar dados para o banco de dados do IntergenicDB..', '2011-01-01', 'TCC'),
    ('PROD-00005', 'wSoft - Metodologia Ágil para Desenvolvimento de Software Orientado à Web', 'A modelagem de um software é a linha motriz que conduz as atividades para o seu desenvolvimento.', '2006-01-01', 'Revista Educacional');

INSERT INTO producao_tecnica(codigoProducao, area, tipo) VALUES 
    ('PROD-00003', 'Informática', 'Previsão futura'),
    ('PROD-00004', 'Informática', 'Avanços científicos')

INSERT INTO producao_cultural(codigoProducao, estilo, material, tipo) VALUES
    ('PROD-00001', 'Testagem', 'Ferramentas Computacionais', ''),
    ('PROD-00005', 'Tendencia', 'Previsão futura', '')

INSERT INTO producao_bibliografica (codigoProducao, autores, editora, isbn, tipo) VALUES 
    ('PROD-00002', 'Daniel Luís Notari, Giovanni Ely Rocco', 'Editora da Universidade de Caxias do Sul', '0689431201444', 'Teórico');

INSERT INTO evento(codigo, nome, data) VALUES 
    ('EVEN-00001', '30 anos CC na UCS', '2013-04-17'),
    ('EVEN-00002', '31 anos CC na UCS', '2014-04-17'),
    ('EVEN-00003', '32 anos CC na UCS', '2015-04-17');

INSERT INTO patente(codigo, nome, descricao, data) VALUES 
    ('PATE-00001', 'Drone X14', 'Drone com 20h de bateria e velocidade máx. de 240km/h', '2017-08-01'),
    ('PATE-00002', 'Gel fixador', 'Gel de secagem rápida capaz de grudar em qualquer tipo de superficie', '2019-04-19'),
    ('PATE-00003', 'Chilete infinito', 'Chiclé com sabor que não desaparece', '2021-11-03')

INSERT INTO projeto(codigo, nome, descricao, qtdeAlunos) VALUES 
    ('PROJ-00001', 'Projeto de evolução da implementação do portal Bacpp de predição de promotores', 'Descricao', '5'),
    ('PROJ-00002', 'rojeto de um portal web para consulta de sequencias intergênicas', 'Descricao', '5'),
    ('PROJ-00003', ' IMPORTAÇÃO DE DADOS PARA O BANCO DE DADOS DO PROJETO LACOS WEB', 'Descricao', '5');

INSERT INTO banca(codigo, nome, descricao, data, tipo) VALUES 
    ('BANC-00001','Predição de regiões promotoras em Bacillus subtilis através do uso de redes neurais artificiais e máquinas de vetor de suporte','DESCRICAO','2018-01-01','Tese'),
    ('BANC-00002','Participação em banca de Hugo André Klauck. Análise de regiões intergênicas de E. Coli utilizando ferramentas computacionais','DESCRICAO','2019-04-10','Exame de qualificação');

INSERT INTO formacao(codigo, nome, dataInicio, dataFim, tipo) VALUES 
    ('FORM-00001','Ciencia da Computação','2015-01-01','2021-06-01','Bacharelado'),
    ('FORM-00002','Analise e Desenvolvimento','2015-01-01','2017-12-31','Bacharelado'),
    ('FORM-00003','Agronomia','2015-01-01',null,'Bacharelado'),
    ('FORM-00004','Matematica','2015-01-01',null,'Bacharelado'),
    ('FORM-00005','Estudo de IA','2023-01-01',null,'Pós-Graduação'),
    ('FORM-00006','Front x Back','2018-01-01','2019-06-30','Pós-Graduação'),
    ('FORM-00007','Estudo do Sonar','2020-01-01','2022-12-31','Doutorado');

INSERT INTO atuacao(codigo, nome, dataInicio, dataFim, tipo) VALUES 
    ('ATUA-00001','Cientista de Dados','2017-09-16','2019-10-14','Pesquisador'),
    ('ATUA-00002','Progrador back-end','2015-07-29',null, 'Progaramdor'),
    ('ATUA-00003','Contador','2009-05-17',null,'Analista'),
    ('ATUA-00004','Database Manager','2020-01-01','2021-04-12','Analista de Dados'),
    ('ATUA-00005','Professor','2021-04-19',null,'Professor');

INSERT INTO instituicao(codigo, nome) VALUES 
	('INST-00001','UCS');

INSERT INTO endereco(codigo, cidade, bairro, numero, estado, cep) VALUES 
    ('ENDE-00001','Caxias do Sul','Vila Cristina','S/N','RS','9200030'),
    ('ENDE-00002','Farroupilnha','Ambaí','112','RS','96263000');

INSERT INTO orgao_regulamentador(codigo, codigoPatente, codigoEndereco, abangrencia) VALUES
    ('OGRE-00001', 'PATE-00001', 'ENDE-00001', 'Nacionais'),
    ('OGRE-00002', 'PATE-00002', 'ENDE-00002', 'Internacioanl'),
    ('OGRE-00003', 'PATE-00003', 'ENDE-00002', 'Nacionais');

-- INSERT INTO CONNECTION TABLES
INSERT INTO pesquisador_producao (cpfPesquisador, codigoProducao, orientador) VALUES 
    ('08094448792', 'PROD-00001', 'Scheila de Avila e Silva'), 
    ('13625365715', 'PROD-00002', 'Daniel Luís Notari'), 
    ('21675077479', 'PROD-00003', 'Scheila de Ávila e Silva'), 
    ('61083713663', 'PROD-00004', 'Daniel Luís Notari'), 
    ('73483759107', 'PROD-00005', 'Iraci Cristina Silveira');

INSERT INTO pesquisador_evento (cpfPesquisador, codigoEvento) VALUES 
    ('08094448792', 'EVEN-00001'), 
    ('08094448792', 'EVEN-00002'), 
    ('61083713663', 'EVEN-00003'), 
    ('73483759107', 'EVEN-00002'), 
    ('08094448792', 'EVEN-00003'), 
    ('13625365715', 'EVEN-00003');

INSERT INTO pesquisador_patente (cpfPesquisador, codigoPatente) VALUES 
    ('73483759107', 'PATE-00001'), 
    ('61083713663', 'PATE-00001'), 
    ('61083713663', 'PATE-00002'), 
    ('13625365715', 'PATE-00001'), 
    ('08094448792', 'PATE-00001')

INSERT INTO pesquisador_projeto (cpfPesquisador, codigoProjeto, orientador) VALUES 
    ('08094448792', 'PROJ-00001', 'Diego Silva'), 
    ('13625365715', 'PROJ-00001', 'Diego Silva'), 
    ('13625365715', 'PROJ-00003', 'Diego Silva'), 
    ('73483759107', 'PROJ-00002', 'Diego Silva');

INSERT INTO pesquisador_banca (cpfPesquisador, codigoBanca) VALUES 
    ('08094448792', 'BANC-00001'), 
    ('13625365715', 'BANC-00002'), 
    ('08094448792', 'BANC-00002');

INSERT INTO pesquisador_formacao (cpfPesquisador, codigoFormacao) VALUES 
    ('21675077479', 'FORM-00001'), 
    ('73483759107', 'FORM-00002'), 
    ('73483759107', 'FORM-00004'), 
    ('21675077479', 'FORM-00006'), 
    ('21675077479', 'FORM-00007'), 
    ('13625365715', 'FORM-00003'), 
    ('13625365715', 'FORM-00005');

INSERT INTO pesquisador_atuacao (cpfPesquisador, codigoAtuacao) VALUES 
    ('08094448792', 'ATUA-00002'), 
    ('21675077479', 'ATUA-00005'), 
    ('13625365715', 'ATUA-00003'), 
    ('73483759107', 'ATUA-00001'), 
    ('61083713663', 'ATUA-00004');

INSERT INTO instituicao_banca (codigoInstituicao, codigoBanca) VALUES 
    ('INST-00001', 'BANC-00002'), 
    ('INST-00001', 'BANC-00001');

INSERT INTO instituicao_atuacao (codigoInstituicao, codigoAtuacao) VALUES 
    ('INST-00001', 'ATUA-00002'), 
    ('INST-00001', 'ATUA-00004');

INSERT INTO instituicao_endereco (codigoInstituicao, codigoEndereco ''', CAMPUS???''') VALUES 
    ('INST-00001', 'ENDE-00001'), 
    ('INST-00001', 'ENDE-00002');
