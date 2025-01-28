#ifndef ENTRYSCENE_H
#define ENTRYSCENE_H

#include <scene/menuscene.h>

class EntryScene : public MenuScene {
 public:
  EntryScene(SceneGame& game);
  ~EntryScene() = default;

 protected:
  void onMenuItemSelected(const std::string& item) override;
};

#endif  // ENTRYSCENE_H