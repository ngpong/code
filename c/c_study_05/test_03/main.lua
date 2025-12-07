local inspect = require("inspect")

local function a(name)
  return assert(os.getenv(name), [[os.getenv() failed: ]] .. name)
end
