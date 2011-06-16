#!/bin/sh

cd ../src

if [ "$1" = "--with-testsuite" ]; then
	foundstr=`grep "CLuaTestInterface.pkg" CLuaInterface.pkg`
	if [ "$foundstr" = "" ]; then
		echo "\$pfile \"CLuaTestInterface.pkg\"" >> CLuaInterface.pkg
	fi
fi

tolua++5.1 -o CLuaInterfaceGenerated.cpp -H CLuaInterfaceGenerated.h CLuaInterface.pkg
cd ../scripts
