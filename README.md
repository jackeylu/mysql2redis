[MySQL2Redis][]
===============

This is a [user-defined function (UDF) ][UDF] plugin for MySQL, which can
provide some [redis][Redis] command support function
to push data from MySQL to Redis.

This application just test on CentOS 6.2(Final),MySQL Server 5.1 and 5.5.
In a Dell Server PowerEdge R601 (CPU Xeon(R) E5506 * 8, 24GB Memory),
about 3000 calls in a second.

If you want to a thread-able solution, you can try this project of [dawnbreaks].

[UDF]: http://dev.mysql.com/doc/refman/5.1/en/adding-functions.html
[Redis]: http://redis.io/
[dawnbreaks]: https://github.com/dawnbreaks/mysql2redis

Requirements
------------

1. [MySQL2Redis][mysql2redis] is built with [HiRedis][hiredis].
So, you should install the library first.

2. MySQL2Redis is a plugin for MySQL, with the UDF support, so
the MySQL server you used must support this feacture. 
See the [UDF] for more information.

[mysql2redis]: https://github.com/jackeylu/mysql2redis
[hiredis]: https://github.com/antirez/hiredis

Installation
-------------

Use the ./install.sh script.

Test
----

See the test directory.

Uninstallation
--------------

Using the uninstall.sh


Notice
--------------
When you do a lot of redis_command() calling in a short time,
you may get a lot of error like this "Connection error on (xxxx/xxx):
Cannot assign requested address" in the error log of MySQL Server.
And, at the same time, you can see a lot of TIME_WAIT in the netstat command
output.

In this case, you can set the kernel parameters or try to modify the code in
hiredis on socket operation (setsockopt() with SO_REUSEADDR).

  >vi /etc/sysctl.conf
  
  >net.ipv4.tcp_syncookies=1
  
  >net.ipv4.tcp_tw_reuse=1
  
  >net.ipv4.tcp_tw_recycle=1
  

and /sbin/sysctl -p to make it be usefull.


Support
-------

You may ask for help and discuss various other issues on
the ... and report bugs on the [bug tracker][].

[bug tracker]: http://github.com/jackeylu/mysql2redis/issues


