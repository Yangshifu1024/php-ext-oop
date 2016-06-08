<?php
if (substr(PHP_OS, 0, 3) == "WIN") {
    die("Skipped: Not compatible with Windows.");
}
if (!extension_loaded("oop")) {
    die("Skipped: Extension not loaded.");
}
?>
