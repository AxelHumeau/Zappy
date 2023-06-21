/*
** EPITECH PROJECT, 2023
** Error.hpp
** File description:
** Error
*/

#ifndef ERROR_HPP
    #define ERROR_HPP
    #include <exception>
    #include <string>

namespace ZappyGui {
    /**
     * @brief
     * NotImplementedError Class Error
     * Error thrown when trying to call an unimplemented function.
     */
    class NotImplementedError : public std::exception {
        public:
            NotImplementedError();
            ~NotImplementedError();
            const char *what() const noexcept override;
        private:
            std::string message;
    };
    /**
     * @brief
     * IndexOutOfBoundsError Class Error
     * Error thrown when trying to acces an element out of bounds.
     */
    class IndexOutOfBoundsError : public std::exception {
        public:
            IndexOutOfBoundsError();
            ~IndexOutOfBoundsError();
            const char *what() const noexcept override;
        private:
            std::string message;
    };
    /**
     * @brief
     * UndifinedResourceTypeError Class Error
     * Error thrown when trying to get or set an amount of a resource that dosen't exist.
     */
    class UndifinedResourceTypeError : public std::exception {
        public:
            UndifinedResourceTypeError();
            ~UndifinedResourceTypeError() = default;
            const char *what() const noexcept override;
        private:
            std::string message;
    };
};

#endif
