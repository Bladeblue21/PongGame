//The Pong Game
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <cmath>
#include <ctime>


int main()
{
    float screenWidth = 1024.f;
    float screenHeight = 800.f;
    float PI = 3.14159265f;


    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Pong");

    //Ball related things
    float ballRadius = 15.f;
    float ballSpeed = 0.1f;
    float ballAngle = 60 * (PI / 180);

    sf::CircleShape ball(ballRadius);
    ball.setFillColor(sf::Color::Green);
    ball.setPosition((window.getSize().x / 2) - ballRadius, (window.getSize().y / 2) - ballRadius);
    
    //Paddle related things
    float paddleSpeed = 0.125f;

    sf::RectangleShape p1_paddle(sf::Vector2f(25, 100));
    p1_paddle.setFillColor(sf::Color::Cyan);
    p1_paddle.setPosition(54.f, (window.getSize().y / 2) - 50);

    sf::RectangleShape p2_paddle(sf::Vector2f(25, 100));
    p2_paddle.setFillColor(sf::Color::Red);
    p2_paddle.setPosition(window.getSize().x - 74.f, window.getSize().y / 2 - 50);

    //Audio related things
    sf::SoundBuffer pongBoop;
    pongBoop.loadFromFile("ball.wav");

    sf::Sound sound;
    sound.setBuffer(pongBoop);

    //Score related things
    int p1_score = 0;
    int p2_score = 0;

    sf::Font scoreFont;
    scoreFont.loadFromFile("sansation.ttf");

    sf::Text scoreText;
    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(128);
    scoreText.setColor(sf::Color::White);
    scoreText.setPosition(window.getSize().x / 4 , 5);
    



    sf::Clock clock;
    bool isPlaying = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }

            isPlaying = true;
        }

        if (isPlaying)
        {
           
            //Paddle movement
            //Player 1 Controls
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                if (p1_paddle.getPosition().y > 0)
                {
                    p1_paddle.move(0, -paddleSpeed);
                }
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                if (p1_paddle.getPosition().y < window.getSize().y - (p1_paddle.getSize().y))
                {
                    p1_paddle.move(0, paddleSpeed);
                }
            }

            //Player 2 Controls
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if (p2_paddle.getPosition().y > 0)
                {
                    p2_paddle.move(0, -paddleSpeed);
                }
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                if (p2_paddle.getPosition().y < window.getSize().y - (p2_paddle.getSize().y))
                {
                    p2_paddle.move(0, paddleSpeed);
                }
            }

            //Ball behavior
            float ballVelocityX = 0.0;
            float ballVelocityY = 0.1f;

            //Paddle 2 Collision
            if (ball.getGlobalBounds().intersects(p2_paddle.getGlobalBounds()))
            {
                if (ball.getPosition().x + ballRadius > p2_paddle.getPosition().x - p2_paddle.getSize().x / 2   &&
                    ball.getPosition().x + ballRadius < p2_paddle.getPosition().x                               &&
                    ball.getPosition().y + ballRadius >= p2_paddle.getPosition().y - p2_paddle.getSize().y / 2  &&
                    ball.getPosition().y - ballRadius <= p2_paddle.getPosition().y + p2_paddle.getSize().y / 2)
                {
                    ballAngle = PI - ballAngle;
                    
                    sound.play();
                    ball.setPosition(p2_paddle.getPosition().x - (p2_paddle.getSize().x / 2) - ballRadius - 0.1f, ball.getPosition().y);
                }
            }

            //Paddle 1 Collision
            if (ball.getGlobalBounds().intersects(p1_paddle.getGlobalBounds()))
            {
                if (ball.getPosition().x - ballRadius < p1_paddle.getPosition().x + p1_paddle.getSize().x / 2 &&
                    ball.getPosition().x - ballRadius > p1_paddle.getPosition().x                               &&
                    ball.getPosition().y + ballRadius >= p1_paddle.getPosition().y - p1_paddle.getSize().y / 2 &&
                    ball.getPosition().y - ballRadius <= p1_paddle.getPosition().y + p1_paddle.getSize().y / 2)
                {
                    ballAngle = PI - ballAngle;
                    
                    sound.play();
                    ball.setPosition(p1_paddle.getPosition().x + (p1_paddle.getSize().x / 2) + ballRadius + 0.1f, ball.getPosition().y);
                }
            }

            if (ball.getPosition().x > window.getSize().x)
            {
                p1_score++;

                ballAngle = PI - ballAngle;
                ball.setPosition((window.getSize().x / 2) - ballRadius, (window.getSize().y / 2) - ballRadius);
            }

            else if (ball.getPosition().x < 0)
            {
                p2_score++;

                ballAngle = PI - ballAngle;
                ball.setPosition((window.getSize().x / 2) - ballRadius, (window.getSize().y / 2) - ballRadius);
            }

            if (ball.getPosition().y >= window.getSize().y - ballRadius)
            {
                ballAngle = -ballAngle;
            }

            else if (ball.getPosition().y <= 0)
            {
                ballAngle = -ballAngle;
            }

            ball.move((ballSpeed) * std::cos(ballAngle), (ballSpeed) * std::sin(ballAngle));
        }

        scoreText.setString(std::to_string(p1_score) + "            " + std::to_string(p2_score));

        window.clear();
        window.draw(scoreText);
        window.draw(ball);
        window.draw(p1_paddle);
        window.draw(p2_paddle);
        window.display();
    }

    return 0;
}