# do not check for files README, TODO, etc
AUTOMAKE_OPTIONS = foreign

INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/threadObject -I$(top_srcdir)/GLee -I/usr/include/freetype2 -I/usr/include/GL -I/usr/include/lua5.1
# LDADD = -lSDL -lSDL_image -lGL -llua5.1 -ltolua++5.1 -lfreetype -lglut -lGLU -lSDL_mixer


bin_PROGRAMS = dawn-rpg

# if configure is run with --with-testsuite we also need to build the testsuite program
if TESTSUITE
    bin_PROGRAMS += testsuite
    testsuite_SOURCES = tests/testsuite.cpp tests/testsuite.h
endif

#todo: Data should be installed in $(pkgdatadir) which is .../share/dawn
dawndatadir = $(bindir)/data


dawn_rpg_SOURCES = src/a_star.cpp \
	src/a_star.h \
	src/actionbar.cpp \
	src/actionbar.h \
	src/buffwindow.cpp \
	src/buffwindow.h \
	src/callindirection.cpp \
	src/callindirection.h \
	src/camerafocushandler.cpp \
	src/camerafocushandler.h \
	src/character.cpp \
	src/character.h \
	src/direction.h \
	src/drawinghelpers.h \
	src/editor.cpp \
	src/editor.h \
	src/characterinfoscreen.cpp \
	src/characterinfoscreen.h \
	src/interface.cpp \
	src/interface.h \
	src/luafunctions.cpp \
	src/luafunctions.h \
	src/luainterfacegenerated.cpp \
	src/luainterfacegenerated.h \
	src/luainterface.h \
	src/magic.h \
	src/magic.cpp \
	src/message.cpp \
	src/message.h \
	src/npc.cpp \
	src/npc.h \
	src/commonsounds.cpp \
	src/commonsounds.h \
	src/configurableframe.h \
	src/configurableframe.cpp \
	src/configuredframes.h \
	src/configuredframes.cpp \
	src/configuration.cpp \
	src/configuration.h \
	src/controlelement.h \
	src/controlelement.cpp \
	src/spell.cpp \
	src/spell.h \
	src/texture.cpp \
	src/texture.h \
	src/zone.cpp \
	src/zone.h \
	src/dawnstate.h \
	src/dawnstate.cpp \
	src/debug.cpp \
	src/debug.h \
	src/elements.cpp \
	src/elements.h \
	src/frames.h \
	src/frames.cpp \
	src/framesbase.cpp \
	src/framesbase.h \
	src/fontcache.cpp \
	src/fontcache.h \
	src/gameloophandler.h \
	src/gameloophandler.cpp \
	src/GLFT_Font.cpp \
	src/GLFT_Font.h \
	src/globals.cpp \
	src/globals.h \
	src/groundloot.cpp \
	src/groundloot.h \
	src/interactionpoint.cpp \
	src/interactionpoint.h \
	src/interactionregion.cpp \
	src/interactionregion.h \
	src/inventory.cpp \
	src/inventory.h \
	src/inventoryscreen.cpp \
	src/inventoryscreen.h \
	src/item.cpp \
	src/item.h \
	src/loadingmanager.h \
	src/loadingscreen.cpp \
	src/loadingscreen.h \
	src/logwindow.cpp \
	src/logwindow.h \
	src/main.cpp \
	src/musiccache.cpp \
	src/musiccache.h \
	src/optionswindow.cpp \
	src/optionswindow.h \
	src/player.cpp \
	src/player.h \
	src/quest.cpp \
	src/quest.h \
	src/questwindow.cpp \
	src/questwindow.h \
	src/random.cpp \
	src/random.h \
	src/resolution.cpp \
	src/resolution.h \
	src/shop.cpp \
	src/shop.h \
	src/soundengine.cpp \
	src/soundengine.h \
	src/spellbook.cpp \
	src/spellbook.h \
	src/stats.h \
	src/statssystem.cpp \
	src/statssystem.h \
	src/testinterface.cpp \
	src/testinterface.h \
	src/textureframe.h \
	src/textwindow.cpp \
	src/textwindow.h \
	src/tileset.cpp \
	src/tileset.h \
	src/timeconverterhelper.h \
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
