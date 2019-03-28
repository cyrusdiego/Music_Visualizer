#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
int main(){
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"Testing");
    while (window.isOpen()) {
    // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Background Colour
        window.clear(sf::Color::Black);

        // Taskbar
        sf::Color taskbar_color(177, 186, 188);
        sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x , 50.f));
        rectangle.setFillColor(taskbar_color);

        //Play Button
        sf::Color button_color(153,0,0);
        sf::CircleShape triangle(20.f,3);
        triangle.setFillColor(button_color);
        triangle.setOrigin(5.0f,5.0f);
        triangle.rotate(210);
        triangle.move(20.0f,45.0f);

        //Pause Button
        sf::Color pause_color(153,0,0);
        sf::RectangleShape rect1(sf::Vector2f(8.0f,40.f));
        sf::RectangleShape rect2(sf::Vector2f(8.0f,40.f));
        rect1.setFillColor(button_color);
        rect2.setFillColor(button_color);
        rect1.move(45.0f,5.0f);
        rect2.move(58.0f,5.0f);

        //Draw the shapes
        window.draw(rectangle);
        window.draw(rect1);
        window.draw(rect2);
        window.draw(triangle);
        window.display();

    }
    return 0;
}
