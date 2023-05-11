CREATE DATABASE lattes

-- CREATE MAIN TABLES
CREATE TABLE pesquisador (
    cpf VARCHAR(11) NOT NULL,
    nome VARCHAR(250) NOT NULL,
    sexo VARCHAR(20),
    dataNascimento DATE NOT NULL,
    descricao TEXT,

    CONSTRAINT pk_ PRIMARY KEY (cpf)
);

CREATE TABLE site (
    dominio VARCHAR(200) NOT NULL,
    nome VARCHAR(250) NOT NULL,
    endereco VARCHAR(200) NOT NULL,
    cpfPesquisador VARCHAR(11) NOT NULL,

    CONSTRAINT pk_dominio_cpfPesquisador PRIMARY KEY (dominio, cpfPesquisador),
    CONSTRAINT fk_site_pesuisador FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf)
);

CREATE TABLE producao (
    codigo VARCHAR(10) NOT NULL,
    nome TEXT NOT NULL,
    descricao TEXT NOT NULL,
    data DATE NOT NULL,
    localPublicacao VARCHAR(200),
    
    CONSTRAINT pk_codigo PRIMARY KEY (codigo)
);

CREATE TABLE producao_tecnica (
    codigoProducao VARCHAR(10) NOT NULL,
    area VARCHAR(200) NOT NULL,
    tipo VARCHAR(200) NOT NULL,

    CONSTRAINT pk_codigoProducao PRIMARY KEY (codigoProducao),
    CONSTRAINT fk_producaoTecnica_producao FOREIGN KEY (codigoProducao) REFERENCES producao (codigo)
);

CREATE TABLE producao_cultural (
    codigoProducao VARCHAR(10) NOT NULL,
    estilo VARCHAR(200) NOT NULL,
    material TEXT NOT NULL,
    tipo VARCHAR(200) NOT NULL,

    CONSTRAINT pk_codigoProducao PRIMARY KEY (codigoProducao),
    CONSTRAINT fk_producaoCultural_producao FOREIGN KEY (codigoProducao) REFERENCES producao (codigo)
);

CREATE TABLE producao_bibliografica (
    codigoProducao VARCHAR(10) NOT NULL,
    autores TEXT NOT NULL,
    editora VARCHAR(200),
    isbn VARCHAR(13),
    tipo VARCHAR(200) NOT NULL,

    CONSTRAINT pk_codigoProducao PRIMARY KEY (codigoProducao),
    CONSTRAINT fk_producaoBibliografica_producao FOREIGN KEY (codigoProducao) REFERENCES producao (codigo)
);

CREATE TABLE evento (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(250) NOT NULL,
    data DATE NOT NULL,

    CONSTRAINT pk_codigo PRIMARY KEY (codigo)
);

CREATE TABLE patente (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(250) NOT NULL,
    descricao TEXT NOT NULL,
    data DATE NOT NULL,

    CONSTRAINT pk_codigo PRIMARY KEY (codigo)
);

CREATE TABLE projeto (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(250) NOT NULL,
    descricao TEXT NOT NULL,
    qtdeAlunos INT,

    CONSTRAINT pk_codigo PRIMARY KEY (codigo)
);

CREATE TABLE banca (
    codigo VARCHAR(10) NOT NULL,
    nome TEXT NOT NULL,
    descricao TEXT NOT NULL,
    data DATE NOT NULL,
    tipo VARCHAR(200),

    CONSTRAINT pk_codigo PRIMARY KEY (codigo)
);

CREATE TABLE formacao (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(250) NOT NULL,
    dataInicio DATE NOT NULL,
    dataFim DATE,
    tipo VARCHAR(200) NOT NULL,

    CONSTRAINT pk_codigo PRIMARY KEY (codigo)
);

CREATE TABLE atuacao (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(250) NOT NULL,
    dataInicio DATE NOT NULL,
    dataFim DATE,
    tipo VARCHAR(200) NOT NULL,

    CONSTRAINT pk_codigo PRIMARY KEY (codigo)
);

CREATE TABLE instituicao (
    codigo VARCHAR(10) NOT NULL,
    nome VARCHAR(250) NOT NULL,

    CONSTRAINT pk_codigo PRIMARY KEY (codigo)
);

CREATE TABLE endereco (
    codigo VARCHAR(10) NOT NULL,
    cidade VARCHAR(200) NOT NULL,
    bairro VARCHAR(200) NOT NULL,
    numero VARCHAR(10) NOT NULL,
    estado VARCHAR(20) NOT NULL,
    cep VARCHAR(8) NOT NULL,

    CONSTRAINT pk_codigo PRIMARY KEY (codigo)
);

