#include "engine/Engine.h"


int main(int argc, char* argv[])
{   
    //初始化Runtime/Modules
    bool initSuccess = engine::Init();
    //主循环
    bool runSuccess = false;
    if (initSuccess) runSuccess = engine::Run();
    //关闭Runtime/Modules
    engine::Shutdown();
    return (initSuccess && runSuccess) ? 0 : 1;
}