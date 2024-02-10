#pragma once

#include <SDL2/SDL.h>

namespace hue {
    const SDL_Color black                   = {   0,   0,   0, 255 };
    const SDL_Color white                   = { 255, 255, 255, 255 };
    const SDL_Color red                     = { 255,   0,   0, 255 };
    const SDL_Color blue                    = {   0,   0, 255, 255 };
    const SDL_Color green                   = {   0, 255,   0, 255 };

    const SDL_Color yellow                  = { 255, 166,  77, 255 };
    const SDL_Color light_gray              = { 211, 211, 211, 255 };

    const SDL_Color blur                    = {  61,  60,  58, 192 };
    const SDL_Color blur_dark               = {  89,  89,  89, 216 };
    const SDL_Color blur_white              = { 255, 255, 255, 192 };
    const SDL_Color blur_red                = { 179,   0,   0, 176 };

    const SDL_Color cinematic_background    = {  26,  26,  26, 255 };


    const SDL_Color portal_off              = { 255, 127, 127, 255 };
    const SDL_Color ui_background           = {  61,  60,  58, 255 };
    const SDL_Color placeholder_text        = { 191, 191, 191, 218 };
}
