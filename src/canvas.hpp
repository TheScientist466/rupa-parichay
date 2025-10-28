#pragma once

#include <SFML/Graphics.hpp>
#include <stdint.h>

class Canvas : public sf::Drawable {
public:
    Canvas(const sf::Vector2u texSize);
    ~Canvas();

private:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    uint32_t* m_pixels;
    sf::Texture m_texture;
    sf::Vector2u m_texSize;

    sf::RectangleShape m_shape;
};
