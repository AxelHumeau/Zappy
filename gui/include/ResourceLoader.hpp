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

    /// @brief Resource loader for the ZappyGui::Renderer
    class ResourceLoader {
        public:
            ResourceLoader() = default;
            ~ResourceLoader() = default;

            /// @brief Load every resources in the resource file
            /// @param resourceFile File contaning the resources to load
            static void load(std::string resourceFile);

            /// @brief Encapsulation of the function loading all ogre's resources
            static void initAll();
        protected:
        private:
            /// @brief Split the string in parameter in multiple strings when one of the delimiter is found
            /// @param str String to split
            /// @param delims String containing all the wanted delimiters
            /// @return std::vector containing every split of the initial string
            static std::vector<std::string> _splitLine(std::string str, const std::vector<std::string> &delims);

            /// @brief Find in the string the position where one of the delimiter is found and returns the position of the delimiter found and the length of the string to the next delimiter
            /// @param str String in which to find the delimiters
            /// @param delims String containing all the wanted delimiters
            /// @return std::pair containing in first the position of the delimiter in the string and in second the length of the sting to the next delimiter
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
