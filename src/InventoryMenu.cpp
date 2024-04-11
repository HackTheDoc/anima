#include "include/WindowStates/InventoryMenu.h"

#include "include/Window.h"
#include "include/Game/Game.h"

InventoryMenu::InventoryMenu(Inventory* inv) {
    lbl_title = nullptr;
    inventory = inv;
}

InventoryMenu::~InventoryMenu() {}

void InventoryMenu::init() {
    lbl_title = new UILabel(Text::Get("Inventory"), "h3", hue::font);
    lbl_usage = new UILabel(Text::Get("LEFT click to use\nRIGHT click to drop"), "small", hue::font);
    itemDescription = new UITextBox("item", "default", hue::font);

    container.w = 3 * Window::screen.w / 5;
    container.h = 3 * Window::screen.h / 5;
    container.x = (Window::screen.w - container.w) / 2;
    container.y = (Window::screen.h - container.h) / 2;

    lbl_title->place(
        container.x + (container.w - lbl_title->width()) / 2,
        container.y + 4 * (Window::fullscreen + 1)
    );

    lbl_usage->place(4 * (Window::fullscreen + 1), 4 * (Window::fullscreen + 1));

    switch (inventory->capacity) {
    case 0:
        break;
    case 1:
        prepareSize1();
        break;
    case 2:
        prepareSize2();
        break;
    case 4:
        prepareSize4();
        break;
    case 6:
    default:
        prepareSize6();
        break;
    }
}

void InventoryMenu::update() {
    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);

    itemDescription->place(Window::screen.w, Window::screen.h);

    for (unsigned int i = 0; i < inventory->capacity; i++) {
        if (i >= inventory->item.size())
            continue;
        if (SDL_PointInRect(&m, &itemRect[i])) {
            itemDescription->setText(inventory->item[i]->to_string(), "default", hue::font, 3 * container.w / 4);
            itemDescription->place(m.x, m.y);

            if (Window::event.mouseClickLeft()) {
                if (inventory->item[i]->use())
                    inventory->item.erase(inventory->item.begin() + i);
            }
            else if (Window::event.mouseClickRight()) {
                Game::island->addItem(Game::player->position, inventory->item[i]);
                inventory->item.erase(inventory->item.begin() + i);
            }
        }
    }
}

void InventoryMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::blur);
    Manager::DrawFilledRect(&container, hue::ui_background);

    lbl_title->draw();

    unsigned int s = inventory->item.size();
    for (unsigned int i = 0; i < inventory->capacity; i++) {
        if (i < s)
            inventory->item[i]->drawIconAt(itemRect[i]);

        Manager::DrawRect(&itemRect[i], hue::border);
    }

    Manager::DrawRect(&container, hue::border);

    lbl_usage->draw();

    itemDescription->draw();
}

void InventoryMenu::clean() {
    inventory = nullptr;
    lbl_title->destroy();
    lbl_usage->destroy();
    itemDescription->destroy();
}

void InventoryMenu::prepareSize1() {
    int h = container.y + container.h - lbl_title->y() - lbl_title->height();
    int i = 256 + 128 * (Window::fullscreen);

    itemRect.push_back({
        container.x + (container.w - i) / 2,
        lbl_title->y() + lbl_title->height() + (h - i) / 2,
        i,
        i
        });
}

void InventoryMenu::prepareSize2() {
    int h = container.y + container.h - lbl_title->y() - lbl_title->height();
    int i = 192 + 96 * (Window::fullscreen);

    itemRect.push_back({
        container.x + (container.w / 2 - i) / 2,
        lbl_title->y() + lbl_title->height() + (h - i) / 2,
        i,
        i
        });

    itemRect.push_back({
        container.x + (3 * container.w / 2 - i) / 2,
        lbl_title->y() + lbl_title->height() + (h - i) / 2,
        i,
        i
        });
}

void InventoryMenu::prepareSize4() {
    int h = container.y + container.h - lbl_title->y() - lbl_title->height();
    int i = 144 + 72 * (Window::fullscreen);

    itemRect.push_back({
        container.x + (container.w / 2 - i) / 2,
        container.y + (h - i) / 2,
        i,
        i
        });

    itemRect.push_back({
        container.x + (3 * container.w / 2 - i) / 2,
        container.y + (h - i) / 2,
        i,
        i
        });

    itemRect.push_back({
        container.x + (container.w / 2 - i) / 2,
        container.y + container.h - (h / 2 + i) / 2,
        i,
        i
        });

    itemRect.push_back({
        container.x + (3 * container.w / 2 - i) / 2,
        container.y + container.h - (h / 2 + i) / 2,
        i,
        i
        });
}

void InventoryMenu::prepareSize6() {
    int h = container.y + container.h - lbl_title->y() - lbl_title->height();
    int i = 128 + 64 * (Window::fullscreen);

    itemRect.push_back({
        container.x + (container.w / 2 - i) / 2,
        container.y + (h - i) / 2,
        i,
        i
        });

    itemRect.push_back({
        container.x + (3 * container.w / 2 - i) / 2,
        container.y + (h - i) / 2,
        i,
        i
        });

    itemRect.push_back({
        container.x + (container.w - i) / 2,
        container.y + (h - i) / 2,
        i,
        i
        });

    itemRect.push_back({
        container.x + (container.w - i) / 2,
        container.y + container.h - (h / 2 + i) / 2,
        i,
        i
        });

    itemRect.push_back({
        container.x + (container.w / 2 - i) / 2,
        container.y + container.h - (h / 2 + i) / 2,
        i,
        i
        });

    itemRect.push_back({
        container.x + (3 * container.w / 2 - i) / 2,
        container.y + container.h - (h / 2 + i) / 2,
        i,
        i
        });
}
