#include<iostream>
#include<Windows.h>
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

		int start_x;
		int start_y;
		int line_width;

		Color color;//цвет фигуры

	public:
		void set_star_x(int start_x)
		{
			this->start_x = start_x<MIN_START_X ? MIN_START_X :
				start_x>MAX_START_X ? MAX_START_X :
				start_x;
		}
		void set_color(Color color)
		{
			this->color = color;
		}
		Color get_color()const
		{
			return color;
		}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		Shape(Color color) :color(color) {}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры:" << get_perimeter() << endl;
			draw();
		}

	};
	class Square :public Shape
	{
		double side;
	public:

		void set_side(double side)
		{
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
		}
		Square(double side, Color color) : Shape(color)
		{
			set_side(side);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона квадрата: " << get_side() << endl;
			Shape::info();
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
		Rectangle(double side_1, double side_2, Color color) :Shape(color)
		{
			set_side_1(side_1);
			set_side_2(side_2);

		}
		void draw()const override
		{
			//cout << "ПРЯМОУГОЛЬНИК" << endl;

			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			HBRUSH HBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hPen);
			SelectObject(hdc, HBrush);
			::Rectangle(hdc, 200, 200, 400, 400);
			DeleteObject(HBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);

		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона 1:" << get_side1() << endl;
			cout << "Сторона 2:" << get_side_2() << endl;
			Shape::info();
		}
	};
}


void main() {
	setlocale(LC_ALL, "");
	Geometry::Square square(5, Geometry::Color::Red);
	square.info();
	Geometry::Rectangle rectangle(20, 15, Geometry::Color::Red);
	rectangle.info();


}