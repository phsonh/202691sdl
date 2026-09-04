---@meta
modules = modules or {}

---@class modules.Math
modules.Math = {}

---计算角度的正弦值。
---参数使用角度制，而不是弧度制。
---@param deg number 角度
---@return number value 正弦值
function modules.Math.sin(deg) end

---计算角度的余弦值。
---参数使用角度制，而不是弧度制。
---@param deg number 角度
---@return number value 余弦值
function modules.Math.cos(deg) end

---计算角度的正切值。
---参数使用角度制，而不是弧度制。
---@param deg number 角度
---@return number value 正切值
function modules.Math.tan(deg) end

---根据二维向量 (dx, dy) 计算方向角。
---返回值使用角度制，通常位于 [-180, 180] 范围内。
---@param dy number Y 方向差值
---@param dx number X 方向差值
---@return number deg 方向角（角度）
function modules.Math.atan2(dy, dx) end

---将角度转换为弧度。
---@param deg number 角度
---@return number rad 弧度
function modules.Math.deg2rad(deg) end

---将弧度转换为角度。
---@param rad number 弧度
---@return number deg 角度
function modules.Math.rad2deg(rad) end
