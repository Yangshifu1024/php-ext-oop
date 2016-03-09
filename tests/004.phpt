--TEST--
Check for object handler
--SKIPIF--
<?php if (!extension_loaded("full_objects")) print "skip"; ?>
--FILE--
<?php

use FullObjects\Object;

$obj = new Object;
var_dump($obj->toString());
var_dump($obj->toArray());
?>
--EXPECT--
string(0) ""
array(0) {
}

