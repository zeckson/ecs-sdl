//
// Created by Evgenii Shchepotev on 27.02.2024.
//

#ifndef ECS_SDL_ENTITY_H
#define ECS_SDL_ENTITY_H

#include <string>
#include <tuple>
#include <memory>

#include "../component/sprite.h"


class Entity {
public:
    const std::string &name;
    const Uint8 id;

    explicit Entity(const std::string &name, const Uint8 &id): name(name), id(id) {};
};


#endif //ECS_SDL_ENTITY_H
