---@meta
modules = modules or {}

---@class modules.Frame
modules.Frame = {}

---设置每帧由引擎调用的 Lua 函数。
---@param func function
function modules.Frame.SetFrameFunc(func) end

---设置目标逻辑帧率。
---@param fps integer
function modules.Frame.SetTargetFPS(fps) end

---获取当前实际帧率。
---@return number fps
function modules.Frame.GetCurrentFPS() end

---获取目标逻辑帧率。
---@return integer fps
function modules.Frame.GetTargetFPS() end

---获取当前逻辑帧编号。
---@return integer frame
function modules.Frame.GetFrameCount() end