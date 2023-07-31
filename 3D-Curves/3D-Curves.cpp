#include <iostream>
#include <random>
#include "ClassDeclarations.h"
#include <corecrt_math_defines.h>                       //  Очень полезный хедер, можно конечно самому посчитать PI = acos(-1)
#include <list>
#include <deque>


int main()
{
    system("cls&&color 2");
    const Byte Container_Size = 15;                     //  Размер первого контейнера(вектора/списка/очереди).
    double Sum_of_Radii = 0;                            //  Сумма радиусов только Circle_3D.

    vector<Smart_Ptr_Curve> Container_Curves;           //  Контейнер(вектор) указателей на объекты базового класса.
    //list<Smart_Ptr_Curve> Container_Curves;           //  Контейнер(список) указателей на объекты базового класса.
    //deque<Smart_Ptr_Curve> Container_Curves;          //  Контейнер(очередь) указателей на объекты базового класса.

 
    Curve_Generator Cur_Gen;                            //  Генерим кривые и заполняем контейнер.
    Cur_Gen.Set_Diapason(-7, 7);                      
    for (size_t i = 0; i < Container_Size; i++)
        Container_Curves.emplace_back(Cur_Gen.Random_Curve());   
 
    using Smart_Ptr_Circle = shared_ptr<Circle_3D>;     //  Умный указатель на Circle_3D из первого контейнера.

    vector<Smart_Ptr_Circle> Con_Circles;               //  2-й Контейнер - массив указателей на Circle_3D из первого контейнера.

    for (auto& Con_Ptr1 : Container_Curves)
    {
        const type_info& Type_Inf{ typeid(*Con_Ptr1) };
        string Class = Type_Inf.name();
        string Sub_Str = Class.substr(6, 20);

        cout << distance(&Container_Curves.front(), &Con_Ptr1) << ".) "
            << Sub_Str << ' ';

        if (Type_Inf.hash_code() == typeid(Circle_3D).hash_code())   
        {
            Con_Circles.emplace_back(dynamic_pointer_cast<Circle_3D>(Con_Ptr1));
            Sum_of_Radii += Con_Circles.back()->radius();
            cout << "                              V";
        }
        cout << "\n        Point(" << Con_Ptr1->Curve_Point(M_PI_4).x << ", " << Con_Ptr1->Curve_Point(M_PI_4).y << ", " << Con_Ptr1->Curve_Point(M_PI_4).z << ")"
            << "\n       Vector(" << Con_Ptr1->Curve_Vector(M_PI_4).x << ", " << Con_Ptr1->Curve_Vector(M_PI_4).y << ", " << Con_Ptr1->Curve_Vector(M_PI_4).z << ")";
        cout << endl;
    }

    cout << "\nFound circles with radii:\n";

    sort(Con_Circles.begin(), Con_Circles.end(), [](const auto& lh, const auto& rh)
    {
        return lh->radius() < rh->radius();
    });

    for (auto& Con_Ptr2 : Con_Circles)
        cout << "   " << distance(&Con_Circles.front(), &Con_Ptr2) << ". " << Con_Ptr2->radius() << endl;

    cout << "\nThe sum of the radii of all circles = " << Sum_of_Radii << endl; 
}


//*************** МЕТОДЫ КЛАССОВ ***************//

//********* Circle_3D *********//
Point_3D Circle_3D::Curve_Point(double t) const {
    return Point_3D
    {
        Radius* cos(t) + C.x,
        Radius* sin(t) + C.y,
        C.z
    };
};


Vector_3D Circle_3D::Curve_Vector(double t) const {
    return Vector_3D
    {
        -1 * Radius * sin(t),
        Radius* cos(t)
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
        Radius* t * cos(t) + C.x,
        Radius* t * sin(t) + C.y,
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

    return make_shared<Ellipse_3D>(Point_3D{Random_Real_Num_Gen(Initial_Val_For_Other_Gens),
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

