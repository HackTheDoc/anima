#include "include/Game/Entities/NPC.h"

#include "include/Game/Game.h"
#include "include/Game/Components/Collision.h"

NPC::NPC(std::string name, Species s, Behavior b) {
    type = Type::NON_PLAYER_CHARACTER;
    species = s;
    behavior = b;
    inventory.capacity = 4;
    this->name = name;
    dialog = nullptr;
}

NPC::NPC(std::string name, Species s, Behavior b, Inventory inv) {
    type = Type::NON_PLAYER_CHARACTER;
    species = s;
    behavior = b;
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

    hp = MAX_HP;

    position.Zero();

    numenLevel = GetMentalPower(species);
}

void NPC::update() {
    if (behavior == Behavior::RANDOM_MOVEMENT)
        randomMovement();
        
    Entity::update();
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
    return {
        .type = type,
        .species = species,
        .name = name,
        .hp = hp,
        .pos = position,
        .inv = inventory,
        .npc_hasdialog = haveDialog,
        .behavior = behavior
    };
}
