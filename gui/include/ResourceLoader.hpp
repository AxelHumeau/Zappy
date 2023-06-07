/*
** EPITECH PROJECT, 2023
** ResourceLoader.hpp
** File description:
** ResourceLoader
*/

#ifndef RESOURCELOADER_HPP_
    #define RESOURCELOADER_HPP_
    #include <string>
    #include <map>
    #include <vector>
    #include <exception>

namespace ZappyGui {

    class ResourceLoader {
        public:
            ResourceLoader() = default;
            ~ResourceLoader() = default;

            static void load(std::string resourceFile);
            static void initAll();
        protected:
        private:
            static std::vector<std::string> _splitLine(std::string str, const std::vector<std::string> &delims);
            static std::pair<std::size_t, std::size_t> _findDelim(std::string str, std::vector<std::string> delims);
    };

    /**
     * @brief
     * ResourceFileNotFoundError Class Error
     * Error thrown when the resource file for the gui can't be read or found.
     */
    class ResourceFileNotFoundError : public std::exception {
        public:
            ResourceFileNotFoundError();
            ~ResourceFileNotFoundError() = default;
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    /**
     * @brief
     * InvalidResourceError Class Error
     * Error thrown when the resource format is invalid.
     */
    class InvalidResourceError : public std::exception {
        public:
            InvalidResourceError();
            ~InvalidResourceError() = default;
            const char *what() const noexcept override;
        private:
            std::string message;
    };

}

#endif /* !RESOURCELOADER_HPP_ */
