//
// Created by Evgenii Shchepotev on 28.03.2024.
//

#include "framerate.h"

#include <utility>

void FrameRate::limit() const {
  if (currentFrameTime <= maxFrameTime) {
    SDL_Delay(Uint32(maxFrameTime) - currentFrameTime);
  }
}

void FrameRate::render(const std::unique_ptr<PixelRenderer>& renderer) const {
  renderer->renderText("FPS: " + std::to_string(int(std::ceil(fps))), 5, 5);
  renderer->renderText("Delay Time: " + std::to_string(maxFrameTime), 5, 30);
  renderer->renderText("Current Frame Time: " + std::to_string(currentFrameTime), 5, 55);
}

float FrameRate::elapsedTime() const { return float(currentFrameTime) / ONE_SECOND; }

void FrameRate::frameStart() { frameStartTime = SDL_GetTicks(); }

void FrameRate::frameEnd() {
  Uint32 currentTime = SDL_GetTicks();
  if (currentTime - startTime >= ONE_SECOND) {
    fps = ((double)frameCount / (currentTime - startTime)) * ONE_SECOND;

    // Reset frame rate counters
    startTime = frameStartTime;
    frameCount = 0;
  }

  currentFrameTime = currentTime - frameStartTime;
  totalFrame++;
  frameCount++;
}

Uint64 FrameRate::currentFrame() const { return totalFrame; }
