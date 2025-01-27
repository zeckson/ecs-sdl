#include "textrenderer.h"

TextRenderer::TextRenderer(TTF_Font* font, const TextRenderer::Config& config) : font(font), config(config) {}

void TextRenderer::render(SDL_Renderer* renderer) const {
  SDL_Surface* textSurface = TTF_RenderText_Blended(font, config.text.c_str(), config.textColor);
  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

  SDL_Rect textRect = {config.bbox.x, config.bbox.y, textSurface->w, textSurface->h};
  if (config.alignment == Center) {
    textRect.x += config.bbox.w / 2 - textSurface->w / 2;
  } else if (config.alignment == Right) {
    textRect.x += config.bbox.w - textSurface->w;
  }

  SDL_SetRenderDrawColor(renderer, config.bgColor.r, config.bgColor.g, config.bgColor.b, config.bgColor.a);
  SDL_RenderFillRect(renderer, &config.bbox);
  SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(textTexture);
}

// Constructor: Initializes the builder with the provided font
TextRenderer::Builder::Builder(TTF_Font* font) : font(font) {
    if (!font) {
        throw std::invalid_argument("Font cannot be null.");
    }
}

// Set alignment for the text
TextRenderer::Builder& TextRenderer::Builder::justify(Alignment align) {
    config.alignment = align;
    return *this;
}

// Set bounding box for the text
TextRenderer::Builder& TextRenderer::Builder::inside(const SDL_Rect& bbox) {
    config.bbox = bbox;
    return *this;
}

// Set the text content
TextRenderer::Builder& TextRenderer::Builder::withText(const std::string& text) {
    config.text = text;
    return *this;
}

// Set background color for the text
TextRenderer::Builder& TextRenderer::Builder::withBackgroundColor(const Pixel& color) {
    config.bgColor = {color.r(), color.g(), color.b()};
    return *this;
}

// Set foreground color for the text
TextRenderer::Builder& TextRenderer::Builder::withColor(const Pixel& color) {
    config.textColor = {color.r(), color.g(), color.b()};
    return *this;
}

// Build and return a TextRenderer object
TextRenderer TextRenderer::Builder::build() const {
    return TextRenderer(font, config);
}