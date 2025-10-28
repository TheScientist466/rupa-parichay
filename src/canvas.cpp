#include "canvas.hpp"

Canvas::Canvas(const sf::Vector2u _texSize) :
    m_texSize(_texSize),
    m_texture(_texSize),
    m_shape((sf::Vector2f)_texSize)
{
    m_pixels = new uint32_t[m_texSize.x * m_texSize.y];
    
    for(size_t i = 0; i < m_texSize.x * m_texSize.y; i++) {
        m_pixels[i] = (i % 2) ? 0xffff0000 : 0xff00ff00;
    }
    m_texture.update((uint8_t*)m_pixels);

    m_shape.setTexture(&m_texture);
}

Canvas::~Canvas() {
    delete[] m_pixels;
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape);
}
