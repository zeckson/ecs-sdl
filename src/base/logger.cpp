//
// Created by Evgenii Shchepotev on 19.03.2024.
//

#include "logger.h"

void Logger::info(const char *format, ...) {
    va_list args;
    va_start(args, format);
    Logger::logv(ApplicationLog::GAME_ENGINE, SDL_LOG_PRIORITY_INFO, format, args);
    va_end(args);
}

void Logger::log(ApplicationLog category, SDL_LogPriority priority, const char *format, ...) {
    va_list args;
    va_start(args, format);
    logv(category, priority, format, args);
    va_end(args);
}

void Logger::logv(ApplicationLog category, SDL_LogPriority priority, const char *format, va_list ap) {
    SDL_LogMessageV(category, priority, format, ap);
}
