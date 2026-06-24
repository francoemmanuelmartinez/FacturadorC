-- MySQL dump 10.13  Distrib 8.0.46, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: comercial
-- ------------------------------------------------------
-- Server version	9.7.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
SET @MYSQLDUMP_TEMP_LOG_BIN = @@SESSION.SQL_LOG_BIN;
SET @@SESSION.SQL_LOG_BIN= 0;

--
-- GTID state at the beginning of the backup 
--

SET @@GLOBAL.GTID_PURGED=/*!80000 '+'*/ '58ff34c9-4d08-11f1-ae22-00d861db1593:1-178';

--
-- Table structure for table `clientes`
--

DROP TABLE IF EXISTS `clientes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `clientes` (
  `id` int NOT NULL AUTO_INCREMENT,
  `nombre` varchar(100) NOT NULL,
  `apellido` varchar(100) NOT NULL,
  `dni` varchar(20) NOT NULL,
  `telefono` varchar(20) DEFAULT NULL,
  `direccion` varchar(255) DEFAULT NULL,
  `mail` varchar(100) NOT NULL,
  `habilitado` int DEFAULT '1',
  PRIMARY KEY (`id`),
  UNIQUE KEY `mail` (`mail`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `clientes`
--

LOCK TABLES `clientes` WRITE;
/*!40000 ALTER TABLE `clientes` DISABLE KEYS */;
INSERT INTO `clientes` VALUES (1,'Cliente','NPCa','1','2231234511','Direccion 1','cliente1@mail.com',1),(2,'Cliente','NPCb','a','2230987654','Direccion 2','cliente2@mail.com',1),(3,'Cliente','NPCc','3','33333333333','Direcccion 3','cliente3@mail.com',1),(4,'122222','12','adw','ad','a','a@a.com',1),(5,'12','333','aaa','vvv','assa1212','aaa@bb.com',1);
/*!40000 ALTER TABLE `clientes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `detalles_de_facturas`
--

DROP TABLE IF EXISTS `detalles_de_facturas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `detalles_de_facturas` (
  `id` int NOT NULL AUTO_INCREMENT,
  `id_factura` int NOT NULL,
  `id_producto` int NOT NULL,
  `cantidad` int NOT NULL,
  `precio_unitario` decimal(10,2) NOT NULL DEFAULT '0.00',
  `descuento` int DEFAULT '0',
  `subtotal` decimal(10,2) NOT NULL DEFAULT '0.00',
  PRIMARY KEY (`id`),
  KEY `id_factura` (`id_factura`),
  KEY `id_producto` (`id_producto`),
  CONSTRAINT `detalles_de_facturas_ibfk_1` FOREIGN KEY (`id_factura`) REFERENCES `facturas` (`id`) ON DELETE CASCADE,
  CONSTRAINT `detalles_de_facturas_ibfk_2` FOREIGN KEY (`id_producto`) REFERENCES `productos` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `detalles_de_facturas`
--

LOCK TABLES `detalles_de_facturas` WRITE;
/*!40000 ALTER TABLE `detalles_de_facturas` DISABLE KEYS */;
INSERT INTO `detalles_de_facturas` VALUES (1,1,4,2,1000.00,10,1800.00),(2,1,5,7,800.00,0,5600.00),(3,2,4,3,1000.00,0,3000.00),(4,2,6,1,3000.00,20,2400.00),(5,2,1,1,2000.00,0,2000.00),(6,3,4,2,1000.00,10,1800.00),(7,3,2,10,1700.00,20,13600.00),(8,4,2,1,1000.00,20,800.00),(9,4,2,20,1000.00,10,18000.00),(10,5,2,11,1000.00,0,11000.00),(11,6,5,5,800.00,0,4000.00);
/*!40000 ALTER TABLE `detalles_de_facturas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `facturas`
--

DROP TABLE IF EXISTS `facturas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `facturas` (
  `id` int NOT NULL AUTO_INCREMENT,
  `numero_factura` varchar(50) NOT NULL,
  `id_cliente` int NOT NULL,
  `nombre_cliente` varchar(100) NOT NULL DEFAULT '',
  `apellido_cliente` varchar(100) NOT NULL DEFAULT '',
  `id_vendedor` int NOT NULL,
  `nombre_vendedor` varchar(100) NOT NULL DEFAULT '',
  `apellido_vendedor` varchar(100) NOT NULL DEFAULT '',
  `fecha_emision` date NOT NULL,
  `subtotal` decimal(10,2) NOT NULL DEFAULT '0.00',
  `descuento_porcentaje` int NOT NULL DEFAULT '0',
  `valor_descontado` decimal(10,2) NOT NULL DEFAULT '0.00',
  `total_compra` decimal(10,2) NOT NULL DEFAULT '0.00',
  PRIMARY KEY (`id`),
  KEY `id_cliente` (`id_cliente`),
  KEY `id_vendedor` (`id_vendedor`),
  CONSTRAINT `facturas_ibfk_1` FOREIGN KEY (`id_cliente`) REFERENCES `clientes` (`id`),
  CONSTRAINT `facturas_ibfk_2` FOREIGN KEY (`id_vendedor`) REFERENCES `usuarios` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `facturas`
--

LOCK TABLES `facturas` WRITE;
/*!40000 ALTER TABLE `facturas` DISABLE KEYS */;
INSERT INTO `facturas` VALUES (1,'FACT-20260616-043952',2,'Cliente','NPCb',5,'Pardo','Parden','2026-06-16',7400.00,0,0.00,7400.00),(2,'FACT-20260616-071151',1,'Cliente','NPCa',6,'Cajera','NPCa','2026-06-16',7400.00,25,1850.00,5550.00),(3,'FACT-20260616-093552',3,'Cliente','NPCc',5,'Pardo','Parden','2026-06-16',15400.00,35,5390.00,10010.00),(4,'FACT-20260617-182127',2,'Cliente','NPCb',5,'Pardo','Parden','2026-06-17',18800.00,35,6580.00,12220.00),(5,'FACT-20260624-130727',3,'Cliente','NPCc',5,'Pardo','Parden','2026-06-24',11000.00,50,5500.00,5500.00),(6,'FACT-20260624-134951',3,'Cliente','NPCc',5,'Pardo','Parden','2026-06-24',4000.00,44,1760.00,2240.00);
/*!40000 ALTER TABLE `facturas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `productos`
--

