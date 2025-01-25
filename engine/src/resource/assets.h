#ifndef ASSETS_H
#define ASSETS_H

#include <fstream>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

// Define a macro to store the name of the struct as a string literal
#define CONFIG_NAME(Struct) #Struct

#define WIDTH 1280
#define HEIGHT 1024
#define FPS 60
#define FULLSCREEN 0

#define FONT_NAME "glitchgoblin"
#define FONT_PATH "gfx/font/glitchgoblin.ttf"
#define DEFAULT_FONT_SIZE 24

namespace Asset {

// Abstract base class for all resources
struct Resource {
  std::string name;
  
  virtual ~Resource() = default;
  virtual void load(std::ifstream& in) = 0;
};

// Window resource
struct Window : Resource {
  int width = WIDTH;
  int height = HEIGHT;
  int fps = FPS;
  bool fullscreen = FULLSCREEN;

  void load(std::ifstream& in) override;
};

// Sprite resource
struct Sprite : Resource {
  std::string path;
  int angle = 0;

  void load(std::ifstream& in) override;
};

// Font resource
struct Font : Resource {
  std::string path = FONT_PATH;
  int size = DEFAULT_FONT_SIZE;

  void load(std::ifstream& in) override;
};

// Animation resource
struct Animation : Sprite {
  int frames = 1;
  int lifetime = 0;  // 0 means not animated

  void load(std::ifstream& in) override;
};

}  // namespace Asset

// Asset manager to handle loading and caching
class Assets {
 private:
  // Factory for creating resources
  std::map<std::string, std::function<std::shared_ptr<Asset::Resource>()>> loaders;

  static Assets instance;

 public:
  // Asset collections
  std::map<std::string, std::shared_ptr<Asset::Resource>> resources;
  // Constructor
  Assets();

  template <typename T>
  const T& getResource(const std::string& name);

  static const Assets& load(const std::string& path);
};

#endif
