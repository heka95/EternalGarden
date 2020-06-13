#if !defined(__ENTITY__)
#define __ENTITY__

#include <vector>
#include "Component/BaseComponent.hpp"

class Entity
{
public:
    Entity(unsigned long uniqueId);
    unsigned long getId();
    
    void addComponent(BaseComponent *component);
    std::vector<BaseComponent*> getComponents() const;
private:
    unsigned long m_id;
    std::vector<BaseComponent*> m_components;
};

#endif