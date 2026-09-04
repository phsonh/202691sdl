---@meta

modules = modules or {}

---@class modules.Debug
modules.Debug = {}

---记录一条普通日志。
---不会中断 Lua 执行。
---@param message string 日志内容
function modules.Debug.Log(message) end

---记录一条警告日志。
---不会中断 Lua 执行。
---@param message string 警告内容
function modules.Debug.Warn(message) end

---抛出一个致命 Lua 错误。
---当前 Lua 执行会立即中断，并由 Engine 统一记录日志、弹出错误窗口并结束运行。
---@param message string 错误内容
function modules.Debug.Error(message) end