CREATE TABLE orgao_regulamentador (
    codigo VARCHAR(10) NOT NULL,
    codigoPatente VARCHAR(10) NOT NULL,
    codigoEndereco VARCHAR(10) NOT NULL,
    abangrencia VARCHAR(200) NOT NULL,

    CONSTRAINT pk_codigo_codigoPatente_codigoEndereco PRIMARY KEY (codigo, codigoPatente, codigoEndereco),
    CONSTRAINT fk_orgaRegulamentador_patente FOREIGN KEY (codigoPatente) REFERENCES patente (codigo),
    CONSTRAINT fk_orgaRegulamentador_endereco FOREIGN KEY (codigoEndereco) REFERENCES endereco (codigo)
);


-- CREATE CONNECTION TABLES
CREATE TABLE pesquisador_producao (
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoProducao VARCHAR(10) NOT NULL,
    orientador VARCHAR(200) NOT NULL,

    CONSTRAINT pk_cpfPesquisador_codigoProducao PRIMARY KEY (cpfPesquisador, codigoProducao),
    CONSTRAINT fk_producao_cepfPesquisador FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
    CONSTRAINT fk_producao_codigoProducao FOREIGN KEY (codigoProducao) REFERENCES producao (codigo)
);

CREATE TABLE pesquisador_evento (
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoEvento VARCHAR(10) NOT NULL,

    CONSTRAINT pk_cpfPesquisador_codigoEvento PRIMARY KEY (cpfPesquisador, codigoEvento),
    CONSTRAINT fk_pesquisadorEvento_pesquisador FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
    CONSTRAINT fk_pesquisadorEvento_evento FOREIGN KEY (codigoEvento) REFERENCES evento (codigo)
);

CREATE TABLE pesquisador_patente (
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoPatente VARCHAR(10) NOT NULL,

    CONSTRAINT pk_cpfPesquisador_codigoPatente PRIMARY KEY (cpfPesquisador, codigoPatente),
    CONSTRAINT fk_pesquisadorPatente_pesquisador FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
    CONSTRAINT fk_pesquisadorPatente_patente FOREIGN KEY (codigoPatente) REFERENCES patente (codigo)
);

CREATE TABLE pesquisador_projeto (
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoProjeto VARCHAR(10) NOT NULL,
    orientador VARCHAR(200) NOT NULL,
    

    CONSTRAINT pk_cpfPesquisador_codigoProjeto PRIMARY KEY (cpfPesquisador, codigoProjeto),
    CONSTRAINT fk_pesquisadorProjeto_pesquisador FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
    CONSTRAINT fk_pesquisadorProjeto_projeto FOREIGN KEY (codigoProjeto) REFERENCES projeto (codigo)
);

CREATE TABLE pesquisador_banca (
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoBanca VARCHAR(10) NOT NULL,

    CONSTRAINT pk_cpfPesquisador_codigoBanca PRIMARY KEY (cpfPesquisador, codigoBanca),
    CONSTRAINT fk_pesquisadorBanca_pesquisador FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
    CONSTRAINT fk_pesquisadorBanca_banca FOREIGN KEY (codigoBanca) REFERENCES banca (codigo)
);

CREATE TABLE pesquisador_formacao (
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoFormacao VARCHAR(10) NOT NULL,

    CONSTRAINT pk_cpfPesquisador_codigoFormacao PRIMARY KEY (cpfPesquisador, codigoFormacao),
    CONSTRAINT fk_pesquisadorFormacao_pesquisador FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
    CONSTRAINT fk_pesquisadorFormacao_formacao FOREIGN KEY (codigoFormacao) REFERENCES formacao (codigo)
);

CREATE TABLE pesquisador_atuacao (
    cpfPesquisador VARCHAR(11) NOT NULL,
    codigoAtuacao VARCHAR(10) NOT NULL,

    CONSTRAINT pk_cpfPesquisador_codigoAtuacao PRIMARY KEY (cpfPesquisador, codigoAtuacao),
    CONSTRAINT fk_pesquisadorAtuacao_pesquisador FOREIGN KEY (cpfPesquisador) REFERENCES pesquisador (cpf),
    CONSTRAINT fk_pesquisadorAtuacao_atuacao FOREIGN KEY (codigoAtuacao) REFERENCES atuacao (codigo)
);

CREATE TABLE instituicao_banca (
    codigoInstituicao VARCHAR(10) NOT NULL,
    codigoBanca VARCHAR(10) NOT NULL,

    CONSTRAINT pk_codigoInstituicao_codigoBanca PRIMARY KEY (codigoInstituicao, codigoBanca),
    CONSTRAINT fk_instituicaoBanca_instituicao FOREIGN KEY (codigoInstituicao) REFERENCES instituicao (codigo),
    CONSTRAINT fk_instituicaoBanca_banca FOREIGN KEY (codigoBanca) REFERENCES banca (codigo)
);

