[MySQL2Redis][]
===============

This is a [user-defined function (UDF) ][UDF] plugin for MySQL, which can
provide some [redis][Redis] command support function
to push data from MySQL to Redis.

[UDF]: http://dev.mysql.com/doc/refman/5.1/en/adding-functions.html
[Redis]: http://redis.io/

Requirements
------------

1. [MySQL2Redis][mysql2reids] is built with [HiRedis][hiredis].
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

Support
-------

You may ask for help and discuss various other issues on
the ... and report bugs on the [bug tracker][].

[bug tracker]: http://github.com/jackeylu/mysql2redis/issues


