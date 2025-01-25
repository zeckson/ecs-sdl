#include "assets.h"

namespace Asset {

void Window::load(std::ifstream& in) {
    in >> width >> height >> fps >> fullscreen;
    if (in.fail()) {
        throw std::runtime_error("Reading Window resource failed");
    }
}

void Sprite::load(std::ifstream& in) {
    in >> name >> path >> angle;
    if (in.fail()) {
        throw std::runtime_error("Reading Sprite resource failed");
    }
}

void Font::load(std::ifstream& in) {
    in >> name >> path >> size;
    if (in.fail()) {
        throw std::runtime_error("Reading Font resource failed");
    }
}

void Animation::load(std::ifstream& in) {
    Sprite::load(in);  // Load base Sprite data
    in >>  frames >> lifetime;
    if (in.fail()) {
        throw std::runtime_error("Reading Animation failed");
    }
}

}  // namespace Asset

Assets::Assets() {
    // Register loaders for different resource types
    loaders["Font"] = []() { return std::make_shared<Asset::Font>(); };
    loaders["Sprite"] = []() { return std::make_shared<Asset::Sprite>(); };
    loaders["Animation"] = []() { return std::make_shared<Asset::Animation>(); };
}

template <typename T>
const T& Assets::getResource(const std::string& name) {
    auto resource = resources.find(name);
    if (resource == resources.end()) {
        throw std::runtime_error("No resource found with name: " + name);
    }
  return resource->second;
}

template <typename T>
Assets Assets::load(const std::string& path) {

  std::ifstream fin(path);

  if (!fin) {
    throw std::runtime_error("Failed to open file: " + path);
  }

  std::string name;
  Assets loaded = Assets();
  while (fin.good() && !fin.eof()) {
    fin >> name;
    auto loader = loaders.find(name);
    if (loader == loaders.end()) {
        throw std::runtime_error("No loader registered for type: " + name);
    }
    auto resource = loader->second();

    resource->load(fin);
    resources[resource->name] = resource;
  }

  fin.close();

  return loaded;

}

