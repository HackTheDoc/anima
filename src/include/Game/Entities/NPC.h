#pragma once

#include "Entity.h"
#include "../Components/Dialog.h"

class NPC : public Entity {
public:
    Dialog* dialog;
    bool haveDialog;
    
    NPC(const std::string& name, const Species s, const Behavior b);
    NPC(const std::string& name, const Species s, const Behavior b, const Inventory& inv);
    ~NPC();

    void init() override;
    void update() override;

    void setDialog(const std::string& id);
    void updateDialogSelectedAnswer(const int i);
    void validateDialog();

    void startDialog();
    void closeDialog();

    Struct::Entity getStructure();
};
