#!/bin/bash

# This script will help us to keep track of all art in Dawn.
# Running this script checks for any new files that are not 
# listed in AssetsLicenceInventory.txt
# Currently searches for *.tga or *.ogg

FILES=$(find data/ -name "*.tga" -o -name "*.ogg")

# setting the internal field seperator to newline
IFS=$'\n'

# our filecounter, just to display dots that we are working.
filecounter=0

for filename in ${FILES}
do
	# just a visual aid to show us that the program is searching. adds a dot every 200 files.
	let filecounter=filecounter+1
	if [ $filecounter -gt 200 ]; then
		echo -n "."
		let filecounter=0
	fi
	
	# we see if the file is listed in our AssetsLicenceInventory.txt, if not we add it and warn the user about it.
	findfile=`cat AssetsLicenceInventory.txt | grep "$filename"`
	if [ -z "$findfile" ]; then 
		echo -e "\n$filename isn't listed in AssetsLicenceInventory.txt."
		echo "Make sure you document the licence and the source of this file"
		echo "$filename" >> AssetsLicenceInventory.txt
	fi
done
