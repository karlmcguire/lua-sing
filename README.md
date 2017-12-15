# lua-sing
Sing buffers for Lua.

**NOTE**: still under heavy development - don't use this yet.

## usage

### new buffer

```lua
local buf = sing.new()
```

### push

```lua
buf:push("karl")
```

### shift

```lua
local name = buf:shift()
```