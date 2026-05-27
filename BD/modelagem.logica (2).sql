CREATE TABLE `CLIENTE` (
  `id_cliente` int PRIMARY KEY,
  `nome` varchar(255),
  `telefone` varchar(255)
);

CREATE TABLE `PRODUTO` (
  `id_produto` int PRIMARY KEY,
  `nome` varchar(255),
  `categoria` varchar(255),
  `preco` decimal
);

CREATE TABLE `FORNECEDOR` (
  `id_fornecedor` int PRIMARY KEY,
  `nome` varchar(255),
  `cnpj` varchar(255)
);

CREATE TABLE `USUARIO` (
  `id_usuario` int PRIMARY KEY,
  `nome` varchar(255),
  `email` varchar(255),
  `senha` varchar(255),
  `tipo` varchar(255)
);

CREATE TABLE `PEDIDO` (
  `id_pedido` int PRIMARY KEY,
  `data` date,
  `status` varchar(255),
  `id_cliente` int
);

CREATE TABLE `ITEM_PEDIDO` (
  `id_item` int PRIMARY KEY,
  `quantidade` int,
  `preco_unitario` decimal,
  `id_pedido` int,
  `id_produto` int
);

CREATE TABLE `FORNECEDOR_PRODUTO` (
  `id_fornecedor` int,
  `id_produto` int,
  PRIMARY KEY (`id_fornecedor`, `id_produto`)
);

CREATE TABLE `ENTRADA` (
  `id_entrada` int PRIMARY KEY,
  `data` date,
  `quantidade` int,
  `id_fornecedor` int,
  `id_produto` int,
  `id_usuario` int
);

CREATE TABLE `SAIDA` (
  `id_saida` int PRIMARY KEY,
  `data` date,
  `quantidade` int,
  `id_produto` int,
  `id_usuario` int
);

ALTER TABLE `PEDIDO` ADD FOREIGN KEY (`id_cliente`) REFERENCES `CLIENTE` (`id_cliente`);

ALTER TABLE `ITEM_PEDIDO` ADD FOREIGN KEY (`id_pedido`) REFERENCES `PEDIDO` (`id_pedido`);

ALTER TABLE `ITEM_PEDIDO` ADD FOREIGN KEY (`id_produto`) REFERENCES `PRODUTO` (`id_produto`);

ALTER TABLE `FORNECEDOR_PRODUTO` ADD FOREIGN KEY (`id_fornecedor`) REFERENCES `FORNECEDOR` (`id_fornecedor`);

ALTER TABLE `FORNECEDOR_PRODUTO` ADD FOREIGN KEY (`id_produto`) REFERENCES `PRODUTO` (`id_produto`);

ALTER TABLE `ENTRADA` ADD FOREIGN KEY (`id_fornecedor`) REFERENCES `FORNECEDOR` (`id_fornecedor`);

ALTER TABLE `ENTRADA` ADD FOREIGN KEY (`id_produto`) REFERENCES `PRODUTO` (`id_produto`);

ALTER TABLE `ENTRADA` ADD FOREIGN KEY (`id_usuario`) REFERENCES `USUARIO` (`id_usuario`);

ALTER TABLE `SAIDA` ADD FOREIGN KEY (`id_produto`) REFERENCES `PRODUTO` (`id_produto`);

ALTER TABLE `SAIDA` ADD FOREIGN KEY (`id_usuario`) REFERENCES `USUARIO` (`id_usuario`);
