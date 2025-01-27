#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <string>
#include <vector>

#include "scene.h"
#include <engine/scenegame.h>

class MenuScene : public Scene {
 public:
  MenuScene(const std::vector<std::string>& items, SceneGame& game);
  ~MenuScene();

  void init() override;
  void update() override;

 private:
  SceneGame& game;
  std::vector<std::string> menuItems;
  int selectedItem;

 protected:
  void onKeyboardAction(const Action& action) override;
  void onMouseAction(const MouseAction& action) override;
};

#endif  // MENUSCENE_H