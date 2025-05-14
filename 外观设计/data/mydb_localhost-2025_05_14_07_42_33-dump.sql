-- MySQL dump 10.13  Distrib 8.0.20, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: mydb
-- ------------------------------------------------------
-- Server version	8.0.20

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `menu`
--

DROP TABLE IF EXISTS `menu`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `menu` (
  `dish_id` int NOT NULL,
  `dish_name` varchar(100) DEFAULT NULL,
  `dish_description` varchar(100) DEFAULT NULL,
  `dish_price` decimal(10,2) DEFAULT NULL,
  `stock_quantity` int DEFAULT NULL,
  `category_id` int DEFAULT NULL,
  `category_name` varchar(100) DEFAULT NULL,
  `is_available` tinyint(1) DEFAULT '1',
  `is_recommended` tinyint(1) DEFAULT '1',
  PRIMARY KEY (`dish_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `menu`
--

LOCK TABLES `menu` WRITE;
/*!40000 ALTER TABLE `menu` DISABLE KEYS */;
INSERT INTO `menu` VALUES (1,'宫保鸡丁','花生米与鸡肉丁炒制，甜辣可口',38.00,20,2,'川菜',1,1),(2,'鱼香肉丝','以泡辣椒等调料炒成鱼香味，肉丝鲜嫩',35.00,18,2,'川菜',1,1),(3,'麻婆豆腐','豆腐细嫩，麻辣鲜香烫',22.00,25,2,'川菜',1,1),(4,'糖醋排骨','酸甜口味，外酥里嫩',42.00,15,4,'苏菜',1,1),(5,'松鼠鳜鱼','形似松鼠，外脆里嫩，酸甜适口',128.00,10,4,'苏菜',1,1),(6,'叫花鸡','用荷叶包裹烤制，鸡肉酥烂',88.00,8,4,'苏菜',1,1),(7,'白切鸡','皮黄肉白，肥嫩鲜美',58.00,12,3,'粤菜',1,1),(8,'烧鹅','皮脆肉嫩，肉香浓郁',80.00,10,3,'粤菜',1,1),(9,'肠粉','米浆蒸熟，搭配虾仁等馅料，口感爽滑',20.00,15,3,'粤菜',1,1),(10,'油爆大虾','虾色红润，鲜嫩脆香',68.00,10,1,'鲁菜',1,1),(11,'糖醋鲤鱼','造型优美，外脆里嫩，酸甜适中',58.00,8,1,'鲁菜',1,1),(12,'葱烧海参','葱香浓郁，海参软糯',168.00,6,1,'鲁菜',1,1),(13,'佛跳墙','食材丰富，汤汁浓郁，味极鲜美',288.00,5,5,'闽菜',1,1),(14,'荔枝肉','形似荔枝，酸甜可口',45.00,10,5,'闽菜',1,1),(15,'醉排骨','外酥里嫩，酒香浓郁',50.00,8,5,'闽菜',1,1),(16,'西湖醋鱼','鱼肉鲜嫩，酸甜清香',65.00,8,6,'浙菜',1,1),(17,'东坡肉','红亮晶莹，味醇汁浓，香糯不腻',55.00,10,6,'浙菜',1,1),(18,'龙井虾仁','虾仁鲜嫩，带有龙井茶香',78.00,8,6,'浙菜',1,1),(19,'剁椒鱼头','鱼头鲜嫩，剁椒味浓',78.00,10,7,'湘菜',1,1),(20,'毛氏红烧肉','色泽红亮，甜咸适中，肥而不腻',68.00,10,7,'湘菜',1,1),(21,'辣椒炒肉','家常美味，香辣下饭',40.00,12,7,'湘菜',1,1),(22,'臭鳜鱼','初闻微臭，入口鲜香',88.00,8,8,'徽菜',1,1),(23,'李鸿章大杂烩','食材多样，味道醇厚',78.00,8,8,'徽菜',1,1),(24,'问政山笋','笋质脆嫩，味道清鲜',45.00,10,8,'徽菜',1,1),(25,'梅菜扣肉','肉香与梅菜香融合，肥而不腻',58.00,10,4,'苏菜',1,1),(26,'回锅肉','咸香微辣，肥而不腻',42.00,12,2,'川菜',1,1),(27,'盐焗鸡','皮爽肉滑，骨香味浓',68.00,8,3,'粤菜',1,1),(28,'菠萝咕咾肉','酸甜开胃，肉质外酥里嫩',48.00,10,3,'粤菜',1,1),(29,'扬州炒饭','米饭粒粒分明，配料丰富',35.00,15,4,'苏菜',1,1),(30,'狮子头','肉质鲜嫩，入口即化',65.00,8,4,'苏菜',1,1),(31,'干烧大虾','虾味醇厚，微辣回甜',78.00,8,1,'鲁菜',1,1),(32,'一品豆腐','豆腐软嫩，汤汁鲜美',58.00,8,1,'鲁菜',1,1),(33,'爆炒腰花','腰花脆嫩，味道醇厚',55.00,10,1,'鲁菜',1,1),(34,'蛏子煎蛋','蛋香与蛏子鲜味融合',45.00,10,5,'闽菜',1,1),(35,'沙茶面','面条劲道，沙茶味浓郁',35.00,15,5,'闽菜',1,1),(36,'爆炒双脆','口感脆嫩，鲜香爽口',68.00,8,5,'闽菜',1,1),(37,'宋嫂鱼羹','色泽金黄，鲜嫩滑润，味似蟹肉',58.00,8,6,'浙菜',1,1),(38,'干炸响铃','外皮酥脆，内馅鲜香',48.00,10,6,'浙菜',1,1),(39,'雪菜大黄鱼','鱼肉鲜嫩，雪菜味美',78.00,8,6,'浙菜',1,1),(40,'外婆菜炒肉','外婆菜口感独特，与肉炒制香味十足',45.00,10,7,'湘菜',1,1),(41,'湘西外婆菜','多种野菜腌制而成，味道浓郁',40.00,12,7,'湘菜',1,1),(42,'口味虾','香辣入味，虾尾鲜嫩',88.00,8,7,'湘菜',1,1),(43,'黄山炖鸽','汤汁清鲜，鸽肉酥烂',78.00,8,8,'徽菜',1,1),(44,'香菇炖鸡','鸡肉软烂，香菇入味',68.00,10,8,'徽菜',1,1),(45,'胡氏一品锅','食材层层叠放，味道丰富',88.00,8,8,'徽菜',1,1),(46,'清蒸鲈鱼','鱼肉鲜嫩，原汁原味',68.00,10,4,'苏菜',1,1),(47,'香辣蟹','螃蟹香辣入味，口感鲜美',98.00,8,2,'川菜',1,1),(48,'豉汁蒸排骨','排骨鲜嫩，豉香浓郁',58.00,10,3,'粤菜',1,1),(49,'清炒时蔬','蔬菜新鲜，清淡爽口',28.00,15,4,'苏菜',1,1),(50,'八宝粥','多种谷物熬制，香甜软糯',18.00,20,6,'浙菜',1,1),(51,'John Doe',NULL,NULL,NULL,NULL,NULL,1,1);
/*!40000 ALTER TABLE `menu` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-05-14  7:42:33
