#include "include/WindowStates/Credits.h"

#include "include/Window.h"

Credits::Credits() {}

Credits::~Credits() {}

void Credits::init() {
    // background
    gif_background = new UIGifTexture("./assets/animations/main menu", 3, 200, Window::screen);

    // title + author
    lbl_title = new UILabel(Text::Get("Developped By"), "h4", hue::white);
    lbl_title->place(
        16 * (Window::fullscreen + 1),
        8*(Window::fullscreen+1)
    );

    lbl_author = new UILabel("HackTheDoc", "h3 bold", hue::red);
    lbl_author->place(
        1 * lbl_title->width() / 3 + 16 * (Window::fullscreen + 1),
        lbl_title->height() + 16*(Window::fullscreen+1)
    );

    int containerWidth = 2 * Window::screen.w /3;
    int offsetY = (Window::screen.h + lbl_author->y() + lbl_author->height()) / 2;

    // links
    lk_discord = new UIHyperlink("Discord", "https://discord.gg/Ya8NWJMcqx", "big", hue::white);
    lk_discord->place(
        (containerWidth - lk_discord->width()) / 2,
        offsetY - lk_discord->height() - 8*(Window::fullscreen+1)
    );

    lk_github = new UIHyperlink("Github", "https://github.com/HackTheDoc", "big", hue::white);
    lk_github->place(
        (containerWidth - lk_github->width()) / 2,
        offsetY - lk_discord->height() - lk_github->height() - 24*(Window::fullscreen+1)
    );

    lk_twitter = new UIHyperlink("Twitter", "https://twitter.com/HackTheDoc", "big", hue::white);
    lk_twitter->place(
        (containerWidth - lk_twitter->width()) / 2,
        offsetY + 8*(Window::fullscreen+1)
    );

    // labels
    lbl_email = new UILabel("hackthedoctor@gmail.com", "big", hue::white);
    lbl_email->place(
        (containerWidth - lbl_email->width()) / 2,
        offsetY + lbl_email->height() + 24*(Window::fullscreen+1)
    );

    lbl_socials = new UILabel(Text::Get("Socials:"), "big bold", hue::white);
    lbl_socials->place(
        (containerWidth - lbl_socials->width()) / 2,
        offsetY - lk_discord->height() - lk_github->height() - lbl_socials->height() - 40*(Window::fullscreen+1)
    );

    // quit button
    btn_quit = new UIButton("X", Event::ID::OPEN_MAIN_MENU, "h3", hue::white);
    btn_quit->place(
        Window::screen.w - btn_quit->width() - 8*(Window::fullscreen+1),
        8*(Window::fullscreen+1)
    );
}

void Credits::update() {
    gif_background->update();

    lk_discord->update();
    lk_github->update();
    lk_twitter->update();

    btn_quit->update();
}

void Credits::render() {
    gif_background->draw();

    lk_discord->draw();
    lk_github->draw();
    lk_twitter->draw();

    lbl_title->draw();
    lbl_author->draw();
    lbl_socials->draw();
    lbl_email->draw();

    btn_quit->draw();
}

void Credits::clean() {
    gif_background->destroy();

    lk_discord->destroy();
    lk_github->destroy();
    lk_twitter->destroy();

    lbl_title->destroy();
    lbl_author->destroy();
    lbl_socials->destroy();
    lbl_email->destroy();

    btn_quit->destroy();
}
