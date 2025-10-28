#include "canvas.hpp"
#include "config.hpp"

#include <imgui.h>

Canvas::Canvas(const sf::Vector2u _texSize) :
    m_texSize(_texSize),
    m_texture(_texSize),
    m_shape((sf::Vector2f)_texSize),
    m_brushSize(DEFAULT_BRUSH_SIZE)
{
    m_pixels = new uint32_t[m_texSize.x * m_texSize.y];
    
    for(size_t i = 0; i < m_texSize.x * m_texSize.y; i++) {
        m_pixels[i] = 0;
    }
    m_texture.update((uint8_t*)m_pixels);

    m_shape.setTexture(&m_texture);
}

Canvas::~Canvas() {
    delete[] m_pixels;
}

void Canvas::update(sf::Time deltaTime) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_parentWindow);
        if(mousePos.x > 0 && mousePos.x < m_texSize.x &&
           mousePos.y > 0 && mousePos.y < m_texSize.x) {
            for(unsigned int y = mousePos.y - m_brushSize; y <= mousePos.y + m_brushSize; y++) {
                for(unsigned int x = mousePos.x - m_brushSize; x <= mousePos.x + m_brushSize; x++) {
                    m_pixels[y * m_texSize.x + x] = 0xffffffff;
                }
            }
                    
            m_texture.update((uint8_t*)m_pixels);
        }
    }
} 

void Canvas::setParentWindow(sf::RenderWindow* _windowPtr) {
    m_parentWindow = _windowPtr;
}

void Canvas::gui() {
    ImGui::DragInt("Brush Size", &m_brushSize);
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape);
}
