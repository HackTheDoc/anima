#pragma once

#include <SDL2/SDL.h>

namespace hue {
    const SDL_Color black                   = { 0,   0,   0, 255 };
    const SDL_Color white                   = { 255, 255, 255, 255 };
    const SDL_Color red                     = { 255,   0,   0, 255 };
    const SDL_Color blue                    = { 0,   0, 255, 255 };
    const SDL_Color green                   = { 0, 255,   0, 255 };

    const SDL_Color yellow                  = { 255, 166,  77, 255 };
    const SDL_Color light_gray              = { 211, 211, 211, 255 };

    const SDL_Color blur                    = {  71,  62, 102, 192 }; // #473E66
    const SDL_Color blur_dark               = {  19,   0,  19, 216 };
    const SDL_Color blur_white              = { 255, 255, 255, 192 };
    const SDL_Color blur_red                = { 179,   0,   0, 176 };

    const SDL_Color cinematic_background    = {  25,   0,  25, 255 }; // #190019

    const SDL_Color font                    = { 245, 215, 219, 255 }; // #F5D7DB
    const SDL_Color text_box                = {  27,  51,  88, 216 }; // #1B3358
    const SDL_Color border                  = { 251, 228, 216, 255 }; // #FBE4D8

    const SDL_Color portal_on               = {  77, 166, 255, 255 };
    const SDL_Color portal_off              = {   0,  89, 179, 255 };
    const SDL_Color door_open               = { 172,  57,  57, 255 };
    const SDL_Color door_closed             = {  96,  32,  32, 255 };


    const SDL_Color ui_background           = {  6, 20, 46, 255 }; // #06142E
    const SDL_Color placeholder_text        = { 191, 191, 191, 218 };
}

/*
#06142E : 6, 20, 46
#1B3358 : 27, 51, 88
#473E66 : 71, 62, 102
#BD83B8 : 189, 131, 184
#F5D7DB : 245, 215, 219
#F1916D : 241, 145, 109

#190019 : 25, 0, 25
#2B124C : 43, 18, 76
#522B5B : 82, 43, 91
#854F6C : 133, 79, 108
#DFB6B2 : 223, 182, 178
#FBE4D8 : 251, 228, 216
*/
