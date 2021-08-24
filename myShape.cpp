#include "directives.hpp"

// Наследуем sf::Shape, тем самым получаем доступ
// и к sf::Drawable, и к sf::Transformable

//myShape
////////////////////////////////////////////////////////////////
    myShape* myShape::copyShape()
    {
        return nullptr;
    }

    void myShape::setDefaultPosition()
    {
        setPosition(m_x, m_y);
    }

    void myShape::changeDefaultPosition(float x, float y)
    {
        m_x = x; m_y = y;
    }

    void myShape::changePresetColor()
    {
        static int current_colour = 0; //
        switch (current_colour)
        {
        case 0: setFillColor(sf::Color::Cyan); break;
        case 1: setFillColor(sf::Color::Red); break;
        case 2: setFillColor(sf::Color::Green); break;
        case 3: setFillColor(sf::Color::Blue); break;
        case 4: setFillColor(sf::Color::Yellow); break;
        case 5: setFillColor(sf::Color::Magenta); break;
        case 6: setFillColor(sf::Color::Black); break;
        case 7: setFillColor(sf::Color::White); current_colour = -1 ;break;
        }
        ++current_colour;
    }

    void myShape::justDance()
    {
        static float speed = 0.5f;
        static float x = 12.f * speed;
        static float y = 12.f * speed;
        static int period = 100;
        static int i = -1;

        ++i;

        if (i < period)
        {
            move(x, y);
        }
        else if (i < period*2)
        {
            move(0.f, -y);
        }
        else if (i < period*3)
        {
            move(-x, y);
        }
        else if (i < period*4)
        {
            move(0.f, -y);
        }
        else
        {
            i = -1;
        }
    }

    void myShape::justDisco()
    {
        static int speed = 1; // highter == slowly
        static int i = 0;
        if((i % speed) == 0)
        {
            changePresetColor();
            i = 0;
        }
        ++i;
    }

    void myShape::setName(const std::string &name)
    {
        m_name = name;
    }

    void myShape::setType(ShapeType type)
    {
        m_type = type;
    }

    void myShape::setVisible()
    {
        m_visible = !m_visible;
    }

    void myShape::setDance()
    {
        m_dance = !m_dance;
    }

    void myShape::setDisco()
    {
        m_disco = !m_disco;
    }

    const std::string& myShape::getName() const
    {
        return m_name;
    }

    ShapeType myShape::getType() const
    {
        return m_type;
    }

    bool myShape::getVisible() const
    {
        return m_visible;
    }

    bool myShape::getDance() const
    {
        return m_dance;
    }

    bool myShape::getDisco() const
    {
        return m_disco;
    }

    bool myShape::getID() const
    {
        return m_id;
    }

    // Сделано для агрегатов
    void myShape::setFillColor(sf::Color color)
    {
        sf::Shape::setFillColor(color);
    }

    const sf::Color& myShape::getFillColor() const
    {
        return sf::Shape::getFillColor();
    }

//myCircle
////////////////////////////////////////////////////////////////

    // Конструкторы
    myCircle::myCircle()
    {
        setOrigin(m_radius.x, m_radius.y);
        setDefaultPosition();
        setType(CIRCLE);
        update();
    }

    myCircle::myCircle(const sf::Vector2f& radius, int vertexs) :
        m_radius(radius), m_vertexs(vertexs)
    {
        setOrigin(m_radius.x, m_radius.y);
        setDefaultPosition();
        setType(CIRCLE);
        update();
    }

    myCircle::myCircle(float radius, int vertexs) :
        m_radius(sf::Vector2f(radius, radius)), m_vertexs(vertexs)
    {
        setOrigin(m_radius.x, m_radius.y);
        setDefaultPosition();
        setType(CIRCLE);
        update();
    }

    // Геттеры-сеттеры
    void myCircle::setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        update();
    }

    void myCircle::setVertexs(int vertexs)
    {
        m_vertexs = vertexs;
        update();
    }

    const sf::Vector2f myCircle::getRadius() const
    {
        return m_radius;
    }

    int myCircle::getVertexs() const
    {
        return m_vertexs;
    }

    // Переопределенные методы
    myShape* myCircle::copyShape()
    {
        return new myCircle(*this);
    }

    // Метод рисования фигуры
    std::size_t myCircle::getPointCount() const
    {
        return m_vertexs;
    }

    sf::Vector2f myCircle::getPoint(std::size_t index) const
    {
        static const float pi = 3.141592654f;

        float angle = index * 2 * pi / getPointCount() - pi/2;
        float x = std::cos(angle) * m_radius.x * 2;
        float y = std::sin(angle) * m_radius.y * 2;

        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }

