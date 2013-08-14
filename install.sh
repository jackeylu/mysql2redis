#!/bin/bash
# lib_mysqludf_redis - a library with redis  functions
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

echo "Compiling the MySQL UDF"
cd src/
make

if test $? -ne 0; then
	echo "ERROR: You need libmysqlclient development software installed "
	echo "to be able to compile this UDF, on Debian/Ubuntu just run:"
	echo "apt-get install libmysqlclient15-dev"
	exit 1
else
	echo "MySQL UDF compiled successfully"
fi

echo -e "\nPlease provide your MySQL root password"
read pwd
echo -e "\nThe password for MySQL root your inputed is $pwd\n"

cd ../
mysql -u root -p$pwd mysql < lib_mysqludf_redis.sql

if test $? -ne 0; then
	echo "ERROR: unable to install the UDF"
	echo "Check the enviroment path of redis, hiredis, mysql and mysql-plugin"
	exit 1
else
	echo "MySQL UDF installed successfully"
fi
