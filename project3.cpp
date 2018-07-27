
//
// This is example code from Chapter 16.5 "An example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <iostream>
#include <sstream>
#include "Graph.h"         // get access to our graphics library facilities
#include "GUI.h"
#include "Window.h"

using namespace Graph_lib;
using namespace std;

//------------------------------------------------------------------------------

struct Lines_window : Window {
	Lines_window(Point xy, int w, int h, const string& title);

private:
	// Data:
	Closed_polyline p1, p2, p3, p4, p5, P;

	Closed_polyline p22, p33, p44;

	int i = 0;
	// Widgets:
	Button next_button;

	void next();



	static void cb_next(Address, Address);

};

//------------------------------------------------------------------------------


Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window(xy, w, h, title),
	next_button(Point(x_max() - 150, 0), 70, 20, "Next point", cb_next)

{
	p1.add(Point(0, 0));
	p1.add(Point(0, 30));
	p1.add(Point(30, 30));
	p1.add(Point(30, 20));
	p1.add(Point(10, 20));
	p1.add(Point(10, 0));


	p2.add(Point(0, 60));
	p2.add(Point(0, 70));
	p2.add(Point(10, 70));
	p2.add(Point(10, 100));
	p2.add(Point(20, 100));
	p2.add(Point(20, 60));

	p22.add(Point(0, 160));
	p22.add(Point(20, 160));
	p22.add(Point(20, 120));
	p22.add(Point(10, 120));
	p22.add(Point(10, 150));
	p22.add(Point(0, 150));

	p4.add(Point(70, 0));
	p4.add(Point(70, 20));
	p4.add(Point(80, 20));
	p4.add(Point(80, 40));
	p4.add(Point(90, 40));
	p4.add(Point(90, 10));
	p4.add(Point(80, 10));
	p4.add(Point(80, 0));

	p44.add(Point(110, 0));
	p44.add(Point(110, 30));
	p44.add(Point(100, 30));
	p44.add(Point(100, 40));
	p44.add(Point(90, 40));
	p44.add(Point(90, 20));
	p44.add(Point(100, 20));
	p44.add(Point(100, 0));


	p3.add(Point(40, 60));
	p3.add(Point(40, 70));
	p3.add(Point(50, 70));
	p3.add(Point(50, 110));
	p3.add(Point(60, 110));
	p3.add(Point(60, 60));




	p33.add(Point(40, 100));
	p33.add(Point(40, 110));
	p33.add(Point(60, 110));
	p33.add(Point(60, 60));
	p33.add(Point(50, 60));
	p33.add(Point(50, 100));


	p5.add(Point(0, 150));
	p5.add(Point(0, 170));
	p5.add(Point(20, 170));
	p5.add(Point(20, 150));



	P.add(Point(100, 50));

	P.add(Point(150, 50));
	P.add(Point(150, 100));
	P.add(Point(100, 100));

	p1.set_color(Color::black);
	p2.set_color(Color::black);
	p3.set_color(Color::black);
	p4.set_color(Color::black);
	p5.set_color(Color::black);

	p1.set_fill_color(Color::red);
	p2.set_fill_color(Color::green);
	p3.set_fill_color(Color::yellow);
	p4.set_fill_color(Color::blue);
	p5.set_fill_color(Color::cyan);


	P.set_color(Color::black);


	attach(next_button);

	attach(p1);
	attach(p2);
	attach(p3);
	attach(p4);
	attach(p5);
	attach(P);
}

//------------------------------------------------------------------------------


void Lines_window::cb_next(Address, Address pw)     // "the usual"
{
	reference_to<Lines_window>(pw).next();
}

//------------------------------------------------------------------------------

void Lines_window::next()
{
	int x1, x2, x3, x4, x5;
	int y1, y2, y3, y4, y5;

	this->i++;

	switch (this->i)
	{
	case 1:
		x1 = 100;
		y1 = 70;
		x2 = 120;
		y2 = -70;

		x3 = 90;
		y3 = -10;


		x4 = 20;
		y4 = 50;

		x5 = 100;
		y5 = -100;

		p1.move(x1, y1);
		p5.move(x5, y5);


		detach(p2);
		p22.set_fill_color(Color::green);
		p22.set_color(Color::black);
		attach(p22);
		p22.move(x2, y2);


		detach(p4);
		p44.set_fill_color(Color::blue);
		p44.set_color(Color::black);
		attach(p44);
		p44.move(x4, y4);

		detach(p3);
		p33.set_fill_color(Color::yellow);
		p33.set_color(Color::black);
		attach(p33);
		p33.move(x3, y3);


		redraw();
		break;
	case 2: break;
	default: {}
	}
}

//------------------------------------------------------------------------------


int main()
try {
	Lines_window win(Point(100, 100), 600, 400, "lines");
	return gui_main();
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Some exception\n";
	return 2;
}
