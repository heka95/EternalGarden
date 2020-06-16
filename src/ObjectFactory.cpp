#include "ObjectFactory.hpp"

std::unique_ptr<ObjectFactory> ObjectFactory::m_instance;
ObjectFactory &ObjectFactory::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance.reset(new ObjectFactory());
    }
    return *m_instance.get();
}

void ObjectFactory::registerType(std::string className, std::function<GameObject *(Garden::ObjectMetaData *metaData)> type)
{
    m_typeRegitry[className] = type;
}

GameObject *ObjectFactory::createNew(std::string type, Garden::ObjectMetaData *metaData)
{
    GameObject *object = nullptr;
    auto iterator = m_typeRegitry.find(type);
    if (iterator != m_typeRegitry.end())
    {
        object = iterator->second(metaData);
    }
    return object;
}