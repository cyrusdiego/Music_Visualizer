#define GLEW_STATIC // *openGL
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";
const GLchar* fragmentSource = R"glsl(
#version 150 core
out vec4 outColor;
void main()
{
    outColor = vec4(1.0, 1.0, 1.0, 1.0);
}
)glsl";
// comments with *openGL indicate it was from the openGL tutorial
int main(){
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 2;
    // window object
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"Testing", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setActive(true);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat vertices[] = {
         0.0f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    bool running = true;
    while (running) {
    // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                running = false;
            }
            else if (event.type == sf::Event::Resized){
                 // adjust the viewport when the window is resized
                 glViewport(0, 0, event.size.width, event.size.height);
             }
        }

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

        // sets Background to black
        // *openGL
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES,0,3);
        // window.pushGLStates();
        // // //Draw the shapes
        // window.draw(rectangle);
        // window.draw(rect1);
        // window.draw(rect2);
        // window.draw(triangle);
        //
        // window.popGLStates();

        window.display();

    }
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);
    window.close();

    return 0;
}
