#include "Log.h"

#include <fstream>
#include <iostream>

namespace core::runtime::Log
{
    namespace
    {
        bool Initialized = false;

        std::ofstream LogFile;


        void Write(
            const char* level,
            std::string_view message,
            std::ostream& console
        )
        {
            // 控制台
            console
                << '['
                << level
                << "] "
                << message
                << '\n';

            // engine.log
            if (LogFile.is_open())
            {
                LogFile
                    << '['
                    << level
                    << "] "
                    << message
                    << '\n';

                // 第一版直接每条都刷新。
                // 以后日志特别多时再考虑缓冲。
                LogFile.flush();
            }
        }
    }


    bool Init()
    {
        if (Initialized)
            return true;

        LogFile.open(
            "engine.log",
            std::ios::out | std::ios::trunc
        );

        if (!LogFile.is_open())
        {
            std::cerr
                << "[FATAL] Failed to open engine.log\n";

            return false;
        }

        Initialized = true;

        Info("Log initialized");

        return true;
    }


    void Shutdown()
    {
        if (!Initialized)
            return;

        Info("Log shutdown");

        LogFile.flush();
        LogFile.close();

        Initialized = false;
    }


    void Debug(std::string_view message)
    {
        Write(
            "DEBUG",
            message,
            std::cout
        );
    }


    void Info(std::string_view message)
    {
        Write(
            "INFO ",
            message,
            std::cout
        );
    }


    void Warn(std::string_view message)
    {
        Write(
            "WARN ",
            message,
            std::cerr
        );
    }


    void Error(std::string_view message)
    {
        Write(
            "ERROR",
            message,
            std::cerr
        );
    }


    void Fatal(std::string_view message)
    {
        Write(
            "FATAL",
            message,
            std::cerr
        );
    }
}