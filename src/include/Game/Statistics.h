#pragma once

#include <string>
#include <array>

// Store the statistic of the world
struct Statistics {
    std::string worldName{ "Adocia" };
    std::string playTime{ "00:00:00" };

    // dark/light
    int attributs{ 0 };

    int numenLevel{ 0 }; // power level
    std::array<bool, 4> powers{ {true, false, false, false} }; // unlocked powers

    int killedEntityCounter{ 0 };
    int resurrectedEntityCounter{ 0 };

    void update();
    void print();

    void entityKilled();
    void entityResurrected();
};
