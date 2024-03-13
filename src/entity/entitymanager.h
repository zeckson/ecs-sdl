//
// Created by Evgenii Shchepotev on 13.03.2024.
//

#ifndef ECS_SDL_ENTITYMANAGER_H
#define ECS_SDL_ENTITYMANAGER_H

#include <list>
#include <map>
#include <memory>

#include "entity.h"

typedef std::list<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, std::shared_ptr<Entity>> EntityMap;

class EntityManager {
public:
    explicit EntityManager() = default;

    std::shared_ptr<Entity> createEntity(const std::string &name);

    void addEntity(const std::shared_ptr<Entity> &entity) {
        entitiesToAdd.push_back(entity);
    };
    void removeEntity(const std::shared_ptr<Entity> &entity) {
        entitiesToRemove.push_back(entity);
    };

    void update();

private:
    Uint32 counter = 0;

    EntityVector entities;
    EntityVector entitiesToAdd;
    EntityVector entitiesToRemove;
};


#endif //ECS_SDL_ENTITYMANAGER_H
