//
// Created by Evgenii Shchepotev on 27.02.2024.
//

#ifndef ECS_SDL_ENTITY_H
#define ECS_SDL_ENTITY_H

#include <string>
#include <unordered_map> // hash_map
#include <memory>

#include "../component/spritecomponent.h"
#include "../component/transformcomponent.h"


class Entity {
public:
    const std::string &name;
    const Uint8 id;

    explicit Entity(const std::string &name, const Uint8 &id): name(name), id(id) {};

    std::shared_ptr<SpriteComponent> sprite;
    std::shared_ptr<TransformComponent> transform;
};


#endif //ECS_SDL_ENTITY_H
