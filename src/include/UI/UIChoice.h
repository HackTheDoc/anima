#pragma once

#include "UILabel.h"

struct UIChoice {
    enum ID {
        LG_ENGLISH,
        LG_FRENCH
    };

    int id;
    UILabel *lbl;
};