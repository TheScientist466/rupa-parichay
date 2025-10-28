#include "renderer.hpp"

#include "config.hpp"

Renderer::Renderer() :
    m_window(sf::VideoMode(WINDOW_SIZE), PROJECT_NAME, sf::Style::Close)
{ 
    m_window.setFramerateLimit(WINDOW_FRAMERATE_LIMIT);
}

Renderer::~Renderer() = default;

int Renderer::run() {
    while(m_window.isOpen()) {
        while(const std::optional event = m_window.pollEvent()) {
            if(event->is<sf::Event::Closed>()) {
                m_window.close();
            }
        }
        m_deltaTime = m_deltaClock.restart();
        m_window.clear();
        m_window.display();
    }
    return 0;
}
