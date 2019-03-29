#include "globals.h"
#include "application.h"
#include "iostream"
application::application(const std::string title) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode::getDesktopMode(), title,sf::Style::Default, settings);

}

application::~application() {}

void application::run() {
    bool running = true;
    float x = 300;
    int change = 0;
    sf::Vertex line[2] = {
        sf::Vertex(sf::Vector2f(300.0f, 600.0f)),
        sf::Vertex(sf::Vector2f(300.0f, 300.0f))
    };
    while(running) {
        dt = clock.restart();
        duration += dt.asSeconds();

        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Q)
                        running = false;
                    if (event.key.code == sf::Keyboard::C){
                      // C key pressed, start animation
                      change = 1;
                    }
                    break;
            }
            sf::Color taskbar_color(177, 186, 188);
            sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x , 50.f));
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

            // //Draw the shapes
            window.clear(sf::Color::Black);
            window.draw(line, 2, sf::Lines);
            window.draw(rectangle);
            // window.draw(rect1);
            // window.draw(rect2);
            // window.draw(triangle);
            window.display();
        }
    }
    window.close();

}
