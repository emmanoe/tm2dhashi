CC = gcc
CFLAGS = -Wall -std=c99 -g
LDFLAGS = -L . -lhashi
AR = ar
ARFLAGS = -r -v
LOBJETS = game.o node.o
SOURCES = hashi_text.c
OBJETS = hashi_text.o
OBJETSTEST = test_game2.c test_toolbox.c
GENERES = hashi_text hashi_text.o libhashi.a test_game2

all : libhashi.a hashi_text test_game2

libhashi.a : $(LOBJETS)
	$(AR) $(ARFLAGS) $@ $^

hashi_text : $(OBJETS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

test_game2 : $(OBJETSTEST) $(OBJETS)
	$(CC) $(CFLAGS) $(OBJETSTEST) -o $@


depends :
	$(CC) $(CFLAGS) -MM $(SOURCES) > dependance.txt

.PHONY : clean test

clean :
	rm -f $(GENERES)

test : test_game2
	./test_game2
