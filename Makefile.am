# do not check for files README, TODO, etc
AUTOMAKE_OPTIONS = foreign

INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/threadObject -I$(top_srcdir)/GLee -I/usr/include/freetype2 -I/usr/include/GL -I/usr/include/lua5.1
# LDADD = -lSDL -lSDL_image -lGL -llua5.1 -ltolua++5.1 -lfreetype -lglut -lGLU


bin_PROGRAMS = dawn_rpg
#todo: Data should be installed in $(pkgdatadir) which is .../share/dawn
dawndatadir = $(bindir)/data
dawn_rpg_SOURCES = src/ActionBar.cpp \
	src/ActionBar.h \
	src/BuffWindow.cpp \
	src/BuffWindow.h \
	src/CAction.cpp \
	src/CAction.h \
	src/callindirection.cpp \
	src/callindirection.h \
	src/cameraFocusHandler.cpp \
	src/cameraFocusHandler.h \
	src/CCharacter.cpp \
	src/CCharacter.h \
	src/CDirection.h \
	src/CDrawingHelpers.h \
	src/CEditor.cpp \
	src/CEditor.h \
	src/CharacterInfoScreen.cpp \
	src/CharacterInfoScreen.h \
	src/CInterface.cpp \
	src/CInterface.h \
	src/CLuaFunctions.cpp \
	src/CLuaFunctions.h \
	src/CLuaInterfaceGenerated.cpp \
	src/CLuaInterfaceGenerated.h \
	src/CLuaInterface.h \
	src/CMessage.cpp \
	src/CMessage.h \
	src/CNPC.cpp \
	src/CNPC.h \
	src/CSpell.cpp \
	src/CSpell.h \
	src/CTexture.cpp \
	src/CTexture.h \
	src/CZone.cpp \
	src/CZone.h \
	src/debug.cpp \
	src/debug.h \
	src/elements.cpp \
	src/elements.h \
	src/fontcache.cpp \
	src/fontcache.h \
	src/GLFT_Font.cpp \
	src/GLFT_Font.h \
	src/interactionpoint.cpp \
	src/interactionpoint.h \
	src/inventory.cpp \
	src/inventory.h \
	src/InventoryScreen.cpp \
	src/InventoryScreen.h \
	src/item.cpp \
	src/item.h \
	src/loadingscreen.cpp \
	src/loadingscreen.h \
	src/main.cpp \
	src/main.h \
	src/optionswindow.cpp \
	src/optionswindow.h \
	src/Player.cpp \
	src/Player.h \
	src/questwindow.cpp \
	src/questwindow.h \
	src/shop.cpp \
	src/shop.h \
	src/Spellbook.cpp \
	src/Spellbook.h \
	src/stats.h \
	src/StatsSystem.cpp \
	src/StatsSystem.h \
	src/textwindow.cpp \
	src/textwindow.h \
	src/TimeConverterHelper.h \
	src/tooltip.cpp \
	src/tooltip.h \
	src/utils.cpp \
	src/utils.h \
	src/GLee/GLee.cpp \
	src/GLee/GLee.h \
	src/pnglite/pnglite.c \
	src/pnglite/pnglite.h \
	src/threadObject/EventClass.cpp \
	src/threadObject/EventClass.h \
	src/threadObject/MutexClass.cpp \
	src/threadObject/MutexClass.h \
	src/threadObject/Thread.cpp \
	src/threadObject/Thread.h

dawndata_DATA = data/spells.lua
