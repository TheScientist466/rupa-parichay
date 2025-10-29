#include "canvas.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Mouse.hpp"
#include "config.hpp"

#include <imgui.h>

Canvas::Canvas(const sf::Vector2u _texSize) :
    m_texSize(_texSize),
    m_texture(_texSize),
    m_shape((sf::Vector2f)_texSize),
    m_brushSize(DEFAULT_BRUSH_SIZE),
    m_modeEraser(false),
    m_brushIndicator(DEFAULT_BRUSH_SIZE),
    m_brushShape(DEFAULT_BRUSH_SIZE)
{
    m_texture.clear(sf::Color::Black);
    m_shape.setTexture(&m_texture.getTexture());
   
    m_brushShape.setOrigin(sf::Vector2f(DEFAULT_BRUSH_SIZE, DEFAULT_BRUSH_SIZE));

    m_brushIndicator.setOrigin(sf::Vector2f(DEFAULT_BRUSH_SIZE, DEFAULT_BRUSH_SIZE));
    m_brushIndicator.setFillColor(sf::Color::Transparent);
    m_brushIndicator.setOutlineColor(sf::Color::Green);
    m_brushIndicator.setOutlineThickness(2);
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
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape);
    target.draw(m_brushIndicator);
}
