A=lib/libanimation.a
AR=ar rcs
CC=gcc -Wall
CFLAGS=-Iinclude `allegro-config --cflags`
EXE=example
MKDIR=mkdir -p
OBJDIR=obj
LIBS=-Llib `allegro-config --libs` -lanimation -lldpng -lpng -lz
RM=rm -fR

.PHONY: clean default

default: clean ${OBJDIR} ${A} ${EXE}

clean:
	${RM} ${A} ${EXE} ${OBJDIR}

 ${A}: ${OBJDIR}/animation.o
	${AR} $@ $?

${EXE}: ${OBJDIR}/main.o
	${CC} -o $@ $? ${LIBS}

${OBJDIR}:
	${MKDIR} $@

${OBJDIR}/animation.o: src/animation.c include/animation.h
	${CC} -c ${CFLAGS} -o $@ $<

${OBJDIR}/main.o: src/main.c
	${CC} -c ${CFLAGS} -o $@ $<

