                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#AC_PREREQ([2.64])
AC_INIT([dawn], [0.0.20], [dawn-rpg-bugreports@lists.sourceforge.net])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([GL], [glEnable], [], [
        echo "Cannot locate GL library. You need this for Dawn to work."
        exit -1
        ])
AC_CHECK_LIB([GLU], [gluBuild2DMipmaps], [], [
        echo "Cannot locate GLU library. You need this for Dawn to work."
        exit -1
        ])
AC_CHECK_LIB([SDL], [SDL_Init], [], [
        echo "Cannot locate SDL library. You need this for Dawn to work."
        exit -1
        ])
AC_CHECK_LIB([SDL_image], [IMG_Load], [], [
        echo "Cannot locate SDL_image library. You need this for Dawn to work."
        exit -1
        ])
AC_CHECK_LIB([SDL_mixer], [Mix_PlayMusic], [], [
        echo "Cannot locate SDL_mixer library. You need this for Dawn to work."
        exit -1
        ])
AC_CHECK_LIB([freetype], [FT_New_Memory_Face], [], [
        echo "Cannot locate freetype library. You need this for Dawn to work."
        exit -1
        ])
AC_CHECK_LIB([glut], [glutSwapBuffers], [], [
        echo "Cannot locate glut library. You need this for Dawn to work."
        exit -1
])
AC_CHECK_LIB([z], [gzsetparams], [], [
        echo "Cannot locate zlib library. You need this for Dawn to work."
        exit -1
])
AC_CHECK_LIB([pthread], [pthread_create], [], [
        echo "Cannot locate pthread library. You need this for Dawn to work."
        exit -1
])
AC_SEARCH_LIBS([luaL_newstate], [lua lua5.1], [], [
        echo "Cannot locate lua5.1 library. You need this for Dawn to work."
        exit -1
	],
	[-lm]
)

AC_SEARCH_LIBS([tolua_open], [tolua++5.1 tolua++], [], [
        echo "Cannot locate tolua++ library. You need this for Dawn to work."
        exit -1
	],
	[-lm]
)


# Checks for header files.
AC_CHECK_HEADERS([zlib.h stddef.h stdint.h stdlib.h string.h tolua++ SDL/SDL.h SDL/SDL_mixer.h SDL/SDL_opengl.h SDL/SDL_image.h GL/gl.h /usr/include/ft2build.h GL/glu.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([atexit floor memset pow putenv sqrt strcspn strspn])

AC_OUTPUT(Makefile)

