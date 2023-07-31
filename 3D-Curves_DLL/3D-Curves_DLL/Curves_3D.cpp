#include <iostream>
#include <random>
#include "Curves_3D.h"
#include <corecrt_math_defines.h>                       //  Очень полезный хедер, можно конечно самому посчитать PI = acos(-1)
#include <list>
#include <deque>

TestDrive::TestDrive() {
}

TestDrive::~TestDrive() {
}

void TestDrive::Hello() {
	std::cout << "Hello TEST DRIVE" << std::endl;
}

void TestDrive::Goodbye() {
	std::cout << "Goodbye TEST DRIVE" << std::endl;
}

//*************** МЕТОДЫ КЛАССОВ ***************//

//********* Circle_3D *********//
Point_3D Circle_3D::Curve_Point(double t) const {
    return Point_3D
    {
        Radius * cos(t) + C.x,
        Radius * sin(t) + C.y,
        C.z
    };
};


Vector_3D Circle_3D::Curve_Vector(double t) const {
    return Vector_3D
    {
        -1 * Radius * sin(t),
        Radius * cos(t)
    };
};

//********* Ellipse_3D *********//

Point_3D Ellipse_3D::Curve_Point(double t) const {
    return Point_3D
    {
        Radius_x * cos(t) + C.x,
        Radius_y * sin(t) + C.y,
        C.z
    };
};

Vector_3D Ellipse_3D::Curve_Vector(double t) const {
    return Vector_3D
    {
        -1 * Radius_x * sin(t),
        Radius_y * cos(t)
    };
};


//********* Spiral_3D *********//

Point_3D Spiral_3D::Curve_Point(double t) const {
    return Point_3D
    {
        Radius * t * cos(t) + C.x,
        Radius * t * sin(t) + C.y,
        Step * t + C.z
    };
}


Vector_3D Spiral_3D::Curve_Vector(double t) const {
    return Vector_3D
    {
        Radius * (cos(t) - t * sin(t)),
        Radius * (sin(t) + t * cos(t)),
        Step
    };
}

// Меняем диапазон.
void Curve_Generator::Set_Diapason(double min, double max)
{
    if ((abs(max) + abs(min)) < 2 * E)
        return;
    Random_Real_Num_Gen = decltype(Random_Real_Num_Gen){ min, max };
};


//  Генеруем объект класса Circle_3D (возвращает умный указатель на базовый класс).
Smart_Ptr_Curve Curve_Generator::Circle()
{
    double radius{};
    while (radius < E)
        radius = abs(Random_Real_Num_Gen(Initial_Val_For_Other_Gens));

    return make_shared<Circle_3D>(Point_3D{ Random_Real_Num_Gen(Initial_Val_For_Other_Gens),
                                            Random_Real_Num_Gen(Initial_Val_For_Other_Gens) },
        radius);
};


//  Генеруем объект класса Ellipse_3D (возвращает умный указатель на базовый класс).
Smart_Ptr_Curve Curve_Generator::Ellipse()
{
    double radius_x{};
    while (radius_x < E)
        radius_x = abs(Random_Real_Num_Gen(Initial_Val_For_Other_Gens));

    double radius_y{};
    while (radius_y < E)
        radius_y = abs(Random_Real_Num_Gen(Initial_Val_For_Other_Gens));

    return make_shared<Ellipse_3D>(Point_3D{ Random_Real_Num_Gen(Initial_Val_For_Other_Gens),
                                            Random_Real_Num_Gen(Initial_Val_For_Other_Gens) },
        radius_x, radius_y);
};


//  Генеруем объект класса Spiral_3D (возвращает умный указатель на базовый класс).
Smart_Ptr_Curve Curve_Generator::Spiral()
{
    double radius{};
    while (radius < E)
        radius = abs(Random_Real_Num_Gen(Initial_Val_For_Other_Gens));

    double step{};
    while (abs(step) < E)
        step = Random_Real_Num_Gen(Initial_Val_For_Other_Gens);

    return make_shared<Spiral_3D>(Point_3D{ Random_Real_Num_Gen(Initial_Val_For_Other_Gens),
                                            Random_Real_Num_Gen(Initial_Val_For_Other_Gens),
                                            Random_Real_Num_Gen(Initial_Val_For_Other_Gens) },
        radius, step);
};


//  Генератор случайных типов кривых.
Smart_Ptr_Curve Curve_Generator::Random_Curve()
{
    switch (Random_Obj_Type_Gen(Initial_Val_For_Other_Gens))
    {
    case Type_Circle:
        return Circle();
    case Type_Ellipse:
        return Ellipse();
    case Type_Spiral:
        return Spiral();
    default:
        return Circle();
    }
};

