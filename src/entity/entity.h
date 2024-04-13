//
// Created by Evgenii Shchepotev on 27.02.2024.
//

#ifndef ECS_SDL_ENTITY_H
#define ECS_SDL_ENTITY_H

#include <memory>
#include <string>
#include <unordered_map>  // hash_map

#include "../component/collisioncomponent.h"
#include "../component/inputcomponent.h"
#include "../component/lifecyclecomponent.h"
#include "../component/shapecomponent.h"
#include "../component/spritecomponent.h"
#include "../component/transformcomponent.h"

class Entity {
 private:
  bool alive = true;
  const std::string name;

 public:
  const Uint8 id;

  explicit Entity(const std::string& name, const Uint8& id) : name(std::string(name)), id(id){};

  std::shared_ptr<SpriteComponent> sprite;
  std::shared_ptr<ShapeComponent> shape;
  std::shared_ptr<CollisionComponent> collision;
  std::shared_ptr<TransformComponent> transform;
  std::shared_ptr<InputComponent> input;
  std::shared_ptr<LifecycleComponent> lifecycle;

  [[nodiscard]] bool isAlive() const { return alive; }

  const std::string& tag() const { return name; }
};

#endif  // ECS_SDL_ENTITY_H
