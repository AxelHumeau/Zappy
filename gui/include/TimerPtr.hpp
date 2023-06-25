/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** TimerPtr
*/

#pragma once
#include <chrono>
#include <memory>

/// @brief Smart pointer that delete the pointer after a certain time
/// @tparam T type of the pointer
template <class T>
class TimerPtr : public std::unique_ptr<T>{
public:
    /// @brief Contruct the pointer
    /// @param time time after which the pointer will be deleted
    /// @param ...args arguments to be passed to the constructor of the pointer
    template <class... Args>
    TimerPtr(std::chrono::milliseconds time, Args&&... args):
        std::unique_ptr<T>(std::make_unique<T>(std::forward<Args>(args)...)),
        timer(time),
        start(std::chrono::high_resolution_clock::now())
    {
    }

    ~TimerPtr() = default;

    /// @brief update the internal timer, must be called regularly
    void updateTimer()
    {
        if (std::chrono::high_resolution_clock::now() - start > timer &&
            *this != nullptr)
            std::unique_ptr<T>::reset(nullptr);
    }

private:
    std::chrono::milliseconds timer;
    std::chrono::_V2::system_clock::time_point start;
};
