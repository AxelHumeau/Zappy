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

class NotInMapError : public std::exception {
    public:
        NotInMapError(): message("Key not in the vector map") {};
        ~NotInMapError() = default;
        const char *what() const noexcept override { return message.c_str(); };
    private:
        std::string message;
};

template<class Key, class T>
class VectorMap {
    public:
        VectorMap() = default;
        ~VectorMap() = default;

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

        void push(std::pair<Key, T> p)
        {
            if (find(p.first) == end())
            {
                _vectorMap.insert(begin(), p);
            }
        };

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

        std::pair<Key, T> &at(const std::size_t &id)
        {
            return _vectorMap[id];
        }

        std::size_t size() const
        {
            return _vectorMap.size();
        }

        typename std::vector<std::pair<Key, T>>::iterator begin()
        {
            return _vectorMap.begin();
        }

        typename std::vector<std::pair<Key,T>>::iterator end()
        {
            return _vectorMap.end();
        }

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
