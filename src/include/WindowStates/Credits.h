#pragma once

#include "WindowState.h"

#include "../UI/UIElements.h"

class Credits : public WindowState {
public:
    Credits();
    ~Credits();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

private:
    UIGifTexture* gif_background;

    UILabel* lbl_title;
    UILabel* lbl_author;
    UILabel* lbl_socials;
    UILabel* lbl_email;

    UIHyperlink* lk_discord;
    UIHyperlink* lk_twitter;
    UIHyperlink* lk_github;

    UIButton* btn_quit;
};
