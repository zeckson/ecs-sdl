//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_COMPONENT_H
#define ECS_SDL_COMPONENT_H

#include <string>

class Component {
public:
    const std::string name;
    virtual ~Component() {}
protected:
    explicit Component(const std::string &name): name(name) {}
};




#endif //ECS_SDL_COMPONENT_H
