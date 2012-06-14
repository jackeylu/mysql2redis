PLUGINDIR=`/usr/bin/mysql_config --plugindir`
INCLUDE=`/usr/bin/mysql_config --include`


install:
	gcc -Wall -I$(INCLUDE) -I. -fPIC -shared lib_mysqludf_redis.c -o $(PLUGINDIR)/lib_mysqludf_redis.so