CREATE TABLE instituicao_formacao (
    codigoInstituicao VARCHAR(10) NOT NULL,
    codigoFormacao VARCHAR(10) NOT NULL,

    CONSTRAINT pk_codigoInstituicao_codigoFormacao PRIMARY KEY (codigoInstituicao, codigoFormacao),
    CONSTRAINT fk_instituicaoFormacao_instituicao FOREIGN KEY (codigoInstituicao) REFERENCES instituicao (codigo),
    CONSTRAINT fk_instituicaoFormacao_formacao FOREIGN KEY (codigoFormacao) REFERENCES formacao (codigo)
);

CREATE TABLE instituicao_atuacao (
    codigoInstituicao VARCHAR(10) NOT NULL,
    codigoAtuacao VARCHAR(10) NOT NULL,

    CONSTRAINT pk_codigoInstituicao_codigoAtuacao PRIMARY KEY (codigoInstituicao, codigoAtuacao),
    CONSTRAINT fk_instituicaoAtuacao_instituicao FOREIGN KEY (codigoInstituicao) REFERENCES instituicao (codigo),
    CONSTRAINT fk_instituicaoAtuacao_atuacao FOREIGN KEY (codigoAtuacao) REFERENCES atuacao (codigo)
);

CREATE TABLE instituicao_endereco (
    codigoInstituicao VARCHAR(10) NOT NULL,
    codigoEndereco VARCHAR(10) NOT NULL,

    CONSTRAINT pk_codigoInstituicao_codigoEndereco PRIMARY KEY (codigoInstituicao, codigoEndereco),
    CONSTRAINT fk_fk_instituicaoEndereco_instituicao FOREIGN KEY (codigoInstituicao) REFERENCES instituicao (codigo),
    CONSTRAINT fk_fk_instituicaoEndereco_endereco FOREIGN KEY (codigoEndereco) REFERENCES endereco (codigo)
);


