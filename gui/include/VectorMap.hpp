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

        typename std::vector<std::pair<Key,T>>::iterator find(const Key &key) const
        {
            for (std::pair<Key, T> &cur : _vectorMap)
            {
                if (cur.first == key)
                    return cur;
            }
            return _vectorMap.end();
        };

        void push(std::pair<Key, T> p)
        {
            if (!find(p.first))
            {
                _vectorMap.emplace(0, p);
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

        std::pair<Key, T> &at(const int &id)
        {
            return _vectorMap[id];
        }

        std::size_t size() const
        {
            return _vectorMap.size();
        }

        std::pair<Key, T> &operator[](const Key &key)
        {
            for (typename std::vector<std::pair<Key, T>>::iterator it = _vectorMap.begin(); it != _vectorMap.end();)
            {
                if (it->first == key)
                    return *it;
                it++;
            }
            throw NotInMapError();
        };

    private:
        std::vector<std::pair<Key, T>> _vectorMap;
};

#endif /* !VECTORMAP_HPP_ */
