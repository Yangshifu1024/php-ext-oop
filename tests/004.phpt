--TEST--
Check for object handler
--SKIPIF--
<?php include('skipif.inc'); ?>
--FILE--
<?php

use OOP\Object;

$obj = new Object;
var_dump($obj->toString());
var_dump($obj->toArray());
?>
--EXPECT--
string(0) ""
array(0) {
}

