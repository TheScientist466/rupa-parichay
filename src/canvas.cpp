#include "canvas.hpp"
#include "config.hpp"

#include <imgui.h>
#include <iostream>

Canvas::Canvas(const sf::Vector2u _texSize) :
    m_texSize(_texSize),
    m_texture(_texSize),
    m_shape((sf::Vector2f)_texSize),
    m_brushSize(DEFAULT_BRUSH_SIZE),
    m_modeEraser(false),
    m_brushIndicator(DEFAULT_BRUSH_SIZE),
    m_brushShape(DEFAULT_BRUSH_SIZE),
    m_pixelatorFactor(DEFAULT_PIXELATOR_FACTOR),
    m_usePixelator(false)
{
    m_shape.setTexture(&m_texture.getTexture());
    m_texture.clear(sf::Color::Black);
   
    m_brushShape.setOrigin(sf::Vector2f(DEFAULT_BRUSH_SIZE, DEFAULT_BRUSH_SIZE));

    m_brushIndicator.setOrigin(sf::Vector2f(DEFAULT_BRUSH_SIZE, DEFAULT_BRUSH_SIZE));
    m_brushIndicator.setFillColor(sf::Color::Transparent);
    m_brushIndicator.setOutlineColor(sf::Color::Green);
    m_brushIndicator.setOutlineThickness(2);

    if(!m_pixelator.loadFromFile("./assets/pixelator.glsl", sf::Shader::Type::Fragment)) {
        std::cerr << "Could not load pixelator shader" << std::endl;
    }
}

Canvas::~Canvas() = default;

void Canvas::update(sf::Time deltaTime) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_parentWindow);
    m_brushIndicator.setPosition((sf::Vector2f)mousePos);
    m_brushShape.setPosition(sf::Vector2f(mousePos.x, WINDOW_SIZE.y - mousePos.y));
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if(mousePos.x > 0 && mousePos.x < m_texSize.x && mousePos.y > 0 && mousePos.y < m_texSize.y) 
            m_texture.draw(m_brushShape);
    }
    m_pixelator.setUniform("tex", m_texture.getTexture());
    m_pixelator.setUniform("factor", m_pixelatorFactor);
} 

void Canvas::setParentWindow(sf::RenderWindow* _windowPtr) {
    m_parentWindow = _windowPtr;
}

void Canvas::gui() {
    if(ImGui::Button("Clear")) {
        m_texture.clear(sf::Color::Black);
    }
    if(ImGui::DragInt("Brush Size", &m_brushSize)) {
        m_brushShape.setPosition({0, 0});
        m_brushShape.setRadius(m_brushSize);
        m_brushShape.setOrigin(sf::Vector2f(m_brushSize, m_brushSize));

        m_brushIndicator.setPosition({0, 0});
        m_brushIndicator.setRadius(m_brushSize);
        m_brushIndicator.setOrigin(sf::Vector2f(m_brushSize, m_brushSize));
    }
    if(ImGui::Checkbox("Eraser Mode", &m_modeEraser)) {
        m_brushIndicator.setOutlineColor(m_modeEraser ? sf::Color::Red : sf::Color::Green);
        m_brushShape.setFillColor(m_modeEraser ? sf::Color::Black : sf::Color::White);
    }
    ImGui::Checkbox("Use Pixelator", &m_usePixelator);
    ImGui::DragFloat("Pixelator Factor", &m_pixelatorFactor, 1.f, 0.f, 0.f, "%.2f");
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(m_usePixelator)
        target.draw(m_shape, &m_pixelator);
    else 
        target.draw(m_shape);
    target.draw(m_brushIndicator);
}