-- INSERT INTO MAIN TABLES
INSERT INTO pesquisador(cpf, nome, sexo, dataNascimento, descricao) VALUES 
    ('61083713663', 'Mateus Joaquim Lima', 'Masculino', '1992-04-19', 'Possui graduação em Ciência da Computação pela Universidade de Caxias do Sul (1998). A formação stricto sensu inclui mestrado em Ciência da Computação pela Universidade Federal do Rio Grande do Sul (2000), doutorado em Biotecnologia pela Universidade de Caxias do Sul (2012) e pós-doutorado em Administração pela Universidade de Caxias do Sul (2019). Atualmente é professor assistente da Área do Conhecimento de Ciências Exatas e Engenharias da Universidade de Caxias do Sul (UCS). Fui coordenador do Curso de Ciência da Computação das ofertas de Caxias do Sul e de Bento Gonçalves da Universidade de Caxias do Sul. Atua como pesquisador do City Lliving Lab vinculado ao Programa de Pós-Graduação em Administração e no Núcleo de pesquisa em Bioinformática. Possui experiência em análise de dados e integração de bases de dados científicas (biológicos, cidades do conhecimento/sistemas de capitais). Os atuais projetos de pesquisa estão relacionados ao problema de predição de promotores e ao desenvolvimento baseado em conhecimento e cidades inteligentes. Já orientou estudantes em nível de especialização/MBA, iniciação científica e graduação. A produção científica está relacionada, principalmente, com a análise computacional de dados genômicos e ao desenvolvimento baseado em conhecimento e cidades inteligentes, destacando-se a concessão de patente nacional sobre um novo método de sistema de tratamento de dados experimentais'), 
    ('13625365715', 'Nair Tânia Rodrigues', 'Feminino', '1974-02-18', 'Possui graduação em Ciência da Computação pela Universidade de Caxias do Sul (1998). A formação stricto sensu inclui mestrado em Ciência da Computação pela Universidade Federal do Rio Grande do Sul (2000), doutorado em Biotecnologia pela Universidade de Caxias do Sul (2012) e pós-doutorado em Administração pela Universidade de Caxias do Sul (2019). Atualmente é professor assistente da Área do Conhecimento de Ciências Exatas e Engenharias da Universidade de Caxias do Sul (UCS). Fui coordenador do Curso de Ciência da Computação das ofertas de Caxias do Sul e de Bento Gonçalves da Universidade de Caxias do Sul. Atua como pesquisador do City Lliving Lab vinculado ao Programa de Pós-Graduação em Administração e no Núcleo de pesquisa em Bioinformática. Possui experiência em análise de dados e integração de bases de dados científicas (biológicos, cidades do conhecimento/sistemas de capitais). Os atuais projetos de pesquisa estão relacionados ao problema de predição de promotores e ao desenvolvimento baseado em conhecimento e cidades inteligentes. Já orientou estudantes em nível de especialização/MBA, iniciação científica e graduação. A produção científica está relacionada, principalmente, com a análise computacional de dados genômicos e ao desenvolvimento baseado em conhecimento e cidades inteligentes, destacando-se a concessão de patente nacional sobre um novo método de sistema de tratamento de dados experimentais'), 
    ('08094448792', 'Nicolas Rafael Joaquim Monteiro', 'Masculino', '1969-02-22', 'Possui graduação em Ciência da Computação pela Universidade de Caxias do Sul (1998). A formação stricto sensu inclui mestrado em Ciência da Computação pela Universidade Federal do Rio Grande do Sul (2000), doutorado em Biotecnologia pela Universidade de Caxias do Sul (2012) e pós-doutorado em Administração pela Universidade de Caxias do Sul (2019). Atualmente é professor assistente da Área do Conhecimento de Ciências Exatas e Engenharias da Universidade de Caxias do Sul (UCS). Fui coordenador do Curso de Ciência da Computação das ofertas de Caxias do Sul e de Bento Gonçalves da Universidade de Caxias do Sul. Atua como pesquisador do City Lliving Lab vinculado ao Programa de Pós-Graduação em Administração e no Núcleo de pesquisa em Bioinformática. Possui experiência em análise de dados e integração de bases de dados científicas (biológicos, cidades do conhecimento/sistemas de capitais). Os atuais projetos de pesquisa estão relacionados ao problema de predição de promotores e ao desenvolvimento baseado em conhecimento e cidades inteligentes. Já orientou estudantes em nível de especialização/MBA, iniciação científica e graduação. A produção científica está relacionada, principalmente, com a análise computacional de dados genômicos e ao desenvolvimento baseado em conhecimento e cidades inteligentes, destacando-se a concessão de patente nacional sobre um novo método de sistema de tratamento de dados experimentais'), 
    ('21675077479', 'Iago Manoel Arthur Figueiredo', 'Masculino', '1991-03-08', 'Possui graduação em Ciência da Computação pela Universidade de Caxias do Sul (1998). A formação stricto sensu inclui mestrado em Ciência da Computação pela Universidade Federal do Rio Grande do Sul (2000), doutorado em Biotecnologia pela Universidade de Caxias do Sul (2012) e pós-doutorado em Administração pela Universidade de Caxias do Sul (2019). Atualmente é professor assistente da Área do Conhecimento de Ciências Exatas e Engenharias da Universidade de Caxias do Sul (UCS). Fui coordenador do Curso de Ciência da Computação das ofertas de Caxias do Sul e de Bento Gonçalves da Universidade de Caxias do Sul. Atua como pesquisador do City Lliving Lab vinculado ao Programa de Pós-Graduação em Administração e no Núcleo de pesquisa em Bioinformática. Possui experiência em análise de dados e integração de bases de dados científicas (biológicos, cidades do conhecimento/sistemas de capitais). Os atuais projetos de pesquisa estão relacionados ao problema de predição de promotores e ao desenvolvimento baseado em conhecimento e cidades inteligentes. Já orientou estudantes em nível de especialização/MBA, iniciação científica e graduação. A produção científica está relacionada, principalmente, com a análise computacional de dados genômicos e ao desenvolvimento baseado em conhecimento e cidades inteligentes, destacando-se a concessão de patente nacional sobre um novo método de sistema de tratamento de dados experimentais'), 
    ('73483759107', 'Bento César Ruan Novaes', 'Masculino', '1943-03-21', 'Possui graduação em Ciência da Computação pela Universidade de Caxias do Sul (1998). A formação stricto sensu inclui mestrado em Ciência da Computação pela Universidade Federal do Rio Grande do Sul (2000), doutorado em Biotecnologia pela Universidade de Caxias do Sul (2012) e pós-doutorado em Administração pela Universidade de Caxias do Sul (2019). Atualmente é professor assistente da Área do Conhecimento de Ciências Exatas e Engenharias da Universidade de Caxias do Sul (UCS). Fui coordenador do Curso de Ciência da Computação das ofertas de Caxias do Sul e de Bento Gonçalves da Universidade de Caxias do Sul. Atua como pesquisador do City Lliving Lab vinculado ao Programa de Pós-Graduação em Administração e no Núcleo de pesquisa em Bioinformática. Possui experiência em análise de dados e integração de bases de dados científicas (biológicos, cidades do conhecimento/sistemas de capitais). Os atuais projetos de pesquisa estão relacionados ao problema de predição de promotores e ao desenvolvimento baseado em conhecimento e cidades inteligentes. Já orientou estudantes em nível de especialização/MBA, iniciação científica e graduação. A produção científica está relacionada, principalmente, com a análise computacional de dados genômicos e ao desenvolvimento baseado em conhecimento e cidades inteligentes, destacando-se a concessão de patente nacional sobre um novo método de sistema de tratamento de dados experimentais');

