<?php

$table="test2";
$host="127.0.0.1";
$port=6379;


$f = fopen("query.sql","wb");
fwrite($f,"use test;\n");
foreach(range(1,30000) as $i)
{

	$sql = "select redis_command(\"$host\",$port,". "\"set foo:$i bar\");\n";
	fwrite($f,$sql);
}
fclose($f);

?>

