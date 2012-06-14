PLUGINDIR=`/usr/bin/mysql_config --plugindir`
INCLUDE=`/usr/bin/mysql_config --include` -I/usr/local/include
LIBS=-lhiredis

install:
	gcc -Werror -O2 $(INCLUDE) -I. -fPIC -shared lib_mysqludf_redis.c \
		$(LIBS) -o $(PLUGINDIR)/lib_mysqludf_redis.so

uninstall:
	rm -f $(PLUGINDIR)/lib_mysqludf_redis.so

clean:
	rm -f *~
	rm -f *.so
	rm -f *.out
