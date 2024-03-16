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
#include "../component/shapecomponent.h"
#include "../component/collisioncomponent.h"
#include "../component/inputcomponent.h"


class Entity {
private:
    bool alive = true;
public:
    const std::string &name;
    const Uint8 id;

    explicit Entity(const std::string &name, const Uint8 &id) : name(name), id(id) {};

    std::shared_ptr<SpriteComponent> sprite;
    std::shared_ptr<ShapeComponent> shape;
    std::shared_ptr<CollisionComponent> collision;
    std::shared_ptr<TransformComponent> transform;
    std::shared_ptr<InputComponent> input;

    [[nodiscard]] bool isAlive() const { return alive; }
};


#endif //ECS_SDL_ENTITY_H
