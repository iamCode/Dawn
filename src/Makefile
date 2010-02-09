# Manual Compile process this makefile is based on
# (Works on Ubuntu Jaunty, lua is often installed differently on 
#    other distros)
#
# g++ -c *.cpp -I/usr/include/GL -I/usr/include/freetype2 -I/usr/include/lua5.1
# g++ -o dawn *.o -lSDL -lSDL_image -lGL -llua5.1 -ltolua++5.1 -lfreetype -llibglut
#
CC=g++
LIBS= -lSDL -lSDL_image -lGL -llua5.1 -ltolua++5.1 -lfreetype -lglut -lGLU
CCFLAGS= -I/usr/include/GL -I/usr/include/freetype2 -I/usr/include/lua5.1 -IthreadObject
SRCDIR= src/


all: dawn-rpg

clean: 
	rm *.o


dawn-rpg: main debug CharacterInfoScreen inventory GLFT_Font CZone utils CMessage CInterface CTexture CSpell CAction CCharacter CEditor cameraFocusHandler CLuaInterfaceGenerated CLuaFunctions item StatsSystem Player CNPC tooltip Spellbook ActionBar InventoryScreen optionswindow interactionpoint elements callindirection BuffWindow questwindow textwindow loadingscreen EventClass MutexClass Thread
	$(CC) $(CCFLAGS) -o dawn-rpg main.o inventory.o CharacterInfoScreen.o utils.o debug.o GLFT_Font.o CZone.o CMessage.o CInterface.o CTexture.o CSpell.o CAction.o CCharacter.o CEditor.o cameraFocusHandler.o CLuaInterfaceGenerated.o CLuaFunctions.o item.o StatsSystem.o Player.o CNPC.o tooltip.o ActionBar.o Spellbook.o InventoryScreen.o optionswindow.o interactionpoint.o elements.o callindirection.o BuffWindow.o questwindow.o textwindow.o loadingscreen.o EventClass.o MutexClass.o Thread.o $(LIBS) 

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

utils: utils.cpp
	$(CC) $(CCFLAGS) -c utils.cpp

CInterface: CInterface.cpp
	$(CC) $(CCFLAGS) -c CInterface.cpp

CMessage: CMessage.cpp
	$(CC) $(CCFLAGS) -c CMessage.cpp

CZone: CZone.cpp
	$(CC) $(CCFLAGS) -c CZone.cpp

GLFT_Font: GLFT_Font.cpp
	$(CC) $(CCFLAGS) -c GLFT_Font.cpp

CharacterInfoScreen: CharacterInfoScreen.cpp
	$(CC) $(CCFLAGS) -c CharacterInfoScreen.cpp 

inventory: inventory.cpp
	$(CC) $(CCFLAGS) -c inventory.cpp

StatsSystem : StatsSystem.cpp
	$(CC) $(CCFLAGS) -c StatsSystem.cpp

item: item.cpp
	$(CC) $(CCFLAGS) -c item.cpp

tooltip: tooltip.cpp
	$(CC) $(CCFLAGS) -c tooltip.cpp

Player: Player.cpp
	$(CC) $(CCFLAGS) -c Player.cpp

CNPC: CNPC.cpp
	$(CC) $(CCFLAGS) -c CNPC.cpp

Spellbook: Spellbook.cpp
	$(CC) $(CCFLAGS) -c Spellbook.cpp

ActionBar: ActionBar.cpp
	$(CC) $(CCFLAGS) -c ActionBar.cpp

InventoryScreen: InventoryScreen.cpp
	$(CC) $(CCFLAGS) -c InventoryScreen.cpp

debug: debug.cpp
	$(CC) $(CCFLAGS) -c debug.cpp

optionswindow: optionswindow.cpp
	$(CC) $(CCFLAGS) -c optionswindow.cpp

textwindow: textwindow.cpp
	$(CC) $(CCFLAGS) -c textwindow.cpp

interactionpoint: interactionpoint.cpp
	$(CC) $(CCFLAGS) -c interactionpoint.cpp

elements: elements.cpp
	$(CC) $(CCFLAGS) -c elements.cpp

callindirection: callindirection.cpp
	$(CC) $(CCFLAGS) -c callindirection.cpp

BuffWindow: BuffWindow.cpp
	$(CC) $(CCFLAGS) -c BuffWindow.cpp

questwindow: questwindow.cpp
	$(CC) $(CCFLAGS) -c questwindow.cpp

loadingscreen: loadingscreen.cpp
	$(CC) $(CCFLAGS) -c loadingscreen.cpp

EventClass: threadObject/EventClass.cpp
	$(CC) $(CCFLAGS) -c threadObject/EventClass.cpp

MutexClass: threadObject/MutexClass.cpp
	$(CC) $(CCFLAGS) -c threadObject/MutexClass.cpp

Thread: threadObject/Thread.cpp
	$(CC) $(CCFLAGS) -c threadObject/Thread.cpp

