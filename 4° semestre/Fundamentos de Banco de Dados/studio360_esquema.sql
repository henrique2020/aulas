CREATE TABLE estado (
  id int NOT NULL,
  nome varchar(50) DEFAULT NULL,
  uf char(2) DEFAULT NULL,
  PRIMARY KEY (id)
);

CREATE TABLE cidade (
  id int not null,
  nome varchar(100) DEFAULT NULL,
  estado_id int NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (estado_id) REFERENCES estado (id) ON DELETE CASCADE
);

CREATE TABLE bairro (
  id int not null,
  status int DEFAULT '1',
  nome varchar(255) NOT NULL DEFAULT '0',
  cidade_id int NOT NULL DEFAULT '0',
  created_at timestamp NOT NULL,
  updated_at timestamp NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (cidade_id) REFERENCES cidade (id) ON DELETE CASCADE 
);

CREATE TABLE corretor (
  id int not null,
  user_id int DEFAULT NULL,
  cidade_id int DEFAULT NULL,
  updated_at timestamp NULL DEFAULT NULL,
  created_at timestamp NULL DEFAULT NULL,
  deleted_at timestamp NULL DEFAULT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (cidade_id) REFERENCES cidade (id) ON DELETE CASCADE
);

CREATE TABLE empreendimento (
  id int,
  incorporadora_id int NOT NULL,
  status int DEFAULT '1',
  data_entrega date DEFAULT NULL,
  latitude varchar(255),
  longitude varchar(255),
  aluguel int DEFAULT '0',
  bairro_id int DEFAULT NULL,
  cidade_id int DEFAULT NULL,
  updated_at timestamp NULL DEFAULT NULL,
  created_at timestamp NULL DEFAULT NULL,
  deleted_at timestamp NULL DEFAULT NULL,
  PRIMARY KEY (id)
  --FOREIGN KEY (bairro_id) REFERENCES bairro (id) ON DELETE CASCADE,
  --FOREIGN KEY (cidade_id) REFERENCES cidade (id) ON DELETE CASCADE  
);

CREATE TABLE incorporadora (
  id int NOT NULL,
  cidade_id int DEFAULT NULL,
  status int DEFAULT '1',
  updated_at timestamp NULL DEFAULT NULL,
  created_at timestamp NULL DEFAULT NULL,
  deleted_at timestamp NULL DEFAULT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (cidade_id) REFERENCES cidade (id)
);

CREATE TABLE users (
  id int NOT NULL,
  created_at timestamp NULL DEFAULT NULL,
  PRIMARY KEY (id),
  UNIQUE (id)
);

CREATE TABLE tipo_planta (
  id int NOT NULL,
  nome varchar(255) DEFAULT NULL,
  tipo int DEFAULT NULL,
  PRIMARY KEY (id)
);	

CREATE TABLE empreendimento_acessos (
  empreendimento_id int DEFAULT NULL,
  user_id int DEFAULT NULL,
  data timestamp DEFAULT NULL,
  sequencia  serial, 
  created_at timestamp DEFAULT NULL,
  updated_at timestamp DEFAULT NULL,
  primary key (empreendimento_id, user_id, data, sequencia),
  FOREIGN KEY (empreendimento_id) REFERENCES empreendimento (id) ON DELETE CASCADE
  --FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE
);

CREATE TABLE empreendimento_andamento_obra (
  id int NOT NULL,
  sequencial serial, 
  empreendimento_id int DEFAULT NULL,
  andamento varchar(100) DEFAULT NULL,
  status int DEFAULT '0',
  created_at timestamp NULL DEFAULT NULL,
  updated_at timestamp NULL DEFAULT NULL,
  deleted_at timestamp NULL DEFAULT NULL,
  PRIMARY KEY (id, sequencial),
  FOREIGN KEY (empreendimento_id) REFERENCES empreendimento (id) ON DELETE CASCADE
);

CREATE TABLE empreendimento_planta (
  id int NOT NULL,
  empreendimento_id int NOT NULL,
  descricao varchar(255) DEFAULT NULL,
  dormitorios int DEFAULT '0',
  tipo int DEFAULT NULL,
  suites int DEFAULT '0',
  banheiros int DEFAULT '0',
  area_privativa decimal(14,2) DEFAULT '0.00',
  area_total decimal(14,2) DEFAULT '0.00',
  area_util decimal(14,2) DEFAULT '0.00',
  area_terreno decimal(14,2) DEFAULT '0.00',
  informacoes varchar,
  valor decimal(14,2) DEFAULT '0.00',
  valor_aluguel decimal(14,2) DEFAULT '0.00',
  lavabos int DEFAULT '0',
  elevadores int DEFAULT '0',
  suites_master int DEFAULT '0',
  vagas int DEFAULT '0',
  updated_at timestamp NULL DEFAULT NULL,
  created_at timestamp NULL DEFAULT NULL,
  deleted_at timestamp NULL DEFAULT NULL,
  PRIMARY KEY (id,empreendimento_id),
  FOREIGN KEY (empreendimento_id) REFERENCES empreendimento (id) ON DELETE CASCADE
);

