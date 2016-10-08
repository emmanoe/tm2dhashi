CC = gcc
CFLAGS = -Wall -std=c99 -g
LDFLAGS = -L . -lhashi
AR = ar
ARFLAGS = -r -v
LOBJETS = game.o node.o
SOURCES = hashi_text.c
OBJETS = hashi_text.o
GENERES = hashi_text hashi_text.o libhashi.a

all : libhashi.a hashi_text

libhashi.a : $(LOBJETS)
	$(AR) $(ARFLAGS) $@ $^

hashi_text : $(OBJETS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

depends :
	$(CC) $(CFLAGS) -MM $(SOURCES)

.PHONY : clean

clean :
	rm -f $(GENERES)
