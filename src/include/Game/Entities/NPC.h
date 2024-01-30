#pragma once

#include "Entity.h"
#include "../Components/Dialog.h"

class NPC : public Entity {
public:
    Dialog* dialog;
    bool haveDialog;
    
    NPC(std::string name, Species s, Behavior b);
    NPC(std::string name, Species s, Behavior b, Inventory inv);
    ~NPC();

    void init() override;
    void update() override;
    void draw() override;
    void kill() override;

    void setDialog(std::string id);
    void updateDialogSelectedAnswer(int i);
    void validateDialog();

    void startDialog();
    void closeDialog();

    EntityStructure getStructure();

private:
    void randomMovement();
};
