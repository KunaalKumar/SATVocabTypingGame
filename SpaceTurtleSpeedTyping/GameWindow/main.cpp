#include "gamewindow.h"
#include <QApplication>
#include <iostream>

int main()
{
    //QApplication a(argc, argv);
    //GameWindow w;
    //w.show();
    //return a.exec();
    int const size = 128;
    enum Direction {DOWN, LEFT, RIGHT, UP};
    int x = size, y = DOWN;
    sf::Vector2i source(x, y);

    sf::RenderWindow w;
    w.create(sf::VideoMode(128, 128), "SFML Animation Demo");
    w.setKeyRepeatEnabled(false);

    sf::Texture t;
    sf::Sprite s;

    if (!t.loadFromFile("../runner.png"))
    {
        std::cout << "Error loading player image" <<std::endl;
    }

    s.setTexture(t);

    while(w.isOpen())
    {
        sf::Event e;
        while(w.pollEvent(e))
        {
            switch (e.type) {
            case sf::Event::Closed:
                w.close();
                break;
            case sf::Event::KeyPressed:
                if (e.key.code == sf::Keyboard::Up)
                    source.y = UP;
                else if (e.key.code == sf::Keyboard::Down)
                    source.y = DOWN;
                else if (e.key.code == sf::Keyboard::Right)
                    source.y = RIGHT;
                else if (e.key.code == sf::Keyboard::Left)
                    source.y = LEFT;
                break;


            }
        }
        source.x++;
        if (source.x * size >= t.getSize().x)
            source.x = 0;

        s.setTextureRect(sf::IntRect(source.x * size, source.y *size, size, size));
        w.draw(s);
        w.display();
        w.clear();
    }
}
