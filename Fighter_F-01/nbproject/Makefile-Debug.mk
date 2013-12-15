#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Bullet.o \
	${OBJECTDIR}/Enemy.o \
	${OBJECTDIR}/Explosion.o \
	${OBJECTDIR}/Fighter.o \
	${OBJECTDIR}/FloatRect.o \
	${OBJECTDIR}/calculations.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs SDL_image` `pkg-config --libs SDL_mixer` `pkg-config --libs sdl` -lSDL_ttf  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fighter_f-01

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fighter_f-01: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fighter_f-01 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Bullet.o: Bullet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags sdl`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Bullet.o Bullet.cpp

${OBJECTDIR}/Enemy.o: Enemy.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags sdl`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Enemy.o Enemy.cpp

${OBJECTDIR}/Explosion.o: Explosion.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags sdl`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Explosion.o Explosion.cpp

${OBJECTDIR}/Fighter.o: Fighter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags sdl`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Fighter.o Fighter.cpp

${OBJECTDIR}/FloatRect.o: FloatRect.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags sdl`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FloatRect.o FloatRect.cpp

${OBJECTDIR}/calculations.o: calculations.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags sdl`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations.o calculations.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags sdl`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fighter_f-01

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
