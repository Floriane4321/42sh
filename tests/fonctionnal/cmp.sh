#!/bin/bash

VAR="/tmp/test."
echo "what num:"
read NUM

RES="$VAR$NUM"
MY="$RES/mysh.out"
TC="$RES/tcsh.out"

echo "/////// 42sh"
cat $MY

echo "/////// tcsh"
cat $TC

echo "////difff"


diff $MY $TC