INSERT INTO site(dominio, nome, endereco, cpfPesquisador) VALUES 
    ('cnpq', 'Plataforma Lattes', 'lattes.cnpq.br', '61083713663'),
    ('cnpq', 'Plataforma Lattes', 'lattes.cnpq.br', '13625365715'),
    ('cnpq', 'Plataforma Lattes', 'lattes.cnpq.br', '08094448792'),
    ('cnpq', 'Plataforma Lattes', 'lattes.cnpq.br', '21675077479'),
    ('cnpq', 'Plataforma Lattes', 'lattes.cnpq.br', '73483759107');

INSERT INTO producao(codigo, nome, descricao, data, localPublicacao) VALUES
    ('PROD-00001', 'Resíduos metalúrgicos, indução de tumor e envelhecimento: um risco ocupacional explicado pela quimio-biologia de sistemas', 'Apresentação de Trabalho/Outra', '2011-01-01', null),
    ('PROD-00002', 'Biological Databases Integration: A Data Warehouse Perspective Applied to Intergenic Regions', 'Artigo Científico', '2019-01-01', 'Scotland: Glasgow: ECronicon Open Access'),
    ('PROD-00003', 'Avaliação de Software Educacional na Educação Básica: Uma abordagem qualitativa com o framework DECIDE', 'Artigo Completo', '2022-01-01', 'REVISTA DE ENSINO, EDUCAÇÃO E CIÊNCIAS HUMANAS'),
    ('PROD-00004', 'Diretrizes Gerais para os Trabalhos de Conclusão de Curso da Universidade de Caxias do Sul', 'Desenvolvimento de material didático ou instrucional', '2007-01-01', 'Universidade de Caxias do Sul'),
    ('PROD-00005', 'Monitor de Programação Orientada a Objetos com Java', 'Monitoria', '2000-01-01', null);

INSERT INTO producao_bibliografica (codigoProducao, autores, editora, isbn, tipo) VALUES 
    ('PROD-00001', 'Nair Tânia Rodrigues, Bento César Ruan Novaes', null, null, 'Apresentação de Trabalho/Outra'),
    ('PROD-00002', 'Nair Tânia Rodrigues, Nicolas Rafael Joaquim Monteiro', null, null, 'Artigo Científico'),
    ('PROD-00003', 'Iago Manoel Arthur Figueiredo, Bento César Ruan Novaes', 'Editora da Universidade de Caxias do Sul', null, 'Artigo Completo');

INSERT INTO producao_tecnica(codigoProducao, area, tipo) VALUES 
    ('PROD-00004', 'Informática', 'Desenvolvimento de material didático ou instrucional'),
    ('PROD-00005', 'Informática', 'Monitoria');

INSERT INTO evento(codigo, nome, data) VALUES 
    ('EVEN-00001', 'Mind7 Startup 2023', '2023-01-01'),
    ('EVEN-00002', 'Foss Day Bento Gonçalves 2019', '2019-01-01'),
    ('EVEN-00003', 'XXXVII Congresso da Sociedade Brasileira de Computação', '2017-01-01'),
    ('EVEN-00004', 'Escola Gaucha de Bioinformática.Prospecção de Dados Biológicos usando Ferramentas de Programação em Java', '2015-01-01'),
    ('EVEN-00005', 'I Curso de Inverno em Bioinformática - USP', '2008-01-01');

INSERT INTO patente(codigo, nome, descricao, data) VALUES 
    ('PATE-00001', 'Sistema de Tratamento de Dados Experimentais, Método Eletrônico e Mídia Física', 'Sistema de Tratamento de Dados Experimentais, Método Eletrônico e Mídia Física', '2014-10-13'),
    ('PATE-00002', 'Lacos Web', 'Programa de Computador', '2020-04-28'),
    ('PATE-00003', 'BacPP', 'Programa de Computador', '2020-04-22'),
    ('PATE-00004', 'IntergenicDB', 'Programa de Computador', '2020-04-22'),
    ('PATE-00005', 'KBD2', 'Programa de Computador', '2021-02-17');

