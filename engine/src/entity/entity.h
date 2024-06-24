//
// Created by Evgenii Shchepotev on 27.02.2024.
//

#ifndef ECS_SDL_ENTITY_H
#define ECS_SDL_ENTITY_H

#include <memory>
#include <optional>
#include <string>
#include <tuple>

#include "../component/collisioncomponent.h"
#include "../component/inputcomponent.h"
#include "../component/lifecyclecomponent.h"
#include "../component/shapecomponent.h"
#include "../component/spritecomponent.h"
#include "../component/transformcomponent.h"

typedef std::tuple<std::optional<SpriteComponent>, std::optional<TransformComponent>, std::optional<CollisionComponent>,
                   std::optional<ShapeComponent>, std::optional<InputComponent>, std::optional<LifecycleComponent> >
    ComponentTuple;

class Entity {
  bool alive = true;
  const std::string name;

  ComponentTuple components;

 public:
  const Uint8 id;

  explicit Entity(const std::string& name, const Uint8& id) : name(std::string(name)), id(id){};

  // NB! Templates are compilable only with inplace methods it's not possible to split
  template <typename T>
  [[nodiscard]] bool has() const {
    auto component = getOptional<T>();
    return component.has_value();
  }

  template <typename T, typename... TArgs>
  T& addComponent(TArgs&&... args) {
    std::optional<T>& value = getOptional<T>();
    // What to do with previous component?
    T component = T(std::forward<TArgs>(args)...);
    value.emplace(component);
    return getComponent<T>();
  }

  template <typename T>
  T& getComponent() {
    return getOptional<T>().value();
  }

  template <typename T>
  const T& getComponent() const {
    return getOptional<T>().value();
  }

  [[nodiscard]] bool isAlive() const { return alive; }

  const std::string& tag() const { return name; }

 private:
  template <typename T>
  const std::optional<T>& getOptional() const {
    return std::get<std::optional<T>>(components);
  }

  template <typename T>
  std::optional<T>& getOptional() {
    return std::get<std::optional<T>>(components);
  }
};

#endif  // ECS_SDL_ENTITY_H
