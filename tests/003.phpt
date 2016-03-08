--TEST--
Check for ini entry function
--SKIPIF--
<?php if (!extension_loaded("full_objects")) print "skip"; ?>
--INI--
full_objects.allow_override=yes
--FILE--
<?php
var_dump(ini_get("full_objects.allow_override"));
?>
--EXPECT--
string(1) "1"

