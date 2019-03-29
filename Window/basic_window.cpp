#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
// comments with *openGL indicate it was from the openGL tutorial
int main(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    // window object
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"Learning Windows",sf::Style::Default, settings);
    bool running = true;

    float x = 300;
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(300.0f, 600.0f)),
        sf::Vertex(sf::Vector2f(300.0f, 300.0f))
    };
    int change = 0;
    float duration = float();
    sf::Clock clock;
    sf::Music music;
    if (!music.openFromFile("The_Beatles_-_Come_Together-45cYwDMibGo.wav"))
        return -1; // error

    while (running) {
        sf::Time dt = clock.restart();
        duration += dt.asSeconds();
    // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::EventType::Closed)
                running = false;
            if (event.type == sf::Event::EventType::KeyPressed){
              if (event.key.code == sf::Keyboard::Q){
                  running = false;
                }
            }
            //Respond to key pressed events
            if (event.type == sf::Event::EventType::KeyPressed){
              if (event.key.code == sf::Keyboard::C){
                // C key pressed, start animation
                change = 1;
              }
              if(event.key.code == sf::Keyboard::P){
                  music.play();

              }
            }
        }

        // Taskbar
        sf::Color taskbar_color(177, 186, 188);
        sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x , 50.f));
        rectangle.setFillColor(taskbar_color);

        // //Play Button
        // sf::Color button_color(153,0,0);
        // sf::CircleShape triangle(20.f,3);
        // triangle.setFillColor(button_color);
        // triangle.setOrigin(5.0f,5.0f);
        // triangle.rotate(210);
        // triangle.move(20.0f,45.0f);
        //
        // //Pause Button
        // sf::Color pause_color(153,0,0);
        // sf::RectangleShape rect1(sf::Vector2f(8.0f,40.f));
        // sf::RectangleShape rect2(sf::Vector2f(8.0f,40.f));
        // rect1.setFillColor(button_color);
        // rect2.setFillColor(button_color);
        // rect1.move(45.0f,5.0f);
        // rect2.move(58.0f,5.0f);


        if (change == 1 && duration > 0.0001f){
          x += 3.0f;
          if (x != 800){
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

    window.close();

    return 0;
}
