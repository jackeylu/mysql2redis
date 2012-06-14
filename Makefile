PLUGINDIR=`/usr/bin/mysql_config --plugindir`
INCLUDE=`/usr/bin/mysql_config --include`


install:
	gcc -Wall -o2 $(INCLUDE) -I. -fPIC -shared lib_mysqludf_redis.c -o $(PLUGINDIR)/lib_mysqludf_redis.so

uninstall:
	rm -f $(PLUGINDIR)/lib_mysqludf_redis.so

clean:
	rm -f *~
	rm -f *.so
	rm -f *.out
