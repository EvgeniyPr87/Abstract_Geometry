#include<iostream>
#include<Windows.h>
#include<cmath>
#include<array>

using std::cout;
using std::cin;
using std::endl;

namespace Geometry
{
	enum Color
	{
		Red = 0x000000FF,
		Green = 0x0000FF00,
		Blue = 0x00FF0000,
		Yellow = 0x0000FFFF,
		Violet = 0x00FF00FF
	};

#define SHAPE_TAKE_PARAMETERS int start_x, int start_y, int line_widh, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_widh, color
#define delimetr "-------------------\n\n"
	struct Point
	{
		double x;
		double y;
	};
	class Shape
	{
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 100;
		static const int MAX_START_X = 800;
		static const int MAX_START_Y = 600;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 32;
		static const int MIN_SIZE = 32;
		static const int MAX_SIZE = 800; 
		static const double PI;

	protected:
		int start_x;
		int start_y;
		int line_width;
		

		Color color;//цвет фигуры

	public:
		void set_start_x(int start_x)
		{
			this->start_x =
				start_x<MIN_START_X ? MIN_START_X :
				start_x>MAX_START_X ? MAX_START_X :
				start_x;
		}
		void set_start_y(int start_y)
		{
			this->start_y =
				start_y<MIN_START_Y ? MIN_START_Y :
				start_y>MAX_START_Y ? MAX_START_Y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			this->line_width =
				line_width<MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
				line_width>MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;
		}

		void set_color(Color color)
		{
			this->color = color;
		}

