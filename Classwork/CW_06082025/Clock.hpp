#pragma once

#include <chrono>

namespace NP
{
    class Clock
    {
    public:
        Clock();
        void start();
        long long elapsed() const;
        void print_elapsed() const;

    private:
        using milli = std::chrono::milliseconds;
        using time_point = std::chrono::high_resolution_clock::time_point;

        time_point start_time;
    };
}