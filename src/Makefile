# Manual Compile process this makefile is based on
# (Works on Ubuntu Jaunty, lua is often installed differently on 
#    other distros)
#
# g++ -c *.cpp -I/usr/include/GL -I/usr/include/freetype2 -I/usr/include/lua5.1
# g++ -o dawn *.o -lSDL -lSDL_image -lGL -llua5.1 -ltolua++5.1 -lfreetype -lglut
#
CC=g++
LIBS= -lSDL -lSDL_image -lGL -lglut -llua5.1 -ltolua++5.1 -lfreetype -lglut
CCFLAGS= -I/usr/include/GL -I/usr/include/freetype2 -I/usr/include/lua5.1
SRCDIR= src/


all: dawn-rpg

clean: 
	rm *.o


dawn-rpg: main debug GLFT_Font CZone CMessage CInterface CTexture CSpell CAction CCharacter CEditor cameraFocusHandler CLuaInterfaceGenerated CLuaFunctions
	$(CC) $(CCFLAGS) -o dawn-rpg main.o debug.o GLFT_Font.o CZone.o CMessage.o CInterface.o CTexture.o CSpell.o CAction.o CCharacter.o CEditor.o cameraFocusHandler.o CLuaInterfaceGenerated.o CLuaFunctions.o $(LIBS) 

main: main.cpp
	$(CC) $(CCFLAGS) -c main.cpp

cameraFocusHandler: cameraFocusHandler.cpp
	$(CC) $(CCFLAGS) -c cameraFocusHandler.cpp

CAction: CAction.cpp
	$(CC) $(CCFLAGS) -c CAction.cpp

CCharacter: CCharacter.cpp
	$(CC) $(CCFLAGS) -c CCharacter.cpp

CSpell: CSpell.cpp
	$(CC) $(CCFLAGS) -c CSpell.cpp

CEditor: CEditor.cpp
	$(CC) $(CCFLAGS) -c CEditor.cpp

CLuaFunctions: CLuaFunctions.cpp
	$(CC) $(CCFLAGS) -c CLuaFunctions.cpp

CLuaInterfaceGenerated: CLuaInterfaceGenerated.cpp
	$(CC) $(CCFLAGS) -c CLuaInterfaceGenerated.cpp

CTexture: CTexture.cpp
	$(CC) $(CCFLAGS) -c CTexture.cpp

CInterface: CInterface.cpp
	$(CC) $(CCFLAGS) -c CInterface.cpp

CMessage: CMessage.cpp
	$(CC) $(CCFLAGS) -c CMessage.cpp

CZone: CZone.cpp
	$(CC) $(CCFLAGS) -c CZone.cpp

GLFT_Font: GLFT_Font.cpp
	$(CC) $(CCFLAGS) -c GLFT_Font.cpp

debug: debug.cpp
	$(CC) $(CCFLAGS) -c debug.cpp

