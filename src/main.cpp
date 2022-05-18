#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
int main()
{
    const unsigned WIDTH = 800;
    const unsigned HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Collisions");

    float dt;
    sf::Clock dt_clock;

    window.setFramerateLimit(60);

    const float gridSize = 50.f;

    // player
    const float movementSpeed = 300.f;
    sf::Vector2f velocity;
    sf::RectangleShape player;
    player.setFillColor(sf::Color::Green);
    player.setSize(sf::Vector2f(gridSize, gridSize));

    // walls
    std::vector<sf::RectangleShape> walls;

    sf::RectangleShape wall;
    wall.setFillColor(sf::Color::Red);
    wall.setSize(sf::Vector2f(gridSize, gridSize));
    wall.setPosition(gridSize * 5, gridSize * 5);
    walls.push_back(wall);

    // Collision
    sf::FloatRect nexPos;
    while (window.isOpen())
    {
        dt = dt_clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        velocity.x = 0.f;
        velocity.y = 0.f;
        // player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            velocity.y += -movementSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            velocity.y += movementSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            velocity.x += -movementSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            velocity.x += movementSpeed * dt;

        // collision
        for (auto &wall : walls)
        {
            sf::FloatRect playerBounds = player.getGlobalBounds();
            sf::FloatRect wallBounds = wall.getGlobalBounds();
            nexPos = playerBounds;
            nexPos.left += velocity.x;
            nexPos.top += velocity.y;
            if (wallBounds.intersects(nexPos))
            {

                // Bottom collision
                if (playerBounds.top < wallBounds.top && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height && playerBounds.left < wallBounds.left + wallBounds.width && playerBounds.left + playerBounds.width > wallBounds.left)
                {
                    velocity.y = 0.f;
                    player.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                }
                // Top collision
                if (playerBounds.top > wallBounds.top && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height && playerBounds.left < wallBounds.left + wallBounds.width && playerBounds.top + playerBounds.height > wallBounds.top)
                {
                    velocity.y = 0.f;
                    player.setPosition(playerBounds.left, wallBounds.top + playerBounds.height);
                }

                // Right collision
                if (playerBounds.left < wallBounds.left && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width && playerBounds.top < wallBounds.top + wallBounds.height && playerBounds.top + playerBounds.height > wallBounds.top)
                {
                    velocity.x = 0.f;
                    player.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
                }
                // Left collision
                if (playerBounds.left > wallBounds.left && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width && playerBounds.top < wallBounds.top + wallBounds.height && playerBounds.top + playerBounds.height > wallBounds.top)
                {
                    velocity.x = 0.f;
                    player.setPosition(wallBounds.left + playerBounds.width, playerBounds.top);
                }
            }
        }
        player.move(velocity);

        // collision screen
        // left collision
        if (player.getPosition().x < 0.f)
            player.setPosition(0.f, player.getPosition().y);

        // top collision
        if (player.getPosition().y < 0.f)
            player.setPosition(player.getPosition().x, 0.f);

        // right collision
        if (player.getPosition().x + player.getGlobalBounds().width > WIDTH)
            player.setPosition(WIDTH - player.getGlobalBounds().width, player.getPosition().y);

        // bottom collision
        if (player.getPosition().y + player.getGlobalBounds().height > HEIGHT)
            player.setPosition(player.getPosition().x, HEIGHT - player.getGlobalBounds().height);
        // or we can use player.setPosition(WIDTH-gridSize,player.getPosition().y);

        window.clear();
        window.draw(player);

        for (auto &i : walls)
        {
            window.draw(i);
        }
        window.display();
    }
}