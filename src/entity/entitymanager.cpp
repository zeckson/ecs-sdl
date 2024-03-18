//
// Created by Evgenii Shchepotev on 13.03.2024.
//
#include <stdexcept>

#include "entitymanager.h"

std::shared_ptr<Entity> EntityManager::createEntity(const std::string &name) {
    if (counter >= MAX_ENTITIES) {
        // TODO: get dead entities pool and clean one and resurrect otherwise die!
        throw std::runtime_error("Maximum entities created: " + std::to_string(MAX_ENTITIES));
    }
    const auto &entity = std::make_shared<Entity>(name, counter++);
    addEntity(entity);
    return entity;
}

void EntityManager::update() {
    for (const auto& entityToRemove: entitiesToRemove) {
        entities.remove(entityToRemove);
        entityMap[entityToRemove->tag()].remove(entityToRemove);
    }
    entitiesToRemove.clear();

    for (const auto& entityToAdd: entitiesToAdd) {
        entities.push_back(entityToAdd);
        entityMap[entityToAdd->tag()].push_back(entityToAdd);
    }
    entitiesToAdd.clear();

}
