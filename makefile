SING_CAP = 4
LUA_VERSION = 5.3

CC = clang
CFLAGS = -DSING_CAP=$(SING_CAP) -undefined dynamic_lookup -std=c99 -lsing

SRC = lua-sing.c
LIB = lua-sing.so

.PHONY: clean install

$(LIB): $(SRC)
	$(CC) $(SRC) -o $(LIB) $(CFLAGS)

install: $(LIB)
	cp $(LIB) /usr/local/lib/lua/$(LUA_VERSION)/ 
	rm $(LIB)

clean: 
	rm $(LIB)
