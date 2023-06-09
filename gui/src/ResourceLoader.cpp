/*
** EPITECH PROJECT, 2023
** ResourceLoader.cpp
** File description:
** ResourceLoader
*/

#include <OGRE/Ogre.h>
#include "ResourceLoader.hpp"

void ZappyGui::ResourceLoader::load(std::string resourceFile)
{
    std::fstream configFile;
    std::string line;
    std::vector<std::string> delims = { " " };
    std::vector<std::string> tmp;

    configFile.open(resourceFile, std::ios::in);
    if (!configFile.is_open() || !configFile.good())
        throw ZappyGui::ResourceFileNotFoundError();

    while(getline(configFile, line)) {
        if (line.length() == 0)
            continue;
        tmp = _splitLine(line, delims);
        if (tmp.size() != 3)
            throw ZappyGui::InvalidResourceError();
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(tmp[0], tmp[1], tmp[2]);
    }
    configFile.close();
}

void ZappyGui::ResourceLoader::initAll()
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

std::vector<std::string> ZappyGui::ResourceLoader::_splitLine(std::string str, const std::vector<std::string> &delims)
{
    std::vector<std::string> lineParts;
    std::string part;

    std::pair<std::size_t, std::size_t> pos;
    while ((pos = _findDelim(str, delims)).first != std::string::npos) {
        if (pos.first != 0) {
            part = str.substr(0, pos.first);
            lineParts.push_back(part);
        }
        str.erase(0, pos.first + pos.second);
    }
    if (str.length() > 0)
        lineParts.push_back(str);
    return lineParts;
}

std::pair<std::size_t, std::size_t> ZappyGui::ResourceLoader::_findDelim(std::string str, std::vector<std::string> delims)
{
    std::pair<std::size_t, std::size_t> result;
    std::size_t pos = std::string::npos;
    result.first = pos;
    result.second = 0;

    for (std::size_t i = 0; i < delims.size(); i++) {
        pos = str.find(delims[i]);
        if (pos < result.first) {
            result.first = pos;
            result.second = delims[i].length();
        }
    }
    return result;
}

ZappyGui::ResourceFileNotFoundError::ResourceFileNotFoundError(): message("Resource file not found")
{
}

char const *ZappyGui::ResourceFileNotFoundError::what() const noexcept
{
    return message.c_str();
}

ZappyGui::InvalidResourceError::InvalidResourceError(): message("Invalid resource format")
{
}

char const *ZappyGui::InvalidResourceError::what() const noexcept
{
    return message.c_str();
}
