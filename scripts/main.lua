modules.Frame.SetTargetFPS(60)

local player = {x=0,y=-200}
local boss = {x=200,y=0}
function Angle(obj1,obj2)
    local dy = obj2.y-obj1.y
    local dx = obj2.x-obj1.x
    return modules.Math.atan2(dy,dx)
end
print(string.format("The angle from boss to player is %.1f",Angle(boss,player)))
modules.Debug.Log("hello")
modules.Debug.Warn("careful")
modules.Debug.Error("fatal test")

print("这里不会执行")

modules.Frame.SetFrameFunc(
    function()
        local current_fps = modules.Frame.GetCurrentFPS()
        local target_fps = modules.Frame.GetTargetFPS()
        local count = modules.Frame.GetFrameCount()
            
        modules.Window.SetTitle(string.format("%d:%.1f/%d", count,current_fps,target_fps))
        --print (modules.Math.sin(count))
    end
)