local sing = require("lua-sing")

-- test sing.cap
--
-- making sure sing.cap returns a number containing the capacity
assert(type(sing.cap()) == "number", "sing.cap")

-- test sing.new
--
-- making sure there's a buffer:push(s) and buffer:shift() function
local keys = 0
for key, value in pairs(sing.new()) do
	assert(key == "shift" or key == "push", "sing.new")
	keys = keys + 1
end
assert(keys == 2, "sing.new function count")

-- test buffer:push(s)
--
-- making sure buffer:push(s) returns true (no error)
local buf = sing.new()
assert(buf:push("karl"), "sing buffer:push(s)")

-- test buffer:shift()
--
-- making sure buffer:shift() equals the previously called buffer:push(s)
assert(buf:shift() == "karl", "sing buffer:shift()")

-- test buffer.__gc metafield
--
-- making sure it's a function that the garbage collector can call
assert(type(getmetatable(buf).__gc) == "function", "sing buffer.__gc function")