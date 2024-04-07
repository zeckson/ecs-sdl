//
// Created by Evgenii Shchepotev on 19.03.2024.
//

#ifndef ECS_SDL_LOGGER_H
#define ECS_SDL_LOGGER_H

#include "SDL2/SDL.h"

enum ApplicationLog {
    GAME_ENGINE = SDL_LOG_CATEGORY_CUSTOM,
};

class Logger {
public:
    static void info(const char* format, ...);
    static void debug(const char* format, ...);
    static void error(const char* format, ...);

    static void log(ApplicationLog category, SDL_LogPriority priority, const char *format, ...);
private:
    static void logv(ApplicationLog category, SDL_LogPriority priority, const char *format, va_list ap);
};


#endif //ECS_SDL_LOGGER_H
