#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
#include "pixel.h"
#include "renderable.h"

class TextRenderer: public Renderable {
 public:
  enum Alignment { Left, Center, Right };

  class Builder;

  void render(SDL_Renderer* renderer) override;

 private:
  struct Config {
    std::string text;
    SDL_Rect bbox;
    SDL_Color textColor;
    SDL_Color bgColor;
    Alignment alignment;
  };

  TTF_Font* font;
  const Config config;

  TextRenderer(TTF_Font* font, const TextRenderer::Config& config);
};

class TextRenderer::Builder {
 private:
  TTF_Font* font;
  TextRenderer::Config config{};

 public:
  Builder(TTF_Font* font);

  Builder& justify(Alignment align);
  Builder& inside(const SDL_Rect& bbox);
  Builder& withText(const std::string& text);
  Builder& withBackgroundColor(const Pixel& color);
  Builder& withColor(const Pixel& color);

  TextRenderer build() const;
};

#endif  // TEXT_RENDERER_H