CREATE TABLE empreendimento_planta_posicao_solar (
  id int NOT NULL,
  empreendimento_planta_id int,
  posicao char(2) DEFAULT NULL,
  updated_at timestamp NULL DEFAULT NULL,
  created_at timestamp NULL DEFAULT NULL,
  PRIMARY KEY (id)
  --FOREIGN KEY (empreendimento_planta_id) REFERENCES empreendimento_planta (id ) ON DELETE CASCADE
);

CREATE TABLE empreendimento_tabela_venda (
  id int NOT NULL,
  unidade varchar(50) DEFAULT NULL,
  valor_reforco_anual decimal(14,2) DEFAULT NULL,
  empreendimento_id int DEFAULT NULL,
  grupo_id int DEFAULT NULL,
  sort int NOT NULL DEFAULT '5000',
  status int NOT NULL,
  valor decimal(14,2) DEFAULT NULL,
  valor_parcela decimal(14,2) DEFAULT NULL,
  entrada decimal(14,2) DEFAULT NULL,
  entrada_porcentagem int DEFAULT NULL,
  ato varchar(255) DEFAULT NULL,
  parcelas int DEFAULT NULL,
  tipo varchar(255) DEFAULT NULL,
  posicao_solar varchar(255) DEFAULT NULL,
  reforco_anual decimal(12,2) DEFAULT NULL,
  qtd_reforco_anual int DEFAULT NULL,
  area_total decimal(14,2) DEFAULT NULL,
  area_privativa decimal(14,2) DEFAULT NULL,
  area_box decimal(14,2) DEFAULT NULL,
  area_uso_comum decimal(14,2) DEFAULT NULL,
  box varchar(50) DEFAULT NULL,
  tipologia varchar(50) DEFAULT NULL,
  suite varchar(50) DEFAULT NULL,
  dormitorios varchar(50) DEFAULT NULL,
  garagem varchar(50) DEFAULT NULL,
  fase varchar(255) DEFAULT NULL,
  casa varchar(255) DEFAULT NULL,
  incc varchar(255) DEFAULT NULL,
  conceito varchar,
  bloco varchar(255) DEFAULT NULL,
  ato_porcentagem int DEFAULT NULL,
  area_apartamento decimal(14,2) DEFAULT NULL,
  na_entrega decimal(14,2) DEFAULT NULL,
  andar varchar(255) DEFAULT NULL,
  area_lote decimal(14,2) DEFAULT NULL,
  saldo_financiado decimal(14,2) DEFAULT NULL,
  reforco_semestral_qtd int DEFAULT NULL,
  reforco_semestral_r decimal(14,2) DEFAULT NULL,
  v10_reforco decimal(14,2) DEFAULT NULL,
  v20_reforco decimal(14,2) DEFAULT NULL,
  v30_reforco decimal(14,2) DEFAULT NULL,
  v40_reforco decimal(14,2) DEFAULT NULL,
  desconto_promocional int DEFAULT NULL,
  desconto_promocional_r decimal(14,2) DEFAULT NULL,
  valor_do_condominio_r decimal(14,2) DEFAULT NULL,
  quadra varchar(100) DEFAULT NULL,
  lote varchar(100) DEFAULT '',
  localizacao varchar(100) DEFAULT NULL,
  tipo_box varchar(100) DEFAULT NULL,
  varanda decimal(14,2) DEFAULT NULL,
  deposito int DEFAULT NULL,
  lancamento int DEFAULT NULL,
  lancamento_r decimal(14,2) DEFAULT NULL,
  valor_m2 decimal(14,2) DEFAULT NULL,
  tabela_investidor decimal(14,2) DEFAULT NULL,
  v6_anuais decimal(14,2) DEFAULT NULL,
  mobiliado_e_decorado varchar(100) DEFAULT NULL,
  condominio decimal(14,2) DEFAULT NULL,
  pavimento varchar(100) DEFAULT NULL,
  valor_avaliacao decimal(14,2) DEFAULT NULL,
  financiamento decimal(14,2) DEFAULT NULL,
  etapa varchar(100) DEFAULT NULL,
  arras decimal(14,2) DEFAULT NULL,
  desconto_promocional_20 int DEFAULT NULL,
  vaga varchar(100) DEFAULT NULL,
  frente_unidade varchar(100) DEFAULT NULL,
  reforco_semestral int DEFAULT NULL,
  iptu_r decimal(14,2) DEFAULT NULL,
  dezembro_2021_10 decimal(14,2) DEFAULT NULL,
  v12_meses_13 decimal(14,2) DEFAULT NULL,
  numero int DEFAULT NULL,
  area_do_garden decimal(14,2) DEFAULT NULL,
  garden decimal(14,2) DEFAULT NULL,
  matricula varchar(100) DEFAULT NULL,
  valor_investidor decimal(14,2) DEFAULT NULL,
  valor_locacao decimal(14,2) DEFAULT NULL,
  v5_reforco decimal(14,2) DEFAULT NULL,
  v6_reforco decimal(14,2) DEFAULT NULL,
  valor_box decimal(14,2) DEFAULT NULL,
  valor_total decimal(14,2) DEFAULT NULL,
  chaves decimal(14,2) DEFAULT NULL,
  v36x_mensais decimal(14,2) DEFAULT NULL,
  entrada_de_50 decimal(14,2) DEFAULT NULL,
  vaga_extra decimal(14,2) DEFAULT NULL,
  v20_na_assinatura_do_contrato varchar(100) DEFAULT NULL,
  patio int DEFAULT NULL,
  desconto_para_pagamento_a_vista_7 varchar(100) DEFAULT NULL,
  condicao_de_pagamento_1 varchar(100) DEFAULT NULL,
  condicao_de_pagamento_2 varchar(100) DEFAULT NULL,
  banheiro int DEFAULT NULL,
  lavabo int DEFAULT NULL,
  sacada varchar(100) DEFAULT NULL,
  precos_em_ate_36x_10_de_entrada decimal(14,2) DEFAULT NULL,
  precos_em_ate_72x_v20_de_entrada decimal(14,2) DEFAULT NULL,
  ato_em_3_x decimal(14,2) DEFAULT NULL,
  v24x_fixacub decimal(14,2) DEFAULT NULL,
  v30_x_mensais decimal(14,2) DEFAULT NULL,
  entrada_de_10_a_20 int DEFAULT NULL,
  saldo_em_ate_42x_com_reforcos_semestrais varchar(100) DEFAULT NULL,
  capital_int int DEFAULT NULL,
  area_privativa_box_m2 decimal(14,2) DEFAULT NULL,
  entrada_15_ato_ou_4x decimal(14,2) DEFAULT NULL,
  parcelas_72x decimal(14,2) DEFAULT NULL,
  corretor varchar(100) DEFAULT NULL,
  desconto_a_vista_20 decimal(14,2) DEFAULT NULL,
  v20_de_entrada decimal(14,2) DEFAULT NULL,
  a_vista_20_de_desconto decimal(14,2) DEFAULT NULL,
  reforco_3x decimal(14,2) DEFAULT NULL,
  desconto decimal(14,2) DEFAULT NULL,
  v20_ato_ou_4x decimal(14,2) DEFAULT NULL,
  v60x_parc_mensais decimal(14,2) DEFAULT NULL,
  v05_ref_anuais_marco decimal(14,2) DEFAULT NULL,
  area_total_apto_box decimal(14,2) DEFAULT NULL,
  area_uso_comum_apto decimal(14,2) DEFAULT NULL,
  area_uso_comum_box decimal(14,2) DEFAULT NULL,
  avaliacao_caixa_para_simulacao decimal(14,2) DEFAULT NULL,
  entrada_10 decimal(14,2) DEFAULT NULL,
  terraco decimal(14,2) DEFAULT NULL,
  baloes_sugeridos int DEFAULT NULL,
  baloes_sugeridos_r decimal(14,2) DEFAULT NULL,
  v30_de_entrada decimal(14,2) DEFAULT NULL,
  v48_parcelas decimal(14,2) DEFAULT NULL,
  desconto_promocional_10 decimal(14,2) DEFAULT NULL,
  desconto_promocional_12 decimal(14,2) DEFAULT NULL,
  v24x_mensais decimal(14,2) DEFAULT NULL,
  saldofinanc decimal(14,2) DEFAULT NULL,
  parcelas_mensais_37x decimal(14,2) DEFAULT NULL,
  parcelas_anuais_3x decimal(14,2) DEFAULT NULL,
  parcelas_anuais_4x decimal(14,2) DEFAULT NULL,
  parcelas_mensais_55x decimal(14,2) DEFAULT NULL,
  valor_promocional decimal(14,2) DEFAULT NULL,
  saldo_em_60x decimal(14,2) DEFAULT NULL,
  v20_entrada_em_3x varchar(100) DEFAULT NULL,
  area_garagem_m2 decimal(14,2) DEFAULT NULL,
  box_duplo int DEFAULT NULL,
  box_duplo_m2 decimal(14,2) DEFAULT NULL,
  area_box_duplo decimal(14,2) DEFAULT NULL,
  cohapar varchar(100) DEFAULT NULL,
  sequencia int DEFAULT NULL,
  area_garden_m2 decimal(14,2) DEFAULT NULL,
  v30_entrada_ato3x decimal(14,2) DEFAULT NULL,
  v40_parcelamento_ate_72x decimal(14,2) DEFAULT NULL,
  v30_0v6_reforcos_anuais decimal(14,2) DEFAULT NULL,
  v30_parcelas decimal(14,2) DEFAULT NULL,
  descricao varchar(100) DEFAULT NULL,
  floreira varchar(100) DEFAULT NULL,
  reforco int DEFAULT NULL,
  reforco_r decimal(14,2) DEFAULT NULL,
  instalacoes decimal(14,2) DEFAULT NULL,
  v02_reforcos_dez22_e_jun23 decimal(14,2) DEFAULT NULL,
  v03_reforcos_dez22_jun23_dez23 decimal(14,2) DEFAULT NULL,
  parcelas_mensais_60x decimal(14,2) DEFAULT NULL,
  avaliacao_cef int DEFAULT NULL,
  v40_entrada decimal(14,2) DEFAULT NULL,
  valor_a_prazo_sem_dacao decimal(14,2) DEFAULT NULL,
  a_vista_ou_financiamento_bancario decimal(14,2) DEFAULT NULL,
  dacaotroca varchar(100) DEFAULT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (empreendimento_id) REFERENCES empreendimento (id) ON DELETE CASCADE
);

