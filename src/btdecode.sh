#!/bin/bash

while read LINE
do
	`echo $LINE | sed 's/\([^ \t(]*\).*\[\(.*\)\].*$/addr2line -e \1 -f -C -i \2/'`
done

