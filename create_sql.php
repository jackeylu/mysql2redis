<?php

$table="test2";

$f = fopen("insert.sql","wb");
fwrite($f,"use test;\n");
foreach(range(0,1000) as $i)
{

	$sql = "insert into $table values($i);\n";
	fwrite($f,$sql);
}
fclose($f);

?>

