#pragma once

#include <SDL2/SDL.h>

namespace hue {
    const SDL_Color black                   = {   0,   0,   0, 255 };
    const SDL_Color white                   = { 255, 255, 255, 255 };
    const SDL_Color red                     = { 255,  85,  85, 255 }; // #ff5555
    const SDL_Color blue                    = { 139, 233, 253, 255 }; // #8be9fd
    const SDL_Color green                   = {  80, 250, 123, 255 }; // #50fa7b

    const SDL_Color yellow                  = { 241, 250, 140, 255 }; // #f1fa8c

    const SDL_Color blur                    = {  40,  42,  54, 192 }; // #282a36
    const SDL_Color blur_dark               = {  22,  23,  29, 216 }; // #16171d
    const SDL_Color blur_white              = { 248, 248, 242, 192 }; // #f8f8f2
    const SDL_Color blur_red                = { 255,  85,  85, 176 }; // #ff5555

    const SDL_Color cinematic_background    = {  22,  23,  29, 255 }; // #16171d

    const SDL_Color font                    = { 248, 248, 242, 255 }; // #f8f8f2
    const SDL_Color text_box                = {  40,  42,  54, 184 }; // #282a36
    const SDL_Color border                  = { 248, 248, 242, 255 }; // #f8f8f2

    const SDL_Color portal_on               = {  77, 166, 255, 255 };
    const SDL_Color portal_off              = {   0,  89, 179, 255 };
    const SDL_Color door_open               = { 172,  57,  57, 255 };
    const SDL_Color door_closed             = {  96,  32,  32, 255 };

    const SDL_Color ui_background           = {  40,  42,  54, 255 }; // #282a36
    const SDL_Color placeholder_text        = { 237, 237, 222, 218 }; // #ededde
}
