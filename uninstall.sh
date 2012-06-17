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

echo "uninstall the MySQL UDF plugin lib_mysqludf_redis"
cd src/
make uninstall

if test $? -ne 0; then
	echo "uninstalled error"
	exit 1
else
	echo "MySQL UDF uninstalled successfully"
fi

cd ../
echo -e "\nPlease provide your MySQL root password"

mysql -u root -p mysql < lib_mysqludf_redis_drop.sql

if test $? -ne 0; then
	echo "ERROR: unable to uninstall the UDF"
	exit 1
else
	echo "MySQL UDF uninstalled successfully"
fi
