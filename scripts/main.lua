local timer = 0

modules.Frame.SetFrameFunc(
    function()
        modules.Window.SetTitle("Frame running")
        print(timer)
        if timer == 120 then
            error("Frame test error")
        end
        timer = timer + 1
    end
)