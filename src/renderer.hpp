#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

class Renderer {
public:
    Renderer();
    ~Renderer();

    [[nodiscard]] int run();

private:
    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;
    sf::Time m_deltaTime;
    bool m_modeDebug;
};
