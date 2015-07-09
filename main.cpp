#include <iostream>
#include <random>

#include "Space.h"

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

class Application {
    bool m_running;
    sf::Window &m_window;
    Space m_space;
public:
    Application(sf::Window &window)
        : m_running(false)
        , m_window(window)
    {
        std::random_device device;
        std::mt19937 gen(device());
        std::uniform_real_distribution<double> dist;

        for(int i = 0; i < 100000; ++i) {
            double x = dist(gen);
            double y = dist(gen);

            x = x * 2.0 - 1.0;
            y = y * 2.0 - 1.0;

            m_space.addParticle(std::make_shared<Particle>(x, y));
        }
    }

    void draw()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBegin(GL_POINTS);
        for(ParticlePtr particle : m_space) {
            const Particle::Position &position = particle->position();
            glVertex2d(position.first, position.second);
        }
        glEnd();

        m_window.display();
    }

    int run() {
        m_running = true;
        while(m_running) {
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    // end the program
                    m_running = false;
                }
                else if (event.type == sf::Event::Resized)
                {
                    // adjust the viewport when the window is resized
                    glViewport(0, 0, event.size.width, event.size.height);
                }
            }

            m_space.tick();
            this->draw();
        }

        return 0;
    }
};

int main()
{
    sf::Window window(sf::VideoMode(800, 600), "OpenGL");
    Application app(window);

    return app.run();
}

