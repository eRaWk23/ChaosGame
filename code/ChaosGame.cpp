// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Timber Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;
    Vector2f newVertex;
    Vector2f newPoint;
    Vector2f currPoint;
    int randCurrVertex;      


	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/
        if(points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
            
            Vector2f fourthClick = points[0];
            if(points.size() > 1)
            {
                fourthClick = points[points.size() - 1];
            }

            randCurrVertex = rand() % (3 - 1 + 1) + 1;
            newVertex = vertices[randCurrVertex - 1];
            currPoint = fourthClick;
            for (int i = 0; i < 50; i++)
            {
                randCurrVertex = rand() % (3 - 1 + 1) + 1;
                newVertex = vertices[randCurrVertex - 1];
                newPoint.x = (newVertex.x + currPoint.x) / 2;
                newPoint.y = (newVertex.y + currPoint.y) / 2;
            }

            for (int i = 0; i < 50; ++i)
            {
                randCurrVertex = rand() % (3 - 1 + 1) + 1;
                newVertex = vertices[randCurrVertex - 1];
                newPoint.x = (newVertex.x + currPoint.x) /2;
                newPoint.y = (newVertex.y + currPoint.y) /2;
                points.push_back(newPoint);
                currPoint = newPoint;
            }
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();

        sf::Font font;
        if (!font.loadFromFile("KOMIKAP_.ttf")) 
        {
            cout << "Error";
        }
        else
        {
            sf::Text text;
            text.setFont(font); 
            text.setString("Click three random places on the screen.\nThen, click a fourth point to mark where we will start");
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::Green);
            text.setStyle(sf::Text::Bold | sf::Text::Underlined);
            window.draw(text);
        }

        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        for(int i = 0; i < points.size(); i++)
        {
            RectangleShape rectUser(Vector2f(2, 2));
            rectUser.setPosition(Vector2f(points[i].x, points[i].y));
            rectUser.setFillColor(Color::Blue);
            window.draw(rectUser);
        }
        window.display();
    }
  
}