INSERT INTO projeto(codigo, nome, descricao, qtdeAlunos) VALUES 
    ('PROJ-00001', 'Sistema de coleta de dados por dispositivos IoT (sensoriamento) para cidades inteligentes', 'O presente projeto pretende viabilizar o uso de soluções tecnológicas inovadoras para impulsionar a inovação, desenvolvimento sustentável, pesquisa científica e economia, melhorando a qualidade de vida da população por meio da melhoria dos serviços oferecidos a ela. Isso se dará por meio do desenvolvimento e validação de um sistema de coleta de dados ambientais em tempo real por dispositivos IoT (sensoriamento) para cidades inteligentes. É importante salientar que ao desenvolver e implementar esse sistema, a infraestrutura de hardware e software utilizada para este projeto habilitará cidades da região Serra, Hortênsias para uso mais amplo de dispositivos IoT o que possibilitará que no futuro outros dispositivos sejam integrados. Além disso, para possibilitar o acesso aos dados obtidos e disponibilizá-los para os usuários, será construído um protótipo de um sistema em nuvem da camada de armazenamento e visualização dos dados. Com isso, os dados poderão ser tratados por diferentes atores para gerar informações em tempo real. O projeto será balizado nas diretrizes da ISO 37122 e nas determinações da Lei Geral de Proteção de Dados (LGPD). A área de abrangência da proposta são seis cidades da região Serra, Hortênsias e Campos de Cima da Serra. Os dados tratados, gerados por sensores IoT fornecerão métricas sobre temperatura, umidade, qualidade do ar, níveis de ruídos, luminosidade, entre outros a depender dos recursos disponíveis. Os dados serão transmitidos por meio de uma rede open source de transmissão de área ampla de baixa potência chamada LoRaWAN, para uma interface centralizada que alimentará uma base de dados. Este movimento contemplará a aquisição e testes de sensores IoT com diferentes funcionalidades, a parametrização de uma interface que atuará como repositório central de dados advindos dos sensores IoT e a construção de um protótipo em nuvem da camada de armazenamento e visualização dos dado', '6'),
    ('PROJ-00002', 'Bacpp', 'Predição de elementos regulatórios da expressão de genes de bactérias gram-negativas com aprimoramento da ferramenta computacional BACPP', '4'),
    ('PROJ-00003', 'IntergenicDB', 'O IntergenicDB é um banco de dados que contém sequências de DNA conhecidas como regiões intergênicas (ou promotores) de seres procariotos. O website IntergenicDB é uma ferramenta que prove uma forma simples de efetuar pesquisar e enviar dados para o banco de dados do IntergenicDB', '3'),
    ('PROJ-00004', 'PROTEASES EXTRACELULARES DE Aeromonas spp', 'Identificação das espécies do gênero Candida isoladas em pacientes HIV/AIDS com candidíase oral e avaliação do perfil de sensibilidade e resistência a drogas antifúngicas', '5'),
    ('PROJ-00005', 'Determinação de Aeromonas em suinos e seus produtos: estudo comparativo entre os métodos convencionais e moleculares', 'Diversos trabalhos vêm demonstrando a presença de Aeromonas em suínos e seus produtos. A relevância deste microrganismo no processo ou produto não é conhecida. Entretanto, suas características, em particular crescimento em baixas temperaturas, produção de lípases, proteases e halotolerância, permitem considera-lo como um potencial contaminante e deteriorante de produtos carneos in natura ou processados. Alem disso, a comprovada patogenicidade de muitos isolados de Aeromonas torna estes organismos de grande relevância na área de saúde pública. Testes microbiológicos clássicos, como plaqueamento ou determinação de número mais provável, não são disponíveis ou tem eficiência limitada ou são muito demorados para determinação de Aeromonas. Fatos estes que tem limitado o número de referência quanto à presença destas bactérias e consequentemente, levado a negligenciar a sua importância como deteriorante ou patógeno. Apesar de não consideradas como técnicas microbiológicas básicas para análise de alimentos, as técnicas moleculares, em particular PCR tem mostrado elevada eficiência na avaliação quali e quantitativa de microrganismos recalcitrantes ou de difícil caracterização. No caso particular de Aeromonas, trabalhos prévios realizados por nosso grupo mostram que o gene lipA é característico deste gênero, estando presente em 99% dos isolados clínicos e ambientais de Aeromonas, e que o gene aerA, responsável pela aerolisina/hemolisina citotóxica, está presente em todas os isolados com potencial patogênico. Assim sendo, o presente projeto visa avaliar a eficiência dos genes lipA e aerA na determinação quali-quantitativa de Aeromonas em suínos, estimar a prevalência destas bactérias em suínos e seus produtos, e estabelecer os pontos crítico no processo de suínos utilizando estas bactérias como indicadores que qualidade microbiológica', '4');

