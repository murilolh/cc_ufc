# SQL Manager 2010 Lite for MySQL 4.5.1.3
# ---------------------------------------
# Host     : localhost
# Port     : 3306
# Database : hotel


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES latin1 */;

SET FOREIGN_KEY_CHECKS=0;

CREATE DATABASE `hotel`
    CHARACTER SET 'latin1'
    COLLATE 'latin1_swedish_ci';

USE `hotel`;

#
# Structure for the `apartmenttype` table : 
#

CREATE TABLE `apartmenttype` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(20) NOT NULL,
  `description` text,
  `bed` int(11) DEFAULT NULL,
  `price` double(6,2) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

#
# Structure for the `apartment` table : 
#

CREATE TABLE `apartment` (
  `number` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `floor` int(11) NOT NULL,
  `status` int(11) NOT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`),
  KEY `type` (`type`),
  CONSTRAINT `apartment_fk` FOREIGN KEY (`type`) REFERENCES `apartmenttype` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=latin1;

#
# Structure for the `person` table : 
#

CREATE TABLE `person` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `cpf` varchar(20) DEFAULT NULL,
  `dateofbirth` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=40 DEFAULT CHARSET=latin1 AVG_ROW_LENGTH=2340;

#
# Structure for the `client` table : 
#

CREATE TABLE `client` (
  `clientid` int(11) NOT NULL,
  `login` varchar(10) DEFAULT NULL,
  `password` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`clientid`),
  UNIQUE KEY `login` (`login`),
  CONSTRAINT `client_fk` FOREIGN KEY (`clientid`) REFERENCES `person` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

#
# Structure for the `check` table : 
#

CREATE TABLE `check` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `clientid` int(11) NOT NULL,
  `apartmentid` int(11) NOT NULL,
  `datebegin` datetime NOT NULL,
  `status` int(11) NOT NULL,
  `dateend` datetime DEFAULT NULL,
  `value` double(6,3) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `check_apartment_fk` (`apartmentid`),
  KEY `clientid` (`clientid`),
  CONSTRAINT `check_apartment_fk` FOREIGN KEY (`apartmentid`) REFERENCES `apartment` (`id`),
  CONSTRAINT `check_client_fk` FOREIGN KEY (`clientid`) REFERENCES `client` (`clientid`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;

#
# Structure for the `employee` table : 
#

CREATE TABLE `employee` (
  `employeeid` int(11) NOT NULL,
  `login` varchar(10) NOT NULL,
  `password` varchar(10) NOT NULL,
  `type` int(11) NOT NULL,
  PRIMARY KEY (`employeeid`),
  UNIQUE KEY `login` (`login`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

#
# Structure for the `service` table : 
#

CREATE TABLE `service` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `price` double(6,2) DEFAULT NULL,
  `name` varchar(20) NOT NULL,
  `description` text,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;

#
# Structure for the `expense` table : 
#

CREATE TABLE `expense` (
  `id` int(11) NOT NULL,
  `date` datetime DEFAULT NULL,
  `serviceid` int(11) NOT NULL,
  `checkid` int(11) NOT NULL,
  `value` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `expense_fk` (`serviceid`),
  KEY `expense_fk1` (`checkid`),
  CONSTRAINT `expense_fk` FOREIGN KEY (`serviceid`) REFERENCES `service` (`id`),
  CONSTRAINT `expense_fk1` FOREIGN KEY (`checkid`) REFERENCES `check` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

#
# Structure for the `hotel` table : 
#

CREATE TABLE `hotel` (
  `name` varchar(20) NOT NULL,
  `address` text,
  `logo` varchar(50) DEFAULT NULL,
  `description` text,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

#
# Data for the `apartmenttype` table  (LIMIT 0,500)
#

INSERT INTO `apartmenttype` (`id`, `name`, `description`, `bed`, `price`) VALUES 
  (1,'Normal','Apartamento comum com 1 Tv e 1 Banheiro',1,20.00),
  (2,'Econômico','Apartamento simples com ventilador e 1 banheiro',1,10.00),
  (3,'Luxuoso','Apartamento de luxo com Tv, Dvd, Frigobar',2,50.00);
COMMIT;

#
# Data for the `apartment` table  (LIMIT 0,500)
#

INSERT INTO `apartment` (`number`, `type`, `floor`, `status`, `id`) VALUES 
  (3,3,1,1,22),
  (2,1,1,1,27),
  (1,2,1,1,28);
COMMIT;

#
# Data for the `person` table  (LIMIT 0,500)
#

INSERT INTO `person` (`id`, `name`, `cpf`, `dateofbirth`) VALUES 
  (5,'ggg','213','2222-11-11 11:11:11'),
  (16,'testete','123132','1985-11-21 00:00:00'),
  (17,'teae','12313213','1985-11-21 00:00:00'),
  (19,'afsdasdf','123123123','1985-11-21 00:00:00'),
  (27,'Rafael de Lima','004.339.063-32','1985-11-21 00:00:00'),
  (33,'Paulo Alves',NULL,'1987-04-03 00:00:00'),
  (34,'Murilo de Holanda','444.302.646-00','1990-11-05 00:00:00'),
  (38,'Murilo de Holanda','004.339.063-32','1985-11-21 00:00:00'),
  (39,'Leandro Monteiro',NULL,'1985-03-02 00:00:00');
COMMIT;

#
# Data for the `client` table  (LIMIT 0,500)
#

INSERT INTO `client` (`clientid`, `login`, `password`) VALUES 
  (33,'paulo','p'),
  (38,'murilo','m'),
  (39,'leandro','l');
COMMIT;

#
# Data for the `check` table  (LIMIT 0,500)
#

INSERT INTO `check` (`id`, `clientid`, `apartmentid`, `datebegin`, `status`, `dateend`, `value`) VALUES 
  (4,39,28,'2010-05-25 11:59:00',0,'2010-05-25 11:59:00',0.000);
COMMIT;

#
# Data for the `employee` table  (LIMIT 0,500)
#

INSERT INTO `employee` (`employeeid`, `login`, `password`, `type`) VALUES 
  (27,'Rafael','a',3),
  (34,'murilo','m',2);
COMMIT;

#
# Data for the `service` table  (LIMIT 0,500)
#

INSERT INTO `service` (`id`, `price`, `name`, `description`) VALUES 
  (1,2.00,'agua de coco','copo 200ml\r\n'),
  (4,3.40,'vodka','bebida asdasd'),
  (6,1.25,'coca cola','refrigerante 2L\r\n');
COMMIT;

#
# Data for the `hotel` table  (LIMIT 0,500)
#

INSERT INTO `hotel` (`name`, `address`, `logo`, `description`) VALUES 
  ('Plaza Caldas Hotel','University Avenue, 2635 Fortaleza - CE, Brazil\r\n','../../Content/Images/hotel.PNG','Live the pleasure to be here');
COMMIT;



/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;