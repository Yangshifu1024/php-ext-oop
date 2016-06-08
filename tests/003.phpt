--TEST--
Check for ini entry function
--SKIPIF--
<?php include('skipif.inc'); ?>
--INI--
oop.allow_override=yes
--FILE--
<?php
var_dump(ini_get("oop.allow_override"));
?>
--EXPECT--
string(1) "1"

