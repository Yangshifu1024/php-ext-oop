--TEST--
Check for register_full_objects_handler function
--SKIPIF--
<?php if (!extension_loaded("full_objects")) print "skip"; ?>
--INI--
full_objects.allow_override=yes
--FILE--
<?php
class Test {}
$type = "string";
var_dump(register_full_objects_handler($type, Test::class));
?>
--EXPECT--
string(4) "Test"

