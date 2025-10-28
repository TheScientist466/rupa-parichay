#include "renderer.hpp"

#include "SFML/System/Vector2.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "config.hpp"

#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>

Renderer::Renderer() :
    m_window(sf::VideoMode(WINDOW_SIZE), PROJECT_NAME, sf::Style::Close)
{ 
    m_window.setFramerateLimit(WINDOW_FRAMERATE_LIMIT);

    sf::Vector2u screenSize = sf::VideoMode::getFullscreenModes()[0].size;
    m_window.setPosition((sf::Vector2i)(screenSize - WINDOW_SIZE) / 2);

    if(!ImGui::SFML::Init(m_window)) {
        std::cerr << "Could not init imgui" << std::endl;
        m_imguiInit = false;
        return;
    }
    m_imguiInit = true;
}

Renderer::~Renderer() = default;

int Renderer::run() {
    if(!m_imguiInit) {
        std::cerr << "imgui has not been initialized" << std::endl;
    }
    while(m_window.isOpen()) {
        while(const std::optional event = m_window.pollEvent()) {
            ImGui::SFML::ProcessEvent(m_window, *event);
            if(event->is<sf::Event::Closed>()) {
                m_window.close();
            }
        }
        m_deltaTime = m_deltaClock.restart();
        ImGui::SFML::Update(m_window, m_deltaTime);
        gui();

        m_window.clear();
        ImGui::SFML::Render(m_window);
        m_window.display();
    }
    return 0;
}

void Renderer::gui() {
    ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowSize({INSPECTOR_SIZE_X, WINDOW_SIZE.y});
    ImGui::SetWindowPos({WINDOW_SIZE.x - INSPECTOR_SIZE_X, 0});
    ImGui::End();
}
