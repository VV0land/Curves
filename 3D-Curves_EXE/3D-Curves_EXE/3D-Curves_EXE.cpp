#include <iostream>
#include <random>
#include "Curves_3D.h"
#include <corecrt_math_defines.h>                       //  Очень полезный хедер, можно конечно самому посчитать PI = acos(-1)
#include <list>
#include <deque>



int main() {

    TestDrive TD;
	TD.Hello();
	TD.Goodbye();

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

