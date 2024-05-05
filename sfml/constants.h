#pragma once

#include <SFML/Graphics.hpp>

namespace constants {
    const std::string DinputFileName{ "rez/in.txt" };
    const std::string DoutputFileName{ "rez/out.png" };

    const int pixelSize{ 10 };
    const std::string fontName{ "arialmt.ttf" };
    const sf::Color zeroColor = sf::Color::White;
    const std::vector<sf::Color> colors{ sf::Color::Red,sf::Color::Blue,sf::Color::Cyan, sf::Color::Green, sf::Color::Magenta, sf::Color::Yellow };
}