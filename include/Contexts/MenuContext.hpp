#ifndef MENU_H
#define MENU_H

#include <Contexts/Context.hpp>
#include <GUI/GUI.hpp>

class MenuContext : public Context {
    std::shared_ptr<GUI::Button> m_play_btn;

    public:
        bool load();
        void update(const float& dt) override;
};

#endif
