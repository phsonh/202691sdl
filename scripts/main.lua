local timer = 0
modules.Frame.SetTargetFPS(60)

modules.Frame.SetFrameFunc(
    function()
        if (timer % 1) == 0 then 
            local current_fps = modules.Frame.GetCurrentFPS()
            local target_fps = modules.Frame.GetTargetFPS()
            local count = modules.Frame.GetFrameCount()
            modules.Window.SetTitle(string.format("%d:%.1f/%d", count,current_fps,target_fps))
        end
        timer = timer + 1
    end
)