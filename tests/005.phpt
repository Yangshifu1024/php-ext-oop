--TEST--
Check for string handler
--SKIPIF--
<?php if (!extension_loaded("full_objects")) print "skip"; ?>
--FILE--
<?php
$string = "string";
var_dump($string->toString());
var_dump($string->toArray());
var_dump($string->length());
var_dump($string->slice(2, 3));
var_dump($string->slice(-2, 3));
var_dump($string->slice(2));
var_dump($string->slice(-6));
var_dump($string->slice(7));
?>
--EXPECT--
string(6) "string"
array(6) {
  [0]=>
  string(1) "s"
  [1]=>
  string(1) "t"
  [2]=>
  string(1) "r"
  [3]=>
  string(1) "i"
  [4]=>
  string(1) "n"
  [5]=>
  string(1) "g"
}
int(6)
string(3) "rin"
string(2) "ng"
string(4) "ring"
string(6) "string"
bool(false)
