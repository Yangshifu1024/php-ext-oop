--TEST--
Check for register_oop_handler function
--SKIPIF--
<?php include('skipif.inc'); ?>
--INI--
oop.allow_override=yes
--FILE--
<?php
class Test {}
$type = "string";
var_dump(register_oop_handler($type, Test::class));
?>
--EXPECT--
string(4) "Test"

