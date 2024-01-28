#include "include/Game/Entities/NPC.h"

#include "include/Game/Game.h"

NPC::NPC(std::string name, Entity::Species species) {
    type = Type::NON_PLAYER_CHARACTER;
    this->species = species;
    inventory.capacity = 4;
    this->name = name;
    dialog = nullptr;
}

NPC::NPC(std::string name, Entity::Species species, Inventory inv) {
    type = Type::NON_PLAYER_CHARACTER;
    this->species = species;
    inventory = inv;
    this->name = name;
    dialog = nullptr;
}

NPC::~NPC() {}

void NPC::init() {
    Entity::init();

    sprite = new Sprite(this);
    sprite->init(species, 6);

    collider = new EntityCollider(this);

    detector = new EntityDetector(this);

    hp = 100;

    position.Zero();

    walkSpeed = 4;

    numenLevel = GetMentalPower(species);
}

void NPC::update() {
    Entity::update();
}

void NPC::draw() {
    Entity::draw();
}

void NPC::kill() {
    Entity::kill();
}

void NPC::setDialog(std::string id) {
    if (dialog != nullptr) {
        dialog->destroy();
        Game::ui->remove("dialog");
    }
    dialog = new Dialog(this, id);
    Game::ui->add("dialog", dialog);
}

void NPC::updateDialogSelectedAnswer(int i) {
    if (dialog == nullptr) return;

    if (i > 0) dialog->moveCursorUp();
    else dialog->moveCursorDown();
}

void NPC::validateDialog() {
    if (dialog == nullptr) return;

    dialog->validateAnswer();
}

void NPC::startDialog() {
    setDialog(name);

    resetMovement();
    
    Game::player->interactingWith = this;
    Entity::startInteraction();
}

void NPC::closeDialog() {
    Game::ui->remove("dialog");

    Entity::closeIntereaction();
}

EntityStructure NPC::getStructure() {
   return {type, Entity::Type::UNKNOWN, species, name, hp, position, inventory, haveDialog};
}