//myTriangle
////////////////////////////////////////////////////////////////

    // Конструкторы
    myTriangle::myTriangle()
    {
        setOrigin(m_radius.x, m_radius.y);
        setDefaultPosition();
        setType(TRIANGLE);
        update();
    }

    myTriangle::myTriangle(const sf::Vector2f& radius) :
        m_radius(radius)
    {
        setOrigin(m_radius.x, m_radius.y);
        setDefaultPosition();
        setType(TRIANGLE);
        update();
    }

    myTriangle::myTriangle(float radius) :
        m_radius(sf::Vector2f(radius, radius))
    {
        setOrigin(m_radius.x, m_radius.y);
        setDefaultPosition();
        setType(TRIANGLE);
        update();
    }

    // Геттеры-сеттеры
    void myTriangle::setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        update();
    }

    const sf::Vector2f myTriangle::getRadius() const
    {
        return m_radius;
    }

    // Переопределенные методы
    myShape* myTriangle::copyShape()
    {
        return new myTriangle(*this);
    }

    // Метод рисования фигуры
    std::size_t myTriangle::getPointCount() const
    {
        return m_vertexs;
    }

    sf::Vector2f myTriangle::getPoint(std::size_t index) const
    {
        static const float pi = 3.141592654f;

        float angle = index * 2 * pi / getPointCount() - pi/2;
        float x = std::cos(angle) * m_radius.x * 2;
        float y = std::sin(angle) * m_radius.y * 2;

        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }


//mySquare
////////////////////////////////////////////////////////////////

    // Конструкторы
    mySquare::mySquare()
    {
        setOrigin(m_length/2, m_length/2);
        setDefaultPosition();
        setType(SQUARE);
        update();
    }

    mySquare::mySquare(float length) :
        m_length(length)
    {
        setOrigin(m_length/2, m_length/2);
        setDefaultPosition();
        setType(SQUARE);
        update();
    }

    // Геттеры-сеттеры
    void mySquare::setLenght(float length)
    {
        m_length = length;
        update();
    }

    float mySquare::getLenght() const
    {
        return m_length;
    }

    // Переопределенные методы
    myShape* mySquare::copyShape()
    {
        return new mySquare(*this);
    }

    // Метод рисования фигуры
    std::size_t mySquare::getPointCount() const
    {
        return m_vertexs;
    }

   sf::Vector2f mySquare::getPoint(std::size_t index) const
    {
        if (index == 0)
            return sf::Vector2f(0.f, 0.f);
        else if (index == 1)
            return sf::Vector2f(m_length, 0.f);
        else if (index == 2)
            return sf::Vector2f(m_length, m_length);
        else if (index == 3)
            return sf::Vector2f(0.f, m_length);

        return sf::Vector2f(0.f, 0.f);
    }


