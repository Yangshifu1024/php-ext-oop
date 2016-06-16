<?php

namespace OOP;

/**
 * Class: String
 *
 * @see Object
 */
class String extends Object {

    /**
     * Get the string length
     *
     * @example $string = "string"; $string->length(); int(6);
     *
     * @return int
     */
    public function length();

    /**
     * Build printable string
     *
     * @return string
     */
    public function toString();

    /**
     * Split string to single chars.
     *
     * @example $string = "string"; $string->toArray(); ['s', 't', 'r', 'i', 'n', 'g']
     *
     * @return array
     */
    public function toArray();

    /**
     * Slice string like `substr`
     *
     * @param int $offset
     * @param int|NULL $length
     *
     * @example $string = "string"; $string->slice(2, 3); string(3) "rin"
     *
     * @return string
     */
    public function slice($offset, $length = NULL);
}
