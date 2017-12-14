SING_CAP = 4

CC = clang
CFLAGS = -DSING_CAP=$(SING_CAP) -undefined dynamic_lookup -std=c99 -lsing

SRC = lua-sing.c
LIB = lua-sing.so

$(LIB): $(SRC)
	$(CC) $(SRC) -o $(LIB) $(CFLAGS)

clean:
	rm $(LIB)
