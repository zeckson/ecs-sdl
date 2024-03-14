//
// Created by Evgenii Shchepotev on 13.03.2024.
//

#include "entitymanager.h"

std::shared_ptr<Entity> EntityManager::createEntity(const std::string &name) {
    return std::make_shared<Entity>(name, counter++);
}

void EntityManager::update() {
    for (const auto& entityToRemove: entitiesToRemove) {
        entities.remove(entityToRemove);
        entityMap[entityToRemove->name].remove(entityToRemove);
    }
    entitiesToRemove.clear();

    for (const auto& entityToAdd: entitiesToAdd) {
        entities.push_back(entityToAdd);
        entityMap[entityToAdd->name].push_back(entityToAdd);
    }
    entitiesToAdd.clear();

}
