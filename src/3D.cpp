#include "Engine.h"
#include "Window.h"
#include "Shapes.h"

int main()
{
    // create window
	// Inherit sf::drawable instead of a static pointer

    sf::RenderWindow* s_Window = getWindow({1280, 720}, "MyWindow"); // this is a horrible implementation, need to fix

    // framerate cap, affects speed of rotation
    s_Window->setFramerateLimit(60);

    // view 
    sf::View Camera(sf::Vector2f(0, 0), sf::Vector2f(89, 50)); // 1.7777:1 ratio (1280/720 = 1.7777)
    s_Window->setView(Camera);

    // math engine
    Engine::E3D E3D(60 /*FOV*/);

    // Object list, every new object gets a unique pointer for their coordinates
    std::unique_ptr<Obj> Cube1(new Obj);

    std::unique_ptr<Obj> Cube2(new Obj);

    // initalization of Obj
    Cube1->set_3D_Coordinates(Shape::createCuboid({ 2, 2, 2 }, 1));

    Cube2->set_3D_Coordinates(Shape::createCuboid({ 2, 2, 2 }, 0.5));

	Cube1->translate({ 1, 2, 0 }); // translates rotation of each object, z axis broken
	E3D.translate(Cube1, { 5, 0, 0 }); // rotation at the center

    while (s_Window->isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (s_Window->pollEvent(event))
        {
            // "close requested" event: close the window
            if (event.type == sf::Event::Closed)
            {
                s_Window->close();
            }
        }

        // calculation before clearing screen in case of blinking due to slow cpu

        Cube1->set_3D_Coordinates(E3D.rotationCalculation(Cube1, { 1, 1, 1 }));

        Cube1->set_2D_Coordinates(E3D.applyPerspective(Cube1));

        Cube2->set_3D_Coordinates(E3D.rotationCalculation(Cube2, { 1, 1, 1 }));

        Cube2->set_2D_Coordinates(E3D.applyPerspective(Cube2));

        // clear screen for update
        s_Window->clear(sf::Color::White);

        // draw
        Cube1->DrawCuboid();
        Cube2->DrawCuboid();

        // display everything
        s_Window->display();
    }


    return 0;
}
