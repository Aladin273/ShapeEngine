#pragma once
#include "directives.hpp"

class ShapeManager
{
private:
    // Настройки программы
    std::string title = "ShapeEngine v0.1";
    sf::Color background_color = sf::Color(121, 160, 149);

    int fps_mode = 60;
    int weight = 1280;
    int height = 720;
    int antialiasing = 16;
    bool apply_changes = false;

    // Параметры фигур
    int current_shape = 0;
    int trace_period = 13;

    bool check_colission = false;
    bool global_tracing = false;

    // Управление фигурой фигур
    float x_right = 15.f;
    float x_left = -15.f;
    float y_up = -15.f;
    float y_down = 15.f;

    float rotation_step = 5.f;
    float rotation = 0.f;

    // Деформация фигуры
    float scale_plus = 1.1f;
    float scale_minus = 0.9f;

    // Место хранения фигур
    std::vector<myShape*> shapes;

    enum Parameters
    {
        LEFT,
        RIGHT,
        DUPLICATE,
        REPLACE,
        CURRENT,
        BY_NAME,
    };

public:
    ShapeManager();

    void createShape();

    void makeAggregate(Parameters parameter);

    void deleteShape(Parameters parameter);

    void editShape();

    void createConfig();

    void readConfig();

    void changeRGBAColor();

    void switchShape();

    void rotateShape(Parameters direction);

    void drawConsoleInterFace();

    void engineSettings();

    void start();
};
