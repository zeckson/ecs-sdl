//
// Created by Evgenii Shchepotev on 19.03.2024.
//

#include "logger.h"

void Logger::info(const char* format, ...) {
  va_list args;
  va_start(args, format);
  Logger::logv(ApplicationLog::GAME_ENGINE, SDL_LOG_PRIORITY_INFO, format, args);
  va_end(args);
}

void Logger::log(ApplicationLog category, SDL_LogPriority priority, const char* format, ...) {
  va_list args;
  va_start(args, format);
  logv(category, priority, format, args);
  va_end(args);
}

void Logger::logAll() { SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG); }

void Logger::logDefault() {
  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
  SDL_LogSetPriority(ApplicationLog::GAME_ENGINE, SDL_LOG_PRIORITY_INFO);
}

void Logger::logv(ApplicationLog category, SDL_LogPriority priority, const char* format, va_list ap) {
  SDL_LogMessageV(category, priority, format, ap);
}

void Logger::debug(const char* format, ...) {
  va_list args;
  va_start(args, format);
  Logger::logv(ApplicationLog::GAME_ENGINE, SDL_LOG_PRIORITY_DEBUG, format, args);
  va_end(args);
}

void Logger::error(const char* format, ...) {
  va_list args;
  va_start(args, format);
  Logger::logv(ApplicationLog::GAME_ENGINE, SDL_LOG_PRIORITY_ERROR, format, args);
  va_end(args);
}
