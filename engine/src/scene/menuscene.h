#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <string>
#include <vector>

#include "scene.h"
#include <engine/scenegame.h>

class MenuScene : public Scene<SceneGame> {
 public:
  MenuScene(const std::vector<std::string>& items, SceneGame& game);
  ~MenuScene();

  void init() override;
  void update() override;

 private:
  std::vector<std::string> menuItems;
  int selectedItem;

 protected:
  void onKeyboardAction(const Action& action) override;
  void onMouseAction(const MouseAction& action) override;

  virtual void onMenuItemSelected(const std::string& item) = 0;
};

#endif  // MENUSCENE_H