#pragma once

#include <map>
#include <string>
#include <memory>
#include <functional>
#include "GameObject.hpp"

class ObjectFactory
{
public:
    virtual ~ObjectFactory() = default;
    static ObjectFactory &getInstance();
    GameObject *createNew(std::string type, Garden::ObjectMetaData *metaData);
    void registerType(std::string className, std::function<GameObject *(Garden::ObjectMetaData *metaData)> type);

private:
    ObjectFactory() = default;
    ObjectFactory(const ObjectFactory &object) = delete;
    ObjectFactory &operator=(const ObjectFactory &object) = delete;
    static std::unique_ptr<ObjectFactory> m_instance;
    std::map<std::string, std::function<GameObject *(Garden::ObjectMetaData *metaData)>> m_typeRegitry;
};

template <class Type>
class Registrar
{
public:
    Registrar(std::string className)
    {
        ObjectFactory::getInstance().registerType(className, [](Garden::ObjectMetaData *metaData) -> GameObject * {
            return new Type(metaData);
        });
    }
};