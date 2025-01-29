#ifndef ENTRYSCENE_H
#define ENTRYSCENE_H

#include <scene/menuscene.h>

#include "ballscene.h"

class EntryScene : public MenuScene {
 private:
  std::shared_ptr<BallScene> bgScene;

 public:
  EntryScene(SceneGame& game, std::shared_ptr<BallScene> bgScene);
  ~EntryScene() = default;

  void init() override;
  void update() override;

 protected:
  void onMenuItemSelected(const std::string& item) override;
};

#endif  // ENTRYSCENE_H