use test;

DROP table IF EXISTS test2;

CREATE TABLE test2(a1 INT,a2 INT);

DROP TRIGGER  IF EXISTS test2redisref;

DELIMITER |
create trigger test2redisref BEFORE INSERT on test2
  For EACH ROW BEGIN
DECLARE done INT DEFAULT 999; 
set done = redis_command("127.0.0.1",6379,concat("lpush testkey ",cast(NEW.a1 as CHAR)));
END;
|
DELIMITER ;

