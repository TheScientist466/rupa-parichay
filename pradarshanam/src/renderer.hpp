#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

#include "canvas.hpp"
#include "program_states.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();

    [[nodiscard]] int run();

private:
    sf::RenderWindow m_window;
    bool m_imguiInit;
    sf::Clock m_deltaClock;
    sf::Time m_deltaTime;
    bool m_modeDebug;

    // Canvas m_canvas;
    
    ProgramStateDispatcher m_currStateDispatcher;
};

