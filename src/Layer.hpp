#if !defined(__ENTITY_COLLECTION__)
#define __ENTITY_COLLECTION__

#include <vector>
#include "Entity.hpp"

class Layer
{
public:
    Layer();
    void addEntity(Entity *entity);
    std::vector<Entity*> getEntities() const;

private:
    unsigned long m_counter;
    std::vector<Entity*> m_entityList;
};

#endif