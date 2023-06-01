/*
** EPITECH PROJECT, 2023
** Utils.hpp
** File description:
** Utils
*/

#ifndef UTILS_HPP_
    #define UTILS_HPP_

namespace ZappyGui {
    struct nop
    {
        template <typename T>
        void operator() (T const &) const noexcept { }
    };
}

#endif /* !UTILS_HPP_ */
