#pragma once
using namespace std;                                        //  Проект маленький, потому не так страшен - "using namespace" как его малюют )))

typedef unsigned char Byte;

struct Point_3D { double x{}, y{}, z{}; };                  // 3D-Точка.
struct Vector_3D { double x{}, y{}, z{}; };                 // 3D-Вектор.

const double E = 1e-10;


//  Основной класс.
class Curve_3D
{
protected:
    Point_3D C;                                            
    Curve_3D() = default;
    Curve_3D(const Point_3D& center) : C{ center } {};

public:
    virtual ~Curve_3D() {}

    virtual Point_3D Curve_Point(double t) const = 0;       // 3D-Точка кривой по параметру t.
    virtual Vector_3D Curve_Vector(double t) const = 0;     // Первая производная (трехмерный вектор) по параметру t.
};

using Smart_Ptr_Curve = shared_ptr<Curve_3D>;               // Псевдоним типа (умный указатель) на базовый класс.


//  Окружность в плоскости XoY.
class Circle_3D : public Curve_3D 
{
    double Radius{};
   
public:
    Circle_3D() = default;
    Circle_3D(const Point_3D& center, double radius)
        : Curve_3D(center), Radius{ radius } {};

    virtual ~Circle_3D() {}

    double radius() const { return Radius; }                  

    virtual Point_3D Curve_Point(double t) const override;
    virtual Vector_3D Curve_Vector(double t) const override;
};


//  Эллипс в плоскости XoY.
class Ellipse_3D : public Curve_3D 
{
    double Radius_x = 0;
    double Radius_y = 0;

public:
    Ellipse_3D() = default;
    Ellipse_3D(const Point_3D& center, double radius_x, double radius_y)
        : Curve_3D(center), Radius_x{ radius_x }, Radius_y{ radius_y } {}

    virtual ~Ellipse_3D() {}

    virtual Point_3D Curve_Point(double t) const override;
    virtual Vector_3D Curve_Vector(double t) const override;
};


//  3D-спираль.
class Spiral_3D : public Curve_3D
{
    double Radius = 0;
    double Step = 0;

public:
    Spiral_3D() = default;
    Spiral_3D(const Point_3D& center, double radius, double step_z)
        : Curve_3D(center), Radius{ radius }, Step{ step_z } {}

    virtual ~Spiral_3D() {}

    virtual Point_3D Curve_Point(double t) const override;
    virtual Vector_3D Curve_Vector(double t) const override;
};


//  Генератор кривых (наследники Curve_3D).
class Curve_Generator
{
    enum Curve_Types { Type_Circle, Type_Ellipse, Type_Spiral };         

    random_device Initial_Val_For_Other_Gens;
    uniform_real_distribution<double> Random_Real_Num_Gen{ -1, 1 };
    uniform_int_distribution<> Random_Obj_Type_Gen{ Type_Circle, Type_Spiral };

public:

    void Set_Diapason(double min, double max);  // Меняем диапазон.
    Smart_Ptr_Curve Circle();                   // Генеруем и размещаем в динамической памяти объект класса Circle_3D (возвращает умный указатель на базовый класс).
    Smart_Ptr_Curve Ellipse();                  // Генеруем и размещаем в динамической памяти объект класса Ellipse_3D (возвращает умный указатель на базовый класс).
    Smart_Ptr_Curve Spiral();                   // Генеруем и размещаем в динамической памяти объект класса Spiral_3D (возвращает умный указатель на базовый класс).
    Smart_Ptr_Curve Random_Curve();             // Генератор случайных кривых.
};