		double get_start_x()const
		{
			return start_x;
		}
		double get_start_y()const
		{
			return start_y;
		}
		double get_line_width()const
		{
			return line_width;
		}
		Color get_color()const
		{
			return color;
		}
		double get_const_PI()const { return 3.14; }

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_widh);
		}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры:" << get_perimeter() << endl;
			cout << delimetr;
			draw();
		}

	};
	
	class Rectangle :public Shape
	{
		double side_1;
		double side_2;
	public:
		void set_side_1(double side_1)
		{
			this->side_1 = side_1;
		}
		void set_side_2(double side_2)
		{
			this->side_2 = side_2;
		}

		double get_side1()const
		{
			return side_1;
		}
		double get_side_2()const
		{
			return side_2;
		}
		double get_area()const override
		{
			return side_1 * side_2;
		}
		double get_perimeter()const override
		{
			return (side_1 + side_2) * 2;
		}
		void draw()const override
		{

			//1.Получаем окно консоли:
			HWND hwnd = GetConsoleWindow();

			//2.Получаем контексе устройства консольного окна:
			HDC hdc = GetDC(hwnd);

			//3.Создаем карандаш:
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			//PS_SOLID-сплошная линия
			//1-толщина линии = 1pixel;
			//RGB(255,0,0)-линия красного цвета

			//4.Создаем кисть, которая выполняет заливку фигуры:
			HBRUSH HBrush = CreateSolidBrush(color);

			//5.Выбираем чем и на чем будем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, HBrush);

			//6.Вызываем нужную функцию для рисования фигуры:
			::Rectangle(hdc, start_x, start_y, start_x + side_1, start_y + side_2);
			// ::  -Global Scope

			//7.Удаляем карандаш и кисть, поскольку они также занимают ресурсы:
			DeleteObject(HBrush);
			DeleteObject(hPen);

			//8.Контекст устройства тоже занимает место, которое нужно освободить:
			ReleaseDC(hwnd, hdc);
		}
		Rectangle(double side_1, double side_2, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side_1(side_1);
			set_side_2(side_2);

		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона 1:" << get_side1() << endl;
			cout << "Сторона 2:" << get_side_2() << endl;
			Shape::info();
		}
	};
	class Square :public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
	};
	class Triangle :public Shape
	{
		
		double side_1;
		double side_2;
		double side_3;

	public:
		void set_side_1(double side_1) { this->side_1 = side_1; }

		void set_side_2(double side_2) { this->side_2 = side_2; }

		void set_side_3(double side_3) { this->side_3 = side_3; }


		double get_side_1()const { return side_1; }

		double get_side_2()const { return side_2; }

		double get_side_3()const { return side_3; }

		double get_perimeter()const override { return side_1 + side_2 + side_3; }
		double get_area()const override
		{
			//формула Герона S=sqrt((p-a)*(p-b)*(p-c)), p-полупериметр

			double P = get_perimeter() / 2;
			return sqrt(((P - side_1) * (P - side_2) * (P - side_3)));
		}
		Triangle(double side_1, double side_2, double side_3, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			//проверка на возможность создания треугольника: 
			//треугольник не существует, если сумма любых его сторон меньше третьей стороны
			if (side_1 + side_2 <= side_3 || side_2 + side_3 <= side_1 || side_3 + side_1 <= side_2)
			{
				throw std::invalid_argument("Треугольник по заданным параметрам не существует");
			}
			set_side_1(side_1);
			set_side_2(side_2);
			set_side_3(side_3);
		}
		Point p1{get_start_x(),get_start_y()};
		Point p2{p1.x + get_side_1(),p1.y};
		Point p3 = {};

		Point Point_Coordinate(Point p1, Point p2, double side_1,double side_2, double side_3)
		{
			double distance_p = (pow(get_side_3(), 2) + pow(get_side_1(), 2) - pow(get_side_2(), 2)) / (2 * get_side_1());

			double height = sqrt(pow(get_side_3(), 2) - pow(distance_p, 2));

			Point  temp_p;
			temp_p.x =p1.x + distance_p * (p2.x - p1.x) / get_side_1();
			temp_p.y =p1.y + distance_p * (p2.y - p1.y) / get_side_1();
			
			return p3 =
			{
				p3.x = static_cast<LONG>(temp_p.x - height * (p2.y - p1.y) / get_side_1()),
				p3.y = static_cast<LONG>(temp_p.y + height * (p2.x - p1.x) / get_side_1())
			};
		}
		//LONG — это тип данных, который используется в Windows API.
		// Он представляет собой 32-битное знаковое целое число.
		//используется для хранения X и Y координат

		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			std::array< POINT, 4 > tPoints;
			tPoints[0] = { static_cast<LONG>(p1.x), static_cast<LONG>(p1.y) };
			tPoints[1] = { static_cast<LONG>(p2.x), static_cast<LONG>(p2.y) };
			tPoints[2] = { static_cast<LONG>(p3.x), static_cast<LONG>(p3.y) };
			tPoints[3] = { static_cast<LONG>(p1.x), static_cast<LONG>(p1.y) };

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Polygon(hdc,tPoints.data(),tPoints.size() );

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << endl;
			cout << typeid(*this).name() << endl;
			cout << "Сторона 1:" << get_side_1() << endl;
			cout << "Сторона 2:" << get_side_2() << endl;
			cout << "Сторона 3:" << get_side_3() << endl;
			Shape::info();
		}
	};
	class Circle :public Shape
	{
		double radius;
	public:
		void set_radius(double radius)
		{
			this->radius = radius;
		}
		double get_radius()const { return radius; }

		double get_area()const override
		{
			return pow(radius, 2) * get_const_PI();
		}
		double get_perimeter()const override
		{
			return 2 * radius * get_const_PI();
		}


		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			if (radius == 0) { throw std::invalid_argument(" НЕвозможно построить окружность !"); }
				this->radius = radius;
		}

		/*Ellipse(HDC hdc,int left,int top,int right,int bottom)
			HDC hdc,      Дескриптор контекста устройства
			int left      Координата X верхнего левого угла ограничивающего прямоугольника
			int top       Координата Y верхнего левого угла ограничивающего прямоугольника
			int right	  Координата X нижнего правого угла ограничивающего прямоугольника
			int bottom    Координата Y нижнего правого угла ограничивающего прямоугольника*/
		
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			
			int left = get_start_x() - radius;
			int top = get_start_y() - radius;
			int right = get_start_x() + radius;
			int bottom = get_start_y() + radius;
			
			::Ellipse(hdc,left, top, right, bottom);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус: " << get_radius() << endl;
			Shape::info();
		}
	};
}// exit from namespace Geometry

void main() {
	setlocale(LC_ALL, "");
	Geometry::Square square(50, 300, 50, 5, Geometry::Color::Green);
	square.info();
	Geometry::Rectangle rectangle(200, 150, 550, 100, 1, Geometry::Color::Blue);
	rectangle.info();
	Geometry::Rectangle rectangle_2(150, 200, 400, 120, 2, Geometry::Color::Violet);
	rectangle_2.info();
	Geometry::Triangle triangle(100, 100, 150, 200, 200, 2, Geometry::Color::Green);
	triangle.info();
	Geometry::Circle circle(100, 300, 400, 3, Geometry::Color::Violet);
	circle.info();





}