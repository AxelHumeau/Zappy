/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ThreadPool
*/

#pragma once
#include "SafeQueue.hpp"
#include <functional>
#include <thread>
#include <list>

template <size_t poolSize>
class ThreadPool {
public:
    ThreadPool(): _finished(false)
    {
        for (size_t i = 0; i < poolSize; i++) {
            _threads.emplace_back([] (bool &finished, SafeQueue<std::function<void()>> &queue)
            {
                std::function<void()> func;

                while (!finished) {
                    if (!queue.tryPop(func))
                        continue;
                    func();
                }
            }, std::ref(_finished), std::ref(_queue));
        }
    }

    ~ThreadPool()
    {
        _finished = true;
        for (auto &thread : _threads)
            thread.join();
    }

    void addTask(std::function<void()> task)
    {
        _queue.push(task);
    }

private:
    SafeQueue<std::function<void()>> _queue;
    bool _finished;
    std::list<std::thread> _threads;
};