//myLine
////////////////////////////////////////////////////////////////

    // Конструкторы
    myLine::myLine()
    {
        setOrigin(m_length/2, m_thickness/2);
        setDefaultPosition();
        setType(LINE);
        update();
    }

    myLine::myLine(float length, float thickness = 2) :
        m_length(length), m_thickness(thickness)
    {
        setOrigin(m_length/2, m_thickness/2);
        setDefaultPosition();
        setType(LINE);
        update();
    }

    // Геттеры-сеттеры
    void myLine::setLenght(float length)
    {
        m_length = length;
        update();
    }

    void myLine::setThickness(float thickness)
    {
        m_thickness = thickness;
        update();
    }

    float myLine::getLenght() const
    {
        return m_length;
    }

    float myLine::getThickness() const
    {
        return m_thickness;
    }

    // Переопределенные методы
   myShape* myLine::copyShape()
    {
        return new myLine(*this);
    }

    // Метод рисования
    std::size_t myLine::getPointCount() const
    {
        return m_vertexs;
    }

    sf::Vector2f myLine::getPoint(std::size_t index) const
    {
        if (index == 0)
            return sf::Vector2f(0.f, 0.f);
        else if (index == 1)
            return sf::Vector2f(m_length, 0.f);
        else if (index == 2)
            return sf::Vector2f(m_length, m_thickness);
        else if (index == 3)
            return sf::Vector2f(0.f, m_thickness);

        return sf::Vector2f(0.f, 0.f);
    }


//myRectangle
////////////////////////////////////////////////////////////////

    // Конструкторы
    myRectangle::myRectangle()
    {
        setOrigin(m_length/2, m_thickness/2);
        setDefaultPosition();
        setType(RECTANGLE);
        update();
    }

    myRectangle::myRectangle(float length, float thickness) :
        m_length(length), m_thickness(thickness)
    {
        setOrigin(m_length/2, m_thickness/2);
        setDefaultPosition();
        setType(RECTANGLE);
        update();
    }

    // Переопределенные методы
   myShape* myRectangle::copyShape()
    {
        return new myRectangle(*this);
    }

    // Геттеры-сеттеры
   void myRectangle::setLenght(float length)
    {
        m_length = length;
        update();
    }

    void myRectangle::setThickness(float thickness)
    {
        m_thickness = thickness;
        update();
    }

    float myRectangle::getLenght() const
    {
        return m_length;
    }

   float myRectangle::getThickness() const
    {
        return m_thickness;
    }

    // Метод рисования
    std::size_t myRectangle::getPointCount() const
    {
        return m_vertexs;
    }

    sf::Vector2f myRectangle::getPoint(std::size_t index) const
    {
        if (index == 0)
            return sf::Vector2f(0.f, 0.f);
        else if (index == 1)
            return sf::Vector2f(m_length, 0.f);
        else if (index == 2)
            return sf::Vector2f(m_length, m_thickness);
        else if (index == 3)
            return sf::Vector2f(0.f, m_thickness);

        return sf::Vector2f(0.f, 0.f);
    }


//myDot
////////////////////////////////////////////////////////////////

    // Конструкторы
    myDot::myDot()
    {
        setOrigin(m_length/2, m_length/2);
        setDefaultPosition();
        setType(DOT);
        update();
    }

    myDot::myDot(float length) :
        m_length(length)
    {
        setOrigin(m_length/2, m_length/2);
        setDefaultPosition();
        setType(DOT);
        update();
    }

    // Переопределенные методы
    myShape* myDot::copyShape()
    {
        return new myDot(*this);
    }

    // Геттеры-сеттеры
    void myDot::setLenght(float length)
    {
        m_length = length;
        update();
    }

    float myDot::getLenght() const
    {
        return m_length;
    }

    // Метод рисования фигуры
    std::size_t myDot::getPointCount() const
    {
        return m_vertexs;
    }

    sf::Vector2f myDot::getPoint(std::size_t index) const
    {
        if (index == 0)
            return sf::Vector2f(0.f, 0.f);
        else if (index == 1)
            return sf::Vector2f(m_length, 0.f);
        else if (index == 2)
            return sf::Vector2f(m_length, m_length);
        else if (index == 3)
            return sf::Vector2f(0.f, m_length);

        return sf::Vector2f(0.f, 0.f);
    }


