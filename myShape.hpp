#pragma once
#include "directives.hpp"

enum ShapeType
{
    DOT, // 0
    LINE,
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    CIRCLE,
    STAR,
    AGGREGATE,
    NUMBER_SHAPES, // 8
};

// Наследуем sf::Shape, тем самым получаем доступ
// и к sf::Drawable, и к sf::Transformable
class myShape : public sf::Shape
{
private:
    float m_x = 0.f;
    float m_y = 0.f;

    bool m_visible = true;
    bool m_dance = false;
    bool m_disco = false;

    std::string m_name = "";
    ShapeType m_type = DOT;
    int m_id = 0;

protected:
    myShape()
    {
        static int id = 0;
        m_id = ++id;
    }

public:
    virtual myShape* copyShape();

    void setDefaultPosition();

    void changeDefaultPosition(float x, float y);

    void changePresetColor();

    void justDance();

    void justDisco();

    void setName(const std::string &name);

    void setType(ShapeType type);

    void setVisible();

    void setDance();

    void setDisco();

    const std::string& getName() const;

    ShapeType getType() const;

    bool getVisible() const;

    bool getDance() const;

    bool getDisco() const;

    bool getID() const;

    ///////////////////////////////////////////////////////////////////////
    // Переопределяем методы sf::Shape
    // Метод рисование фигуры, обязательно для переопредления
    virtual std::size_t getPointCount() const = 0;
    virtual sf::Vector2f getPoint(std::size_t) const = 0;

    // Сделано для агрегатов
    virtual void setFillColor(sf::Color color);
    virtual const sf::Color& getFillColor() const;

    // Персональные методы, необязательно для переопределения.
    // Прямоугольник + квадрат + линия + точка
    virtual void setLenght(float) {}
    virtual float getLenght() const { return 0.f;}

    // Прямоугольник + линия
    virtual void setThickness(float) {}
    virtual float getThickness() const { return 0.f; }

    // Круг + звезда + треугольник
    virtual void setRadius(const sf::Vector2f&) {}
    virtual void setVertexs(int) {}
    virtual const sf::Vector2f getRadius() const { return sf::Vector2f(0.0f, 0.0f); }
    virtual int getVertexs() const { return 0; }

    // Звезда
    virtual void setInnerRadius(const sf::Vector2f&) {}
    virtual const sf::Vector2f getInnerRadius() const { return sf::Vector2f(0.0f, 0.0f); }

};

class myCircle : public myShape
{
private :
    sf::Vector2f m_radius = sf::Vector2f(40.f, 40.f);
    int m_vertexs = 100;

public :
    // Конструкторы
    explicit myCircle();

    explicit myCircle(const sf::Vector2f& radius, int vertexs);

    explicit myCircle(float radius, int vertexs);

    // Геттеры-сеттеры
    virtual void setRadius(const sf::Vector2f& radius) override;

    virtual void setVertexs(int vertexs) override;

    virtual const sf::Vector2f getRadius() const override;

    virtual int getVertexs() const override;

    // Переопределенные методы
    virtual myShape* copyShape() override;

    // Метод рисования фигуры
    virtual std::size_t getPointCount() const override;

    virtual sf::Vector2f getPoint(std::size_t index) const override;
};

class myTriangle : public myShape
{
private :
    sf::Vector2f m_radius = sf::Vector2f(40.f, 40.f);
    const int m_vertexs = 3;

public :
    // Конструкторы
    explicit myTriangle();

    explicit myTriangle(const sf::Vector2f& radius);

    explicit myTriangle(float radius);

    // Геттеры-сеттеры
    virtual void setRadius(const sf::Vector2f& radius) override;

    virtual const sf::Vector2f getRadius() const override;

    // Переопределенные методы
    virtual myShape* copyShape() override;

    // Метод рисования фигуры
    virtual std::size_t getPointCount() const override;

    virtual sf::Vector2f getPoint(std::size_t index) const override;
};

