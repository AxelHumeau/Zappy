/*
** EPITECH PROJECT, 2023
** Error.cpp
** File description:
** Error
*/

#include "Error.hpp"

namespace ZappyGui {
    NotImplementedError::NotImplementedError(): message("Not implemented") {}
    NotImplementedError::~NotImplementedError() {}
    char const *NotImplementedError::what() const noexcept { return message.c_str(); }

    IndexOutOfBoundsError::IndexOutOfBoundsError(): message("Index out of bounds") {}
    IndexOutOfBoundsError::~IndexOutOfBoundsError() {}
    char const *IndexOutOfBoundsError::what() const noexcept { return message.c_str(); }

    UndefinedResourceTypeError::UndefinedResourceTypeError()
    : message("Undefined resource type") {}
    char const *UndefinedResourceTypeError::what() const noexcept { return message.c_str(); }
}

