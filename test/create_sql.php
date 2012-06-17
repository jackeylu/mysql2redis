<?php

$table="test2";

$f = fopen("insert.sql","wb");
fwrite($f,"use test;\n");
foreach(range(1,100000) as $i)
{

	$sql = "insert into $table values($i,$i);\n";
	fwrite($f,$sql);
}
fclose($f);

?>

