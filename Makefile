CC = gcc
CFLAGS = -Wall -std=c99 -g
LDFLAGS = -L . -lhashi
AR = ar
ARFLAGS = -r -v
LOBJETS = game.o node.o
SOURCES = hashi_text.c
OBJETS = hashi_text.o
GENERES = hashi_text hashi_text.o libhashi.a test_game2

all : libhashi.a hashi_text test_game2

libhashi.a : $(LOBJETS)
	$(AR) $(ARFLAGS) $@ $^

hashi_text : $(OBJETS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

test_game2 :
	gcc -std=c99 -Wall -g test_game2.c game.o node.o test_toolbox.c -o test_game2

depends :
	$(CC) $(CFLAGS) -MM $(SOURCES)

.PHONY : clean

clean :
	rm -f $(GENERES)
