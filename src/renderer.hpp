#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

class Renderer {
public:
    Renderer();
    ~Renderer();

    [[nodiscard]] int run();

private:
    void gui();

    sf::RenderWindow m_window;
    bool m_imguiInit;
    sf::Clock m_deltaClock;
    sf::Time m_deltaTime;
    bool m_modeDebug;
};