INSERT INTO banca(codigo, nome, descricao, data, tipo) VALUES 
    ('BANC-00001', 'Promoter sequence characterazation through the analysis of enthalpy, entropy, stability and base-pair stacking values', 'Participação em banca de Gustavo Sganzerla Martinez', '2018-01-01', 'Mestrado'),
    ('BANC-00002', 'predição de regiões promotoras em Bacillus subtilis através do uso de redes neurais artificiais e máquinas de vetor de suporte', 'Participação em banca de Rafael Coelho', '2018-01-01', 'Teses de doutorado'),
    ('BANC-00003', 'Smart Cities: Uso de sensores e dados secundários para cidades inteligentes centradas no cidadão', 'Participação em banca de Mayron Dalla Santa de Carvalho', '2021-01-01', 'Qualificações de Doutorado'),
    ('BANC-00004', 'Análise de regiões intergênicas de E. Coli utilizando ferramentas computacionais', 'Participação em banca de Hugo André Klauck', '2019-01-01', 'Qualificações de Doutorado'),
    ('BANC-00005', 'Participação em banca de Marcio Bystronski', 'Uma proposta para integração de sistemas computacionais jurídicos de diferentes esferas jurisdicionais', '2013-01-01', 'Monografias de cursos de aperfeiçoamento/especialização');

INSERT INTO formacao(codigo, nome, dataInicio, dataFim, tipo) VALUES 
    ('FORM-00001', 'Doutorado em Biotecnologia', '2008-01-01', '2012-01-01', 'Doutorado'),
    ('FORM-00002', 'Mestrado em Computação', '1998-01-01', '2000-01-01', 'Mestrado'),
    ('FORM-00003', 'Especialização em MBA em Gestão do Ensino Superior', '2017-01-01', '2019-01-01', 'Especialização'),
    ('FORM-00004', 'Graduação em Bacharelado em Ciência da Computação', '1992-01-01', '1997-01-01', 'Bacharelado'),
    ('FORM-00005', 'Pós-doutorado', '2018-01-01', '2019-01-01', 'Pós-doutorado'),
    ('FORM-00006', 'Graduação em Bacharelado em Ciência da Computação', '2020-01-01', null, 'Bacharelado'),
    ('FORM-00007', 'Graduação em Bacharelado em Ciência da Computação', '2013-01-01', null, 'Bacharelado');

INSERT INTO atuacao(codigo, nome, dataInicio, dataFim, tipo) VALUES 
    ('ATUA-00001', 'Doutor Adjunto I', '2000-01-01', null, 'Professor'),
    ('ATUA-00002', 'Bolsista', '1996-01-01', '1998-01-01', 'Bolsista IC Cnpq'),
    ('ATUA-00003', 'Bacharelado em Ciência da Computaçã', '2023-03-01', null, 'Ensino'),
    ('ATUA-00004', 'Bacharelado em Ciência da Computação', '2022-08-01', '2022-12-01', 'Ensino'),
    ('ATUA-00005', 'Conselhos', '2016-03-01', '2022-02-01', 'Conselhos');

INSERT INTO instituicao(codigo, nome) VALUES 
	('INST-00001', 'UCS'),
    ('INST-00002', 'IFRS'),
    ('INST-00003', 'UFRGS'),
    ('INST-00004', 'PUC'),
    ('INST-00005', 'USP');

INSERT INTO endereco(codigo, cidade, bairro, numero, estado, cep) VALUES 
    ('ENDE-00001', 'Caxias do Sul', 'Vila Cristina', '1130', 'RS', '95070560'),
    ('ENDE-00002', 'Vacaria', 'Barcellos', '2800 ', 'RS', '95206364'),
    ('ENDE-00003', 'Porto Alegre', 'Cidade Baixa', '110', 'RS', '90046900'),
    ('ENDE-00004', 'São Paulo', 'Butantã', '1280', 'SP', '05508900'),
    ('ENDE-00005', 'Porto Alegre', 'Partenon', '4088', 'RS', '90610060');

INSERT INTO orgao_regulamentador(codigo, codigoPatente, codigoEndereco, abangrencia) VALUES
    ('OGRE-00001', 'PATE-00001', 'ENDE-00005', 'Nacional'),
    ('OGRE-00002', 'PATE-00002', 'ENDE-00005', 'Internacional'),
    ('OGRE-00003', 'PATE-00003', 'ENDE-00005', 'Nacional'),
    ('OGRE-00004', 'PATE-00004', 'ENDE-00005', 'Internacional'),
    ('OGRE-00005', 'PATE-00005', 'ENDE-00005', 'Nacional');

