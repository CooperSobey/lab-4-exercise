#ifndef TIMER_H
#define TIMER_H
#include <chrono>
#include <cstdint>
#include <ratio>



class Timer {
public:
    using nanoseconds = std::chrono::nanoseconds;
    using microseconds = std::chrono::microseconds;
    using milliseconds = std::chrono::milliseconds;
    using seconds = std::chrono::seconds;
    using minutes = std::chrono::minutes;
    using hours = std::chrono::hours;

    Timer() : lastTime(std::chrono::steady_clock::now()) {}

    void restart() {
        lastTime = std::chrono::steady_clock::now();
    }

    template <typename T>
    uint64_t click() {
        const auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<T>(now - lastTime);
        lastTime = now;
        return elapsed.count();
    }

    template <typename T>
    uint64_t glance() const {
        const auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<T>(now - lastTime);
        return elapsed.count();
    }

private:
    std::chrono::steady_clock::time_point lastTime;

};
#endif  // TIMER_H
