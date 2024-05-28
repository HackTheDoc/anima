#include "include/Game/Statistics.h"

#include "include/Game/Game.h"

void Statistics::update() {
    numenLevel = Game::player->numenLevel;
}

void Statistics::print() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    std::cout << worldName << " Stats:" << std::endl;
    std::cout << "- playtime         : " << playTime << std::endl;
    std::cout << "- attributs        : " << attributs << std::endl;
    std::cout << "- numen level      : " << numenLevel << std::endl;
    std::cout << "- powers: ";
    for (const auto& p : powers)
        std::cout << p << " ";
    std::cout << std::endl;
    std::cout << "- entity killed    : " << killedEntityCounter << std::endl;
    std::cout << "- entity resurected: " << resurrectedEntityCounter << std::endl;

    std::cout << std::endl;
}

void Statistics::entityKilled() {
    attributs--;
    killedEntityCounter++;
}

void Statistics::entityResurrected() {
    attributs++;
    resurrectedEntityCounter++;
}