class mySquare : public myShape
{
private :
    float m_length = 125.f;
    const int m_vertexs = 4;


public :
    // Конструкторы
    explicit mySquare();
    explicit mySquare(float length);

    // Геттеры-сеттеры
    virtual void setLenght(float length) override;

    virtual float getLenght() const override;

    // Переопределенные методы
    virtual myShape* copyShape() override;

    // Метод рисования фигуры
    virtual std::size_t getPointCount() const override;

    virtual sf::Vector2f getPoint(std::size_t index) const override;
};

class myLine : public myShape
{
private :
    float m_length = 250.f;
    float m_thickness = 1.f;

    const int m_vertexs = 4;

public :
    // Конструкторы
    explicit myLine();

    explicit myLine(float length, float thickness);

    // Геттеры-сеттеры
    virtual void setLenght(float length) override;

    virtual void setThickness(float thickness) override;

    virtual float getLenght() const override;

    virtual float getThickness() const override;

    // Переопределенные методы
    virtual myShape* copyShape() override;

    // Метод рисования
    virtual std::size_t getPointCount() const override;

    virtual sf::Vector2f getPoint(std::size_t index) const override;
};

class myRectangle : public myShape
{
private :
    float m_length = 250.f;
    float m_thickness = 125.f;

    const int m_vertexs = 4;

public :
    // Конструкторы
    explicit myRectangle();

    explicit myRectangle(float length, float thickness);

    // Переопределенные методы
    virtual myShape* copyShape() override;

    // Геттеры-сеттеры
    virtual void setLenght(float length) override;

    virtual void setThickness(float thickness) override;

    virtual float getLenght() const override;

    virtual float getThickness() const override;

    // Метод рисования
    virtual std::size_t getPointCount() const override;

    virtual sf::Vector2f getPoint(std::size_t index) const override;
};

class myDot : public myShape
{
private :
    float m_length = 2.f;
    const int m_vertexs = 4;

public :
    // Конструкторы
    explicit myDot();

    explicit myDot(float length);

    // Переопределенные методы
    virtual myShape* copyShape() override;

    // Геттеры-сеттеры
    virtual void setLenght(float length) override;

    virtual float getLenght() const override;

    // Метод рисования фигуры
    virtual std::size_t getPointCount() const override;

    virtual sf::Vector2f getPoint(std::size_t index) const override;
};

class myStar : public myShape
{
private :
    sf::Vector2f m_radius = sf::Vector2f(85.f, 85.f);
    sf::Vector2f m_inner_radius = sf::Vector2f(55.f, 55.f);
    int m_vertexs = 5;

public :
    // Конструкторы
    explicit myStar();

    explicit myStar(int vertexs);

   // Переопределенные методы
    virtual myShape* copyShape() override;

    // Геттеры-сеттеры
    virtual void setVertexs(int vertexs) override;

    virtual void setRadius(const sf::Vector2f& radius) override;

    virtual void setInnerRadius(const sf::Vector2f& inner_radius) override;

    virtual int getVertexs() const override;

    virtual const sf::Vector2f getRadius() const override;

    virtual const sf::Vector2f getInnerRadius() const override;

    // Метод рисования фигуры
    virtual std::size_t getPointCount() const override;

    virtual sf::Vector2f getPoint(std::size_t index) const override;
};

class myAggregate : public myShape
{
    myShape* m_part_one = nullptr;
    myShape* m_part_two = nullptr;

public:
    explicit myAggregate(myShape* part_one, myShape* part_two);

    virtual ~myAggregate();
    // Переопределённые методы
    virtual myShape* copyShape() override;

    virtual void setFillColor(sf::Color color) override; // будет один общий цвет для фигур;

    virtual const sf::Color& getFillColor() const override;

    // Метод рисования (используется только draw)
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual std::size_t getPointCount() const;
    virtual sf::Vector2f getPoint(std::size_t index) const;

};
