#include "directives.hpp"

    ShapeManager::ShapeManager() {}

    void ShapeManager::createShape()
    {
        int select; ShapeType type; std::string name;
        std::cout << "  Dot (0), Line (1), Triangle (2), Square (3),\n  Rectangle (4), Circle (5), Star (6), cancel (7)\n\n";
        std::cout << "  Select shape : "; std::cin >> select;

        type = static_cast<ShapeType>(select);

        switch (type)
        {
            case DOT:       shapes.push_back(new myDot());       break;
            case LINE:      shapes.push_back(new myLine());      break;
            case TRIANGLE:  shapes.push_back(new myTriangle());  break;
            case SQUARE:    shapes.push_back(new mySquare());    break;
            case RECTANGLE: shapes.push_back(new myRectangle()); break;
            case CIRCLE:    shapes.push_back(new myCircle());    break;
            case STAR:      shapes.push_back(new myStar());      break;
            case 7: drawConsoleInterFace();         return; // выход

            default:
            {
                std::cout << " Error! Try again.\n";
                sf::sleep(sf::milliseconds(300));
                drawConsoleInterFace();
                return;
            }
        }

        std::cin.clear(); std::cin.ignore();

        std::cout << "  Enter a name for the shape : "; getline(std::cin, name);

        shapes[(current_shape = shapes.size() - 1)]->setName(name); // выбираем имя + делаем "выбранной" фигурой

        std::cout << "\n  Excellent!\n";
        sf::sleep(sf::milliseconds(300));
        drawConsoleInterFace();
    }

    void ShapeManager::makeAggregate(Parameters parameter)
    {
        if (shapes.size() > 1)
        {
            std::string one, two, name;          // имена агрегатов
            int index_one = -1, index_two = -1;  // индексы агрегатов

            std::cout << "  Enter name shape #1 : "; getline(std::cin, one);
            std::cout << "  Enter name shape #2 : "; getline(std::cin, two);
            std::cout << "  Enter name for aggregate : "; getline(std::cin, name);

            for(int i = 0; i < shapes.size(); ++i)   // использую обычный for, чтобы иметь индекс
            {
                if(shapes[i]->getName() == one)
                    index_one = i;
                else if(shapes[i]->getName() == two)
                    index_two = i;
                else
                {
                    continue;
                }
            }

            if((index_one == -1) || (index_two == -1) )
            {
                std::cout << " Error! Try again.\n";
                sf::sleep(sf::milliseconds(300));
                drawConsoleInterFace();
                return;
            }

            shapes.push_back(new myAggregate(shapes[index_one]->copyShape(), shapes[index_two]->copyShape()));

            if(parameter == REPLACE) // если DUPLICATE, то ничего не делаем, он лишь для "читабельности"
            {
                if(index_one > index_two)  // для устранения путанины с индексами
                {                          // удаляем сначала элемент с бОльшим индексом
                    shapes.erase(shapes.begin()+index_one);
                    shapes.erase(shapes.begin()+index_two);
                }
                else
                {
                    shapes.erase(shapes.begin()+index_two);
                    shapes.erase(shapes.begin()+index_one);
                }
            }

            shapes[(current_shape = shapes.size() - 1)]->setName(name); // выбираем имя + делаем "выбранной" фигурой

            std::cout << "\n  Excellent!\n";
            sf::sleep(sf::milliseconds(300));
            drawConsoleInterFace();
        }
    }

    void ShapeManager::deleteShape(Parameters parameter)
    {
        if (shapes.size() > 0)
        {
            std::string name; int index = -1; // если не переопределим, то удаляем текущую фигуру

            if(parameter == BY_NAME)
            {
                std::cout << "  Enter name shape : "; getline(std::cin, name);

                for(int i = 0; i < shapes.size(); ++i)   // использую обычный for, чтобы иметь индекс
                {
                    if(shapes[i]->getName() == name)
                    {
                        index = i;
                        break;
                    }
                }

                if(index == -1)
                {
                    std::cout << " Error! Try again.\n";
                    sf::sleep(sf::milliseconds(300));
                    drawConsoleInterFace();
                    return;
                }
            }
            if (parameter == CURRENT)
            {
                index = current_shape;
            }

            shapes.erase(shapes.begin()+index);

            current_shape = shapes.size() - 1;

            std::cout << "\n  Excellent!\n";
            sf::sleep(sf::milliseconds(300));
            drawConsoleInterFace();
        }
    }

    void ShapeManager::editShape()
    {
        float one, two; int num;

        std::cout << "  (Enter -1 to keep standard values)\n\n";
        std::cout << "  Shape ID #" << shapes[current_shape]->getID() << std::endl;
        switch (shapes[current_shape]->getType())
        {
            case DOT && SQUARE:
            {
                std::cout << "  Set lenght : "; std:: cin >> one;
                if(one != -1)
                    shapes[current_shape]->setLenght(one);
                break;
            }
            case LINE && RECTANGLE:
            {
                std::cout << "  Set lenght : "; std:: cin >> one;
                std::cout << "  Set thickness : "; std:: cin >> two;
                if(one != -1)
                    shapes[current_shape]->setLenght(one);
                if(two != -1)
                    shapes[current_shape]->setThickness(two);
                break;
            }
            case TRIANGLE:
            {
                std::cout << "  Set radius : "; std:: cin >> one;
                if(one != -1)
                    shapes[current_shape]->setRadius(sf::Vector2f(one, one));
                break;
            }
            case CIRCLE:
            {
                std::cout << "  Set radius : "; std:: cin >> one;
                std::cout << "  Set vertexs : "; std:: cin >> num;
                if(one != -1)
                    shapes[current_shape]->setRadius(sf::Vector2f(one, one));
                if(two != -1)
                    shapes[current_shape]->setVertexs(num);
                break;
            }
            case STAR:
            {
                std::cout << "  Set radius : "; std:: cin >> one;
                std::cout << "  Set inner radius : "; std:: cin >> two;
                std::cout << "  Set vertexs : "; std:: cin >> num;
                if(one != -1)
                    shapes[current_shape]->setRadius(sf::Vector2f(one, one));
                if(one != -1)
                    shapes[current_shape]->setInnerRadius(sf::Vector2f(two, two));
                if(one != -1)
                    shapes[current_shape]->setVertexs(num);
                break;
            }
            case AGGREGATE:
            {
                // оставим на потом
                break;
            }
            default:
                sf::sleep(sf::milliseconds(300));
                drawConsoleInterFace();
                return;
                break;
        }

        std::cout << "  Set origin x : "; std:: cin >> one;
        std::cout << "  Set origin y : "; std:: cin >> two;
        if(one != -1)
            shapes[current_shape]->setOrigin(one, two);
        std::cout << "  Set default position x (global) : "; std:: cin >> one;
        std::cout << "  Set default position y (global) : "; std:: cin >> two;
        if(one != -1)
            shapes[current_shape]->changeDefaultPosition(one, two);

        sf::sleep(sf::milliseconds(300));
        drawConsoleInterFace();
        return;
    }

    void ShapeManager::createConfig()
    {
        std::ofstream fout;
        std::string file_name;
        std::cout << "  Enter file name : ";
        getline(std::cin, file_name);
        fout.open(file_name, std::ifstream::app);
        fout.unsetf(std::ios::floatfield);
        fout.precision(10);

        if(!fout.is_open())
        {
            std::cout << " Error! Try again.\n";
            sf::sleep(sf::milliseconds(300));
            drawConsoleInterFace();
            return;
        }
        else
        {
            for(int i = 0; i < shapes.size(); ++i)
            {
                fout << "\n  " <<static_cast<int>(shapes[i]->getType()) << "    " << shapes[i]->getName()
                << "    " << shapes[i]->getPosition().x << "    " << shapes[i]->getPosition().y
                << "    " << shapes[i]->getOrigin().x << "    " << shapes[i]->getOrigin().y
                << "    " << shapes[i]->getScale().x << "    " << shapes[i]->getScale().y
                << "    " << shapes[i]->getRotation() << "    " << shapes[i]->getFillColor().toInteger()
                << "    " << shapes[i]->getVisible() << "    " << shapes[i]->getDance()
                << "    " << shapes[i]->getDisco();
            }
        }
        fout.close();

        std::cout << "\n  Excellent!\n";
        sf::sleep(sf::milliseconds(300));
        drawConsoleInterFace();
    }

    void ShapeManager::readConfig()
    {
        std::ifstream fin;
        std::string file_name;
        std::cout << " Enter file name : ";
        getline(std::cin, file_name);

        fin.open(file_name);

        if(!fin.is_open())
        {
            std::cout << " Error! Try again.\n";
            sf::sleep(sf::milliseconds(300));
            drawConsoleInterFace();
            return;
        }
        else
        {
            shapes.clear();

            std::string name;
            sf::Uint32 color;

            int i = 0;
            int type;
            float pos_x;
            float pos_y;
            float origin_x;
            float origin_y;
            float scale_x;
            float scale_y;
            float rotation;
            bool visible;
            bool disco;
            bool dance;

            while (!fin.eof())
            {
                fin >> type;
                fin >> name;
                fin >> pos_x;
                fin >> pos_y;
                fin >> origin_x;
                fin >> origin_y;
                fin >> scale_x;
                fin >> scale_y;
                fin >> rotation;
                fin >> color;
                fin >> visible;
                fin >> dance;
                fin >> disco;

                switch (type)
                {
                    case DOT:       shapes.push_back(new myDot());       break;
                    case LINE:      shapes.push_back(new myLine());      break;
                    case TRIANGLE:  shapes.push_back(new myTriangle());  break;
                    case SQUARE:    shapes.push_back(new mySquare());    break;
                    case RECTANGLE: shapes.push_back(new myRectangle()); break;
                    case CIRCLE:    shapes.push_back(new myCircle());    break;
                    case STAR:      shapes.push_back(new myStar());      break;
                    case 7: drawConsoleInterFace();         return; // выход
                    default:
                    {
                        std::cout << " Error! Try again.\n";
                        sf::sleep(sf::milliseconds(300));
                        drawConsoleInterFace();
                        return;
                    }
                }

                shapes[i]->setName(name);
                shapes[i]->setPosition(pos_x, pos_y);
                shapes[i]->setOrigin(origin_x, origin_y);
                shapes[i]->setScale(scale_x, scale_y);
                shapes[i]->setRotation(rotation);
                shapes[i]->setFillColor(sf::Color(color));

                if(!visible) // по-дефолту видима
                    shapes[i]->setVisible();
                if(dance)
                    shapes[i]->setDance();
                if(disco)
                    shapes[i]->setDisco();
                ++i;
            }
        }
        current_shape = shapes.size() - 1;
        fin.close();

        std::cout << "\n  Excellent!\n";
        sf::sleep(sf::milliseconds(300));
        drawConsoleInterFace();
    }

    void ShapeManager::changeRGBAColor()
    {
        size_t r, g, b, a;
        std::cout << "  R: "; std::cin >> r;
        std::cout << "  G: "; std::cin >> g;
        std::cout << "  B: "; std::cin >> b;
        std::cout << "  A: "; std::cin >> a;

        shapes[current_shape]->setFillColor(sf::Color(r, g, b, a));

        std::cout << " Excellent!\n";
        sf::sleep(sf::milliseconds(300));

        drawConsoleInterFace();
    }

    void ShapeManager::switchShape()
    {
        if(current_shape == (shapes.size() - 1))
            current_shape = 0;
        else
            ++current_shape;
    }

    void ShapeManager::rotateShape(Parameters direction)
    {
        rotation = shapes[current_shape]->getRotation();

        if(direction == LEFT)
        {
            if((rotation - rotation_step) < 0.f)
                shapes[current_shape]->setRotation(rotation -= rotation_step + 360.f);
            else
                shapes[current_shape]->setRotation(rotation -= rotation_step);
        }
        else if (direction == RIGHT)
        {
            if((rotation + rotation_step) > 360.f)
                shapes[current_shape]->setRotation(rotation += rotation_step - 360.f);
            else
                shapes[current_shape]->setRotation((rotation += rotation_step));
        }
        else
            return;
    }

    void ShapeManager::drawConsoleInterFace()
    {
        system("cls");
        std::cout << "   [1] Add new shape\n";
        std::cout << "   [2] Make agregate (duplicate)\n";
        std::cout << "   [3] Make agregate (replace)\n";
        std::cout << "   [4] Delete shape\n";
        std::cout << "   [5] Delete by name\n";
        std::cout << "   [6] Create config\n";
        std::cout << "   [7] Read from config\n";
        std::cout << "   [8] Engine Settings\n\n";
        std::cout << " [Tab] Change shape\n";
        std::cout << "   [F] Change color\n";
        std::cout << "   [G] Change color RGBA\n";
        std::cout << "   [T] Change tracing\n";
        std::cout << "   [C] Change colission\n";
        std::cout << "   [V] Change visible\n\n";
        std::cout << "   [J] Gonna dance!\n";
        std::cout << "   [H] Gonna disco!\n\n";
        std::cout << "   [Z] Scale +\n";
        std::cout << "   [X] Scale -\n";
        std::cout << "   [Q] Rotation left\n";
        std::cout << "   [E] Rotation right\n";
        std::cout << "   [R] Reset position\n";
        std::cout << "   [B] Edit shape\n";
        std::cout << "\n------------------------------------------------------------------------------------\n";
        for(const auto &shape : shapes)
        {
            std:: cout << "  " << shape->getName();
        }
        std::cout << "\n------------------------------------------------------------------------------------\n";
    }

    void ShapeManager::engineSettings()
    {
        int select, r, g, b, a;
        while(true)
        {
            system("cls");
            std::cout << "  [1] Set window size (" << weight << "x" << height << ")\n";
            std::cout << "  [2] Set fps mode (" << fps_mode << ")\n";
            std::cout << "  [3] Set antialiasing level (" << antialiasing << ")\n";
            std::cout << "  [4] Set background color ("
            << static_cast<int>(background_color.r) << ", "
            << static_cast<int>(background_color.r) << ", "
            << static_cast<int>(background_color.r) << ", "
            << static_cast<int>(background_color.r) << ")\n";
            std::cout << "  [5] Set trace period (" << trace_period << ")\n";
            std::cout << "  [6] Set shape move speed (" << x_right << ")\n";
            std::cout << "  [7] Set shape scale speed (+"<< scale_plus << " -" << scale_minus << ")\n";
            std::cout << "  [8] Set shape rotation speed (" << rotation_step << ")\n";
            std::cout << "  [9] Back (apply changes)\n";
            std::cout << "------------------------------------------------------------------------------------\n";
            std::cout << "  Select : "; std::cin >> select;
            std::cout << "------------------------------------------------------------------------------------\n";

            switch (select)
            {
            case 1:
                std::cout << "  Weight : "; std::cin >> weight;
                std::cout << "  Height : "; std::cin >> height;
                break;
            case 2:
                std::cout << "  FPS mode : "; std::cin >> fps_mode;
                break;
            case 3:
                std::cout << "  Antialiasing level : "; std::cin >> antialiasing;
                break;
            case 4:
                std::cout << "  R : "; std::cin >> r;
                std::cout << "  G : "; std::cin >> g;
                std::cout << "  B : "; std::cin >> b;
                std::cout << "  A : "; std::cin >> a;
                background_color = sf::Color(r, g, b, a);
                break;
            case 5:
                std::cout << "  Trace period : "; std::cin >> trace_period;
                break;
            case 6:
                std::cout << "  UP(-) : "; std::cin >> y_up;
                std::cout << "  DOWN(+) : "; std::cin >> y_down;
                std::cout << "  LEFT(-) : "; std::cin >> x_left;
                std::cout << "  RIGHT(+) : "; std::cin >> x_right;
                break;
            case 7:
                std::cout << "  Scale (1...N) : "; std::cin >> scale_plus;
                std::cout << "  Scale (0...1) : "; std::cin >> scale_minus;
                break;
            case 8:
                std::cout << "  Rotation speed : "; std::cin >> rotation_step;
                break;
            case 9:
                apply_changes = true;
                drawConsoleInterFace();
                return;
                break;
            default:
                apply_changes = true;
                drawConsoleInterFace();
                return;
                break;
            }
        }
    }

    void ShapeManager::start()
    {
        drawConsoleInterFace();

        sf::RenderWindow window(sf::VideoMode(weight, height), title);
        sf::ContextSettings settings; settings.antialiasingLevel = antialiasing;
        window.setFramerateLimit(fps_mode);

        while (window.isOpen())
	    {
            if (apply_changes)
            {
                apply_changes = false;

                window.close();
                window.create(sf::VideoMode(weight, height), title);

                window.setFramerateLimit(fps_mode);
                settings.antialiasingLevel = antialiasing;
            }

	    	// Обрабатываем очередь событий в цикле
	    	sf::Event event;
	    	while (window.pollEvent(event))
	    	{
	    		if (event.type == sf::Event::Closed)
	    			window.close();
                if (event.type == sf::Event::KeyPressed)
                {
                    // Пункты меню
                    if (event.key.code == sf::Keyboard::Num1)
                    {
                        createShape();
                    }
                    if (event.key.code == sf::Keyboard::Num7)
                    {
                        readConfig();
                    }
                    if (event.key.code == sf::Keyboard::Num8)
                    {
                        engineSettings();
                    }

                    if (shapes.size() > 0) // пока фигур не существует - блокируем
                    {
                        // Пункты меню
                        if (event.key.code == sf::Keyboard::Num2)
                        {
                            makeAggregate(DUPLICATE);
                        }
                        if (event.key.code == sf::Keyboard::Num3)
                        {
                            makeAggregate(REPLACE);
                        }
                        if (event.key.code == sf::Keyboard::Num4)
                        {
                            deleteShape(CURRENT);
                        }
                        if (event.key.code == sf::Keyboard::Num5)
                        {
                            deleteShape(BY_NAME);
                        }
                        if (event.key.code == sf::Keyboard::Num6)
                        {
                            createConfig();
                        }

                        // Управление фигурой
                        if (event.key.code == sf::Keyboard::Tab)
                        {
                            switchShape();
                        }
                        if (event.key.code == sf::Keyboard::F)
                        {
                            shapes[current_shape]->changePresetColor(); // у текущей фигуры
                        }
                        if (event.key.code == sf::Keyboard::G)
                        {
                            changeRGBAColor();  // у текущей фигуры
                        }
                        if (event.key.code == sf::Keyboard::H)
                        {
                            shapes[current_shape]->setDisco();
                        }
                        if (event.key.code == sf::Keyboard::J)
                        {
                            shapes[current_shape]->setDance();
                        }
                        if (event.key.code == sf::Keyboard::V)
                        {
                            shapes[current_shape]->setVisible();
                        }
                        if (event.key.code == sf::Keyboard::B)
                        {
                            editShape();
                        }
                        if (event.key.code == sf::Keyboard::C)
                        {
                            check_colission = !check_colission;
                        }
                        if (event.key.code == sf::Keyboard::T)
                        {
                            global_tracing = !global_tracing;
                        }
                    }
                }
            }
            if (shapes.size() > 0) // пока фигур не существует - блокируем
            {
                // Движение фигуры
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    shapes[current_shape]->move(0, y_up);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    shapes[current_shape]->move(0, y_down);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    shapes[current_shape]->move(x_left, 0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    shapes[current_shape]->move(x_right, 0);
                }
                //Ротация фигуры
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                {
                    rotateShape(LEFT);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                {
                    rotateShape(RIGHT);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                {
                    shapes[current_shape]->setDefaultPosition();
                }
                // Деформация фигуры
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                {
                    shapes[current_shape]->scale(1.1f, 1.1f);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
                {
                    shapes[current_shape]->scale(0.9f, 0.9f);
                }
            }
            // Механизм следа фигуры
            if(!global_tracing)
            {
                window.clear(background_color);
            }
            else
            {
                static int trace_count = 0;
                if( (trace_count % trace_period) == 0)
                {
                    // очищаем экран с определённой переодичностью
                    // в обычном случае, эта функция всегда должна
                    // вызываться перед отрисовкой
                    window.clear(background_color);
                    trace_count = 0;
                }
                ++trace_count;
            }
            for(const auto &shape : shapes) // Финальная отрисовка фигуры
            {
                if (check_colission)
                {
                    for(int i = 0; i < shapes.size(); i++)
                    {
                        if (shapes[current_shape]->getGlobalBounds().intersects(shapes[i]->getGlobalBounds()) && (current_shape != i))
                        {
                            // Моргаем при коллизии
                            shapes[current_shape]->changePresetColor();
                        }
                    }
                }
                if(shape->getDance())       // Автодвижение фигуры
                {
                    shape->justDance();
                }
                if(shape->getDisco())       // Мигание фигуры
                {
                    shape->justDisco();
                }
                                        // Если невидима, то зачем рисовать?) (экономит много ресурсов)
                if(shape->getVisible()) // Но управлять фигурой всё так же можно!
                {
                    window.draw(*shape);
                }
            }
            window.display();
        }
    }