//myStar
////////////////////////////////////////////////////////////////

    // Конструкторы
    myStar::myStar()
    {
        setOrigin(m_radius.x, m_radius.y);
        setDefaultPosition();
        setType(STAR);
        update();
    }

    myStar::myStar(int vertexs) :
        m_vertexs(vertexs)
    {
        setOrigin(m_radius.x, m_radius.y);
        setDefaultPosition();
        setType(STAR);
        update();
    }

   // Переопределенные методы
    myShape* myStar::copyShape()
    {
        return new myStar(*this);
    }

    // Геттеры-сеттеры
    void myStar::setVertexs(int vertexs)
    {
        m_vertexs = vertexs;
        update();
    }

    void myStar::setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        update();
    }

    void myStar::setInnerRadius(const sf::Vector2f& inner_radius)
    {
        m_inner_radius = inner_radius;
        update();
    }

    int myStar::getVertexs() const
    {
        return m_vertexs;
    }

    const sf::Vector2f myStar::getRadius() const
    {
        return m_radius;
    }

    const sf::Vector2f myStar::getInnerRadius() const
    {
        return m_inner_radius;
    }

    // Метод рисования фигуры
    std::size_t myStar::getPointCount() const
    {
        return m_vertexs*2+1;
    }

    sf::Vector2f myStar::getPoint(std::size_t index) const
    {
        static const float pi = 3.141592654f;
        static float a = 0;
        float x;
        float y;

        //+ pi/getPointCount()

        if (!(index%2)) //При выполнении условия четности следующие формулы
        {
            x = m_inner_radius.x/2*cos(a*pi/180 + pi/getPointCount());
            y = -(m_inner_radius.y/2*sin(a*pi/180 + pi/getPointCount()));
        }
        else //При невыполнении условия четности следующие формулы
        {
            x = m_radius.x*cos(a*pi/180 + pi/getPointCount());
            y = -(m_radius.y*sin(a*pi/180 + pi/getPointCount()));
        }
        a=a+180/m_vertexs;

        return sf::Vector2f(m_radius.x + x, m_radius.x + y);
    }


//myAggregate
////////////////////////////////////////////////////////////////

    myAggregate::myAggregate(myShape* part_one, myShape* part_two)
    {
        m_part_one = part_one->copyShape();
        m_part_two = part_two->copyShape();

        setOrigin((part_one->getPosition().x + part_two->getPosition().x)/2,
        (part_one->getPosition().y + part_two->getPosition().y)/2);

        setPosition((part_one->getPosition().x + part_two->getPosition().x)/2,
        (part_one->getPosition().y + part_two->getPosition().y)/2);

        setType(AGGREGATE);
        update();
    }

    myAggregate::~myAggregate()
    {
        delete m_part_one;
        delete m_part_two;
    }

    // Переопределённые методы
    myShape* myAggregate::copyShape()
    {
        myAggregate* temp = new myAggregate(*this);
        temp->m_part_one = m_part_one->copyShape();
        temp->m_part_two = m_part_two->copyShape();

        return temp;
    }

    void myAggregate::setFillColor(sf::Color color)   // будет один общий цвет для фигур
    {
        m_part_one->setFillColor(color);
        m_part_two->setFillColor(color);
    }

    const sf::Color& myAggregate::getFillColor() const
    {
        return m_part_one->getFillColor();
    }

    // Метод рисования (используется только draw)
    void myAggregate::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the entity's transform -- combine it with the one that was passed by the caller
        states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

        // draw the vertex array
        target.draw(*m_part_one, states);
        target.draw(*m_part_two, states);
    }

    std::size_t myAggregate::getPointCount() const { return 0; }
    sf::Vector2f myAggregate::getPoint(std::size_t index) const { return sf::Vector2f(0.f, 0.f); }
