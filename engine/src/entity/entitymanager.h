//
// Created by Evgenii Shchepotev on 13.03.2024.
//

#ifndef ECS_SDL_ENTITYMANAGER_H
#define ECS_SDL_ENTITYMANAGER_H

#include <list>
#include <map>
#include <memory>

#include "entity.h"

#define MAX_ENTITIES 255

typedef std::list<std::shared_ptr<Entity>> EntityList;
typedef std::map<std::string, EntityList> EntityMap;

class EntityManager {
 public:
  explicit EntityManager() = default;

  std::shared_ptr<Entity> createEntity(const std::string& name);

  void removeEntity(const std::shared_ptr<Entity>& entity) { entitiesToRemove.push_back(entity); };

  void update();

  const EntityList& getAllEntities() { return entities; }

  const EntityList& getEntities(const std::string& tag);

 private:
  Uint32 counter = 0;

  EntityMap entityMap;
  EntityList entities;
  EntityList entitiesToAdd;
  EntityList entitiesToRemove;

  void addEntity(const std::shared_ptr<Entity>& entity) { entitiesToAdd.push_back(entity); };
};

#endif  // ECS_SDL_ENTITYMANAGER_H
