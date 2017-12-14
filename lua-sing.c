#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "sing.h"

/* lua_sing_push is called with buffer:push("string") and pushes the string to
   the tail of the buffer */
static int 
lua_sing_push(lua_State *L) {
	/* check if argument is string */
	if(lua_isstring(L, -1) != 1)
		return luaL_error(L, "argument must be a string");

	/* get sing_buffer pointer from metatable field */
	luaL_getmetafield(L, -2, "__sing__point");

	/* push argument string to sing_buffer */
	sing_push(lua_touserdata(L, -1), (char *)lua_tostring(L, -2));

	/* return nothing */
	return 0;
}

/* lua_sing_shift is called with buffer:shift() and shifts the buffer, returning
   the next element in the buffer */
static int
lua_sing_shift(lua_State *L) {
	/* get sing_buffer pointer from metatable field */
	luaL_getmetafield(L, -1, "__sing__point");

	/* get the next element */
	lua_pushstring(L, sing_shift(lua_touserdata(L, -1)));

	/* return string */
	return 1;
}

/* lua_sing_close is called by the lua garbage collector when the buffer object
   is marked for collection, so it frees the memory previously used to hold
   the buffer's sing_buffer struct */
static int
lua_sing_close(lua_State *L) {
	/* get sing_buffer pointer from metatable field */
	luaL_getmetafield(L, -1, "__sing__point");

	/* free memory */
	free(lua_touserdata(L, -1));

	/* return nothing */
	return 0;
}

/* lua_sing_new is called by sing.new() and returns a new buffer object */
static int 
lua_sing_new(lua_State *L) {
	/* create a table for use in lua */
	lua_createtable(L, 0, 2);

	lua_pushcfunction(L, &lua_sing_push);
	lua_setfield(L, -2, "push");

	lua_pushcfunction(L, &lua_sing_shift);
	lua_setfield(L, -2, "shift");

	/* create a metatable to set on the object */
	lua_createtable(L, 0, 2);

	lua_pushcfunction(L, &lua_sing_close);
	/* __gc is ran by the garbage collector before the object is collected */	
	lua_setfield(L, -2, "__gc");

	/* create a new sing_buffer and initialize */
	struct sing_buffer *b = malloc(sizeof(struct sing_buffer));
	sing_init(b);

	/* add the pointer to metatable */	
	lua_pushlightuserdata(L, b);
	lua_setfield(L, -2, "__sing__point");

	/* set metatable to table object created earlier */
	lua_setmetatable(L, -2);

	/* return table object */
	return 1;
}

/* lua_sing_cap is called by sing.cap() and returns the capacity of buffers */
static int 
lua_sing_cap(lua_State *L) {
	lua_pushinteger(L, SING_CAP);
	return 1;
}

static const struct luaL_Reg lua_sing[] = {
	{"new", lua_sing_new},
	{"cap", lua_sing_cap}
};

int 
luaopen_sing (lua_State *L) {
	luaL_newlib(L, lua_sing);
	return 1;
}
