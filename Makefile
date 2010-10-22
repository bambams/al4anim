A=lib/libal4anim.a
AR=ar rcs
CC=gcc -Wall
CFLAGS=-Iinclude `allegro-config --cflags`
EXE=example
LIBDIR=lib
MKDIR=mkdir -p
OBJDIR=obj
LIBS=-Llib `allegro-config --libs` -lal4anim -lldpng -lpng -lz
RM=rm -fR

.PHONY: clean default dirs library

default: dirs library ${EXE}

dirs: ${LIBDIR} ${OBJDIR}

clean:
	${RM} ${EXE} ${LIBDIR} ${OBJDIR}

library: dirs ${A}

${A}: ${OBJDIR}/animation.o
	${AR} $@ $?

${EXE}: ${OBJDIR}/main.o
	${CC} -o $@ $? ${LIBS}

${LIBDIR}:
	${MKDIR} $@

${OBJDIR}:
	${MKDIR} $@

${OBJDIR}/animation.o: src/animation.c include/animation.h
	${CC} -c ${CFLAGS} -o $@ $<

${OBJDIR}/main.o: src/main.c
	${CC} -c ${CFLAGS} -o $@ $<

