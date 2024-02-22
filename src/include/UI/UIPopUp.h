#pragma once

#include "UIElement.h"
#include "UILabel.h"

class UIPopUp : public UIElement {
public:
    static const int DELAY;
    int timeLeft;

    UIPopUp();
    ~UIPopUp();

    void addBlur();
    // void with translation
    void addLabel(const std::string& t);
    // no translation
    void addDirectLabel(const std::string& t);

    void draw(int offset);
    void destroy() override;

    bool operator<(const UIPopUp* o) const;

private:
    bool haveBlur;
    UILabel* lbl;
};
