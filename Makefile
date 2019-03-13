CFLAGS = -g -Wall -pedantic
LDFLAGS = ./ftd2xx.lib

SRC = $(wildcard *.c)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(NOM)))

all: ProjetA3.exe

remake: clean ProjetA3.exe

ProjetA3.exe : $(OBJ)
	gcc obj/* $(LDFLAGS) -o $@ 

obj/%.o: %.c
	gcc -c -Iinclude $(CFLAGS) -o $@ $<

clean:
	rm obj/*.o *.exe *.gch -f

clear:
	rm obj/*.o *.gch -f
