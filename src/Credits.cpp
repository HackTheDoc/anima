#include "include/WindowState/Credits.h"

#include "include/Window.h"

Credits::Credits() {}

Credits::~Credits() {}

void Credits::init() {
    // background
    background = new GifTexture("./assets/animations/main menu", 3, 200, Window::screen);

    // title + author

    label[TITLE] = new UILabel(Text::Get("Developped By"), "h4", hue::white);
    label[TITLE]->place(
        16 * (Window::fullscreen + 1),
        8*(Window::fullscreen+1)
    );

    label[AUTHOR] = new UILabel("HackTheDoc", "h3 bold", hue::red);
    label[AUTHOR]->place(
        1 * label[TITLE]->width() / 3 + 16 * (Window::fullscreen + 1),
        label[TITLE]->height() + 16*(Window::fullscreen+1)
    );

    int containerWidth = 2 * Window::screen.w /3;
    int offsetY = (Window::screen.h + label[AUTHOR]->y() + label[AUTHOR]->height()) / 2;

    // links
    link[DISCORD] = new UIHyperlink("Discord", "https://discord.gg/Ya8NWJMcqx", "big", hue::white);
    link[DISCORD]->place(
        (containerWidth - link[DISCORD]->width()) / 2,
        offsetY - link[DISCORD]->height() - 8*(Window::fullscreen+1)
    );

    link[GITHUB] = new UIHyperlink("Github", "https://github.com/HackTheDoc", "big", hue::white);
    link[GITHUB]->place(
        (containerWidth - link[GITHUB]->width()) / 2,
        offsetY - link[DISCORD]->height() - link[GITHUB]->height() - 24*(Window::fullscreen+1)
    );

    link[TWITTER] = new UIHyperlink("Twitter", "https://twitter.com/HackTheDoc", "big", hue::white);
    link[TWITTER]->place(
        (containerWidth - link[TWITTER]->width()) / 2,
        offsetY + 8*(Window::fullscreen+1)
    );

    // labels
    label[EMAIL] = new UILabel("hackthedoc@gmail.com", "big", hue::white);
    label[EMAIL]->place(
        (containerWidth - label[EMAIL]->width()) / 2,
        offsetY + label[EMAIL]->height() + 24*(Window::fullscreen+1)
    );

    label[SOCIALS] = new UILabel(Text::Get("Socials:"), "big bold", hue::white);
    label[SOCIALS]->place(
        (containerWidth - label[SOCIALS]->width()) / 2,
        offsetY - link[DISCORD]->height() - link[GITHUB]->height() - label[SOCIALS]->height() - 40*(Window::fullscreen+1)
    );

    // quit button
    quitButton = new UIButton("X", UIButton::ID::QUIT_CREDITS, "h3", hue::white);
    quitButton->place(
        Window::screen.w - quitButton->width() - 8*(Window::fullscreen+1),
        8*(Window::fullscreen+1)
    );
}

void Credits::update() {
    background->play();

    for (int i = 0; i < NUMBER_OF_LINKS; i++)
    {
        link[i]->update();
    }

    quitButton->update();
}

void Credits::render() {
    background->draw();

    for (int i = 0; i < NUMBER_OF_LINKS; i++)
    {
        link[i]->draw();
    }

    for (int i = 0; i < NUMBER_OF_LABELS; i++)
    {
        label[i]->draw();
    }

    quitButton->draw();
}

void Credits::clean()
{
    background->destroy();

    for (int i = 0; i < NUMBER_OF_LINKS; i++)
    {
        link[i]->destroy();
    }

    for (int i = 0; i < NUMBER_OF_LABELS; i++)
    {
        label[i]->destroy();
    }

    quitButton->destroy();
}

void Credits::useHyperlink(std::string l)
{
    if (l == "discord")
        link[DISCORD]->openURL();
    else if (l == "twitter")
        link[TWITTER]->openURL();
    else if (l == "github")
        link[GITHUB]->openURL();
}