DROP TABLE IF EXISTS `productos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `productos` (
  `id` int NOT NULL AUTO_INCREMENT,
  `descripcion` varchar(255) NOT NULL,
  `precio` decimal(10,2) NOT NULL DEFAULT '0.00',
  `stock` int NOT NULL,
  `id_proveedor` int DEFAULT NULL,
  `habilitado` int DEFAULT '1',
  PRIMARY KEY (`id`),
  KEY `id_proveedor` (`id_proveedor`),
  CONSTRAINT `productos_ibfk_1` FOREIGN KEY (`id_proveedor`) REFERENCES `proveedores` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `productos`
--

LOCK TABLES `productos` WRITE;
/*!40000 ALTER TABLE `productos` DISABLE KEYS */;
INSERT INTO `productos` VALUES (1,'Cereales Skarchitos',2000.00,99,5,1),(2,'Galletas Don Satur',1000.00,8,6,1),(3,'Biscochos Don Satur',1200.00,20,6,1),(4,'Cereales Knorr',1000.00,93,4,1),(5,'Caldos Knorr',800.00,68,4,1),(6,'Chocolate Aguila',3000.00,9,5,1);
/*!40000 ALTER TABLE `productos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `proveedores`
--

DROP TABLE IF EXISTS `proveedores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `proveedores` (
  `id` int NOT NULL AUTO_INCREMENT,
  `nombre` varchar(100) DEFAULT NULL,
  `direccion` varchar(150) DEFAULT NULL,
  `telefono` varchar(30) DEFAULT NULL,
  `mail` varchar(60) NOT NULL,
  `habilitado` int DEFAULT '1',
  PRIMARY KEY (`id`),
  UNIQUE KEY `mail` (`mail`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `proveedores`
--

LOCK TABLES `proveedores` WRITE;
/*!40000 ALTER TABLE `proveedores` DISABLE KEYS */;
INSERT INTO `proveedores` VALUES (1,'Cereales S.A.','Calle 2','2231010101','cereales1@mail.com',1),(2,'Galletitas S.A.','Calle1','2232020202','galletitas1@mail.com',1),(3,'Chocolates S.A','Calle 33','2233030303','chocholates1@mail.com',1),(4,'Knorr','Calle 4','2234040404','knorr@mail.com',1),(5,'Arcor','Calle 5','2235050505','arcor@mail.com',1),(6,'Don Satur','Calle 6','2236060606','donsatur@mail.com',1);
/*!40000 ALTER TABLE `proveedores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `usuarios`
--

DROP TABLE IF EXISTS `usuarios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `usuarios` (
  `id` int NOT NULL AUTO_INCREMENT,
  `nombre` varchar(100) DEFAULT NULL,
  `apellido` varchar(100) DEFAULT NULL,
  `dni` varchar(10) DEFAULT NULL,
  `telefono` varchar(30) DEFAULT NULL,
  `direccion` varchar(150) DEFAULT NULL,
  `mail` varchar(60) NOT NULL,
  `rol` varchar(20) DEFAULT NULL,
  `password` varchar(20) DEFAULT NULL,
  `habilitado` int DEFAULT '1',
  PRIMARY KEY (`id`),
  UNIQUE KEY `mail` (`mail`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `usuarios`
--

LOCK TABLES `usuarios` WRITE;
/*!40000 ALTER TABLE `usuarios` DISABLE KEYS */;
INSERT INTO `usuarios` VALUES (5,'Pardo','Parden','37030738','2235024735','Diagonal Canata 2695','pardo@mail.com','Administrador','admin1',1),(6,'Cajera','NPCa','1','1','A','cajero1@mail.com','Cajero','cajero1',1),(7,'Deposito','NPCb','2','2','B','deposito1@mail.com','Deposito','deposito1',1),(8,'Cajero','NPCc','3','3','C','cajero2@mail.com','Cajero','cajero2',1),(9,'Admin','NoMeRompasNicoo','12345678','223478967','Calle 123','admin2@mail.com','Administrador','123456',1),(10,'Admin','PorSiLasDudas','9876542','224786532','Calle 2000','admin3@mail.com','Administrador','123456',1),(11,'Depo','NPCz','3098765','22365748','Calle 24','depo@mail.com','Deposito','deposito',1);
/*!40000 ALTER TABLE `usuarios` ENABLE KEYS */;
UNLOCK TABLES;
SET @@SESSION.SQL_LOG_BIN = @MYSQLDUMP_TEMP_LOG_BIN;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2026-06-24 15:08:31
