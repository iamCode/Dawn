#!/bin/bash
PARSEMODE=0
while read LINE
do
	if [ $PARSEMODE -eq 1 -o "${LINE:2:8}" = 'btdecode' ]
	then
		PARSEMODE=1
		ERRORLINES="$ERRORLINES\n$LINE"
		if [ "${LINE:0:4}" = "EOBT" ]
		then
			PARSEMODE=2
		fi
	else
		echo $LINE
	fi
done

if [ $PARSEMODE -eq 2 ]
then
	# found a backtrace
	echo "converting the following backtrace:"
	echo
	echo -e "$ERRORLINES"
	echo
	echo "We are sorry, your game of dawn crashed."
	echo
	echo "To help us debug the problem and make dawn more stable, give the following lines to the developers of dawn, please."
	echo "The developers of dawn can be reached via dawn-rpg-bugreport@lists.sourceforge.net."
	echo "If possible add some text what you were doing when the game crashed or how the crash can be reproduced."
	echo "Try to add the last line of the previous output (something from before 'converting the following backtrace') as well."
	echo
	echo "Thank you very much for your help!"
	echo
	echo "converted backtrace:"
	echo
	echo -e "$ERRORLINES" | sh
fi