CREATE TABLE empreendimento_tabela_venda_grupo (
  id int NOT NULL,
  empreendimento_id int NOT NULL,
  slug varchar(100) NOT NULL DEFAULT '',
  name varchar(100) NOT NULL DEFAULT '',
  created_at timestamp NOT NULL,
  updated_at timestamp NOT NULL,
  PRIMARY KEY (id)
  --FOREIGN KEY (empreendimento_id) REFERENCES empreendimento (id) ON DELETE CASCADE
);

CREATE TABLE tabela_venda_campos (
  id int NOT NULL,
  slug varchar(100) NOT NULL DEFAULT '',
  name varchar(100) NOT NULL DEFAULT '',
  input_type varchar(20) NOT NULL DEFAULT '',
  vdefault int NOT NULL DEFAULT '0',
  created_at timestamp NOT NULL,
  updated_at timestamp NOT NULL,
  PRIMARY KEY (id)
);

CREATE TABLE incorporadora_has_cidade (
  cidade_id int DEFAULT NULL,
  incorporadora_id int DEFAULT NULL,
  FOREIGN KEY (cidade_id) REFERENCES cidade (id) ON DELETE CASCADE,
  FOREIGN KEY (incorporadora_id) REFERENCES incorporadora (id) ON DELETE CASCADE
);

CREATE TABLE user_enterprise_share (
  id int NOT NULL,
  user_id int NOT NULL,
  enterprise_id int NOT NULL,
  receive_notification int DEFAULT '0',
  status char NOT NULL DEFAULT 'I',
  created_at timestamp NOT NULL,
  deleted_at timestamp NULL DEFAULT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE
);

CREATE TABLE user_enterprise_share_access (
  id int NOT NULL,
  user_enterprise_share_id int NOT NULL,
  created_at timestamp NOT NULL,
  updated_at timestamp NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (user_enterprise_share_id) REFERENCES user_enterprise_share (id) ON DELETE CASCADE
);

CREATE TABLE user_has_cidades_atuacao (
  user_id int NOT NULL,
  cidade_id int DEFAULT NULL,
  UNIQUE (user_id,cidade_id),
  FOREIGN KEY (cidade_id) REFERENCES cidade (id) ON DELETE CASCADE
  --FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE
);