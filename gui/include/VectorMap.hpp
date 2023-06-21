/*
** EPITECH PROJECT, 2023
** VectorMap.hpp
** File description:
** VectorMap
*/

#ifndef VECTORMAP_HPP_
    #define VECTORMAP_HPP_
    #include <vector>
    #include <map>
    #include <algorithm>
    #include <exception>

/**
 * @brief
 * NotInMapError Class Error
 * Error thrown when the key is not in found in the vector map.
 */
class NotInMapError : public std::exception {
    public:
        NotInMapError(): message("Key not in the vector map") {};
        ~NotInMapError() = default;
        const char *what() const noexcept override { return message.c_str(); };
    private:
        std::string message;
};

/// @brief Class encapsulating a vector and has some methods of a map
/// @tparam Key Template for the key class of the map
/// @tparam T Template for the value class of the map
template<class Key, class T>
class VectorMap {
    public:
        VectorMap() = default;
        ~VectorMap() = default;

        /// @brief Find the key in the vector and returns its iterator or the end iterator if not found
        /// @param key Key to find
        /// @return Iterator to the found key or end iterator if not found
        typename std::vector<std::pair<Key,T>>::const_iterator find(const Key &key) const
        {
            for (typename std::vector<std::pair<Key, T>>::const_iterator it = _vectorMap.begin(); it != _vectorMap.end();)
            {
                if (it->first == key)
                    return it;
                it++;
            }
            return _vectorMap.end();
        };

        /// @brief Insert the pair at the begining of the vector
        /// @param p Pair to push
        void push(std::pair<Key, T> p)
        {
            if (find(p.first) == end())
            {
                _vectorMap.insert(begin(), p);
            }
        };

        /// @brief Deletes an element of the vector by its key
        /// @param key Key used to delete
        /// @return Boolean, true if the key has been deleted, false if the key hasn't been found
        bool erase(const Key &key)
        {
            for (typename std::vector<std::pair<Key, T>>::iterator it = _vectorMap.begin(); it != _vectorMap.end();)
            {
                if (it->first == key)
                {
                    _vectorMap.erase(it);
                    return true;
                }
                it++;
            }
            return false;
        };

        /// @brief Returns a reference to the element at the id
        /// @param id Size_t for the id
        /// @return Pair of the key and element at the id specified
        std::pair<Key, T> &at(const std::size_t &id)
        {
            return _vectorMap[id];
        }

        /// @brief Returns the size of the vector
        /// @return Size_t of the size of the vector
        std::size_t size() const
        {
            return _vectorMap.size();
        }

        /// @brief Returns the begin iterator
        /// @return Iterator begin
        typename std::vector<std::pair<Key, T>>::iterator begin()
        {
            return _vectorMap.begin();
        }

        /// @brief Returns the end iterator
        /// @return Iterator end
        typename std::vector<std::pair<Key,T>>::iterator end()
        {
            return _vectorMap.end();
        }

        /// @brief Overload for the bracket to get the element with the key in the bracket. If the key is not in the vector, throw a NotInMap error
        /// @param key Key to search for
        /// @return Element with the key passed in the bracket
        T &operator[](const Key &key)
        {
            for (typename std::vector<std::pair<Key, T>>::iterator it = _vectorMap.begin(); it != _vectorMap.end();)
            {
                if (it->first == key)
                    return (*it).second;
                it++;
            }
            throw NotInMapError();
        };

    private:
        std::vector<std::pair<Key, T>> _vectorMap;
};

#endif /* !VECTORMAP_HPP_ */
