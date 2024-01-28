#pragma once

struct Animation {
    int index;
    int frames;
    int speed;

    Animation() {}

    /// @brief Create an animation Component
    /// @param i : index of the animation on the AnimationSheet
    /// @param f : number of frames
    /// @param s : frames rate in ms
    Animation(int i, int f, int s) {
        index = i;
        frames = f;
        speed = s;
    }
};
