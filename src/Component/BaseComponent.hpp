#pragma once

#include <string>

class BaseComponent
{
public:
    BaseComponent(){}
    virtual ~BaseComponent(){}
protected:
    std::string m_name = "BaseComponent";
};