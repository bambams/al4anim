AR=ar rcs
BINDIR=bin
CC=gcc -Wall
CFLAGS=-Iinclude `allegro-config --cflags`
CP=cp -i
LIBDIR=lib
MKDIR=mkdir -p
LIBS=-Llib `allegro-config --libs` -lal4anim -lldpng -lpng -lz
OBJDIR=obj
PREFIX=/usr
RM=rm -iR

A=${LIBDIR}/libal4anim.a
EXE=${BINDIR}/example
SO=lib/libal4anim.so

.PHONY: all clean default dirs distclean dynamic example install library static

default: dirs library

all: library example

dirs: ${BINDIR} ${LIBDIR} ${OBJDIR}

distclean:
	if [ -f ${PREFIX}/${A} ]; then ${RM} ${PREFIX}/${A}; fi
	if [ -f ${PREFIX}/${SO} ]; then ${RM} ${PREFIX}/${SO}; fi

dynamic: dirs ${SO}

clean:
	${RM} -f ${BINDIR} ${EXE} ${LIBDIR} ${OBJDIR}

example: dirs ${EXE}

install:
	if [ -f ${A} ]; then ${CP} ${A} ${PREFIX}/lib; fi
	if [ -f ${SO} ]; then ${CP} ${SO} ${PREFIX}/lib; fi

library: dirs static dynamic

static: dirs ${A}

${A}: ${OBJDIR}/a4a_animation.o
	${AR} $@ $?

${BINDIR}:
	${MKDIR} $@

${EXE}: ${OBJDIR}/main.o
	${CC} -o $@ $? ${LIBS}

${LIBDIR}:
	${MKDIR} $@

${OBJDIR}:
	${MKDIR} $@

${OBJDIR}/a4a_animation.o: src/a4a_animation.c include/a4a_animation.h
	${CC} -c ${CFLAGS} -fPIC -o $@ $<

${OBJDIR}/main.o: src/main.c
	${CC} -c ${CFLAGS} -o $@ $<

${SO}: ${OBJDIR}/a4a_animation.o
	${CC} -shared -Wl,-soname,libal4anim.so -o $@ $?

