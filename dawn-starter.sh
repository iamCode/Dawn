#!/bin/bash

if [ ! -e `dirname $0`/dawn-rpg ]
then
	echo "Could not find file `dirname $0`/dawn-rpg. Please compile dawn first using 'cd `dirname $0` && ./configure && make'."
	exit 1
fi

pushd `dirname $0`
./dawn-rpg "$@" | ./errorparser.sh
popd > /dev/null

