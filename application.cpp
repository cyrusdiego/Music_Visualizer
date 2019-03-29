#include "globals.h"
#include "application.h"
#include "iostream"
application::application(const std::string title) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode::getDesktopMode(), title,sf::Style::Default, settings);
    music.openFromFile("The_Beatles_-_Come_Together-45cYwDMibGo.wav");
    rectangle.setSize(sf::Vector2f(window.getSize().x , 50.f));
}

application::~application() {}

void application::run() {
    while(true) {
        processEvents();
        updateScreen();
        renderScreen();
    }
}

void application::processEvents() {
    if(window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Q)
                    window.close();
                if (event.key.code == sf::Keyboard::C){
                  // C key pressed, start animation
                  change = 1;
                }
                if(event.key.code == sf::Keyboard::P) {
                    music.play();
                }
                break;
        }
    }
}

void application::updateScreen() {
    dt = clock.restart();
    duration += dt.asSeconds();

    sf::Color taskbar_color(177, 186, 188);
    rectangle.setFillColor(taskbar_color);

    if (change == 1 && duration > 0.0001f){
        x += 3.0f;
        if (x != 800){
            std::cout<< "went in "<< std::endl;
            // Reset frame time and set new color for circle
            duration = 0;
            line[1] = sf::Vertex(sf::Vector2f(300,x));
        } else {
            // Stop animation
            change = 0;
        }
    }
}

void application::renderScreen() {
    window.clear(sf::Color::Black);
    window.draw(line, 2, sf::Lines);
    window.draw(rectangle);
    window.display();
}