-- INSERT INTO CONNECTION TABLES
INSERT INTO pesquisador_producao (cpfPesquisador, codigoProducao, orientador) VALUES 
    ('08094448792', 'PROD-00001', 'Scheila de Avila e Silva'), 
    ('13625365715', 'PROD-00002', 'Daniel Luís Notari'), 
    ('21675077479', 'PROD-00003', 'Scheila de Ávila e Silva'), 
    ('61083713663', 'PROD-00004', 'Daniel Luís Notari'), 
    ('73483759107', 'PROD-00005', 'Iraci Cristina Silveira'), 
    ('08094448792', 'PROD-00002', 'Daniel Luís Notari'), 
    ('08094448792', 'PROD-00003', 'Scheila de Ávila e Silva'), 
    ('73483759107', 'PROD-00004', 'Daniel Luís Notari');

INSERT INTO pesquisador_evento (cpfPesquisador, codigoEvento) VALUES 
    ('08094448792', 'EVEN-00001'), 
    ('08094448792', 'EVEN-00002'), 
    ('61083713663', 'EVEN-00003'), 
    ('73483759107', 'EVEN-00004'), 
    ('08094448792', 'EVEN-00005'), 
    ('13625365715', 'EVEN-00003'), 
    ('21675077479', 'EVEN-00003'), 
    ('13625365715', 'EVEN-00001'), 
    ('21675077479', 'EVEN-00004'), 
    ('73483759107', 'EVEN-00005'), 
    ('73483759107', 'EVEN-00002');

INSERT INTO pesquisador_patente (cpfPesquisador, codigoPatente) VALUES 
    ('61083713663', 'PATE-00001'), 
    ('13625365715', 'PATE-00001'), 
    ('08094448792', 'PATE-00002'), 
    ('61083713663', 'PATE-00002'), 
    ('21675077479', 'PATE-00002'), 
    ('61083713663', 'PATE-00003'), 
    ('73483759107', 'PATE-00004'), 
    ('73483759107', 'PATE-00005');

INSERT INTO pesquisador_projeto (cpfPesquisador, codigoProjeto, orientador) VALUES 
    ('08094448792', 'PROJ-00001', 'Scheila de Avila e Silva'), 
    ('13625365715', 'PROJ-00002', 'Diego Silva'), 
    ('13625365715', 'PROJ-00003', 'Iraci Cristina Silveira'), 
    ('21675077479', 'PROJ-00004', 'Iraci Cristina Silveira'), 
    ('73483759107', 'PROJ-00004', 'Diego Silva');

INSERT INTO pesquisador_banca (cpfPesquisador, codigoBanca) VALUES 
    ('61083713663', 'BANC-00001'), 
    ('61083713663', 'BANC-00002'), 
    ('13625365715', 'BANC-00002'), 
    ('21675077479', 'BANC-00003'), 
    ('73483759107', 'BANC-00004'), 
    ('08094448792', 'BANC-00005');

INSERT INTO pesquisador_formacao (cpfPesquisador, codigoFormacao) VALUES 
    ('61083713663', 'FORM-00001'),
    ('61083713663', 'FORM-00002'),
    ('61083713663', 'FORM-00004'),
    ('61083713663', 'FORM-00005'),
    ('21675077479', 'FORM-00006'),
    ('13625365715', 'FORM-00003'),
    ('13625365715', 'FORM-00007');

INSERT INTO pesquisador_atuacao (cpfPesquisador, codigoAtuacao) VALUES 
    ('08094448792', 'ATUA-00002'), 
    ('21675077479', 'ATUA-00005'), 
    ('13625365715', 'ATUA-00003'), 
    ('73483759107', 'ATUA-00001'), 
    ('61083713663', 'ATUA-00004');

INSERT INTO instituicao_banca (codigoInstituicao, codigoBanca) VALUES 
    ('INST-00001', 'BANC-00002'),
    ('INST-00001', 'BANC-00001'),
    ('INST-00003', 'BANC-00003'),
    ('INST-00004', 'BANC-00004'),
    ('INST-00002', 'BANC-00005');

INSERT INTO instituicao_formacao (codigoInstituicao, codigoFormacao) VALUES 
    ('INST-00002', 'FORM-00001'),
    ('INST-00001', 'FORM-00002'),
    ('INST-00001', 'FORM-00003'),
    ('INST-00001', 'FORM-00004'),
    ('INST-00005', 'FORM-00005');

INSERT INTO instituicao_atuacao (codigoInstituicao, codigoAtuacao) VALUES 
    ('INST-00001', 'ATUA-00001'),
    ('INST-00002', 'ATUA-00002'),
    ('INST-00003', 'ATUA-00003'),
    ('INST-00002', 'ATUA-00004'),
    ('INST-00005', 'ATUA-00005');

INSERT INTO instituicao_endereco (codigoInstituicao, codigoEndereco) VALUES 
    ('INST-00001', 'ENDE-00001'),
    ('INST-00001', 'ENDE-00002'),
    ('INST-00003', 'ENDE-00003'),
    ('INST-00004', 'ENDE-00004');
