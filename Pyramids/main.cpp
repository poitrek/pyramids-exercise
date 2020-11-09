#include "main.hpp"
#include <iostream>
//#include <CImg.h>
//#include <cmath>
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>


Point::Point(float _x = 0.f, float _y = 0.f)
	:x(_x), y(_y) {}

bool Point::operator==(const Point& p) {
	return x == p.x && y == p.y;
}

Point Point::operator+(const Point& p)
{
	return Point(x + p.x, y + p.y);
}

Point Point::operator-(const Point& p)
{
	return Point(x - p.x, y - p.y);
}

void Point::draw_shape(Canvas& canvas)
{
	/*canvas.get_drawer().circle(
		int(round(x * canvas.get_px_ratio_w())),
		int(round(y * canvas.get_px_ratio_h())),
		2);*/
	canvas.get_drawer().plot_pixel(
		int(round(x * canvas.get_px_ratio_w())), 
		int(round(y * canvas.get_px_ratio_h())));
}

void Point::move(const Line& line) {
	this->x += line.dx();
	this->y += line.dy();
}

float matrix2d::det(float a, float b, float c, float d) {
	return a * d - b * c;
}

float matrix2d::det(Point P1, Point P2) {
	return P1.x * P2.y - P1.y * P2.x;
}


InfLine::InfLine(const Point& P1, const Point& P2) {
	A = P1.y - P2.y;
	B = P2.x - P1.x;
	C = matrix2d::det(P1, P2);
}

InfLine::posType InfLine::mutualPosition(const InfLine& ifL) {
	// If the lines are not parallel
	if (matrix2d::det(this->A, ifL.A, this->B, ifL.B) != 0)
		return InfLine::posType::intersect;
	else {
		// take the non-zero coefficient
		float coeff1 = (this->A == 0) ? this->B : this->A;
		float coeff2 = (ifL.A == 0) ? ifL.B : ifL.A;
		if (this->C / coeff1 == ifL.C / coeff2)
			return InfLine::posType::overlap;
		else
			return InfLine::posType::disjoint;
	}
		
}

Point InfLine::intersection(const InfLine &ifL) {
	Point p;
	p.x = matrix2d::det(this->B, ifL.B, this->C, ifL.C) / matrix2d::det(this->A, ifL.A, this->B, ifL.B);
	p.y = matrix2d::det(this->A, ifL.A, this->C, ifL.C) / matrix2d::det(this->B, ifL.B, this->A, ifL.A);
	return p;
}


bool Line::operator==(const Line& l)
{
	return (this->get_start() == l.get_start() && this->get_stop() == l.get_stop())
		|| (this->get_start() == l.get_stop() && this->get_stop() == l.get_start());
}

bool Line::is_end(Point p)
{
	return p == this->get_start() || p == this->get_stop();
}

Point Line::get_middle() {
	return Point((start.x + stop.x) / 2.f, (start.y + stop.y / 2.f));
}

float Line::len() {
	float dx = stop.x - start.x;
	float dy = stop.y - start.y;
	return sqrt(dx * dx + dy * dy);
}

Line Line::intersection(Line line) {
	/* Algorithm:
	1) Check if the (infinite) lines defined by the ends of the segments
	have an intersection, if so, calculate it
	2) If there is an intersection S of the lines, check if S belongs to
	both segments*/
	InfLine il1(*this), il2(line);
	switch (il1.mutualPosition(il2))
	{
	case InfLine::posType::intersect: {
		Point s = il1.intersection(il2);
		float x1 = fmin(this->get_start().x, this->get_stop().x);
		float x2 = fmax(this->get_start().x, this->get_stop().x);
		float x3 = fmin(line.get_start().x, line.get_stop().x);
		float x4 = fmax(line.get_start().x, line.get_stop().x);
		if (s.x >= x1 && s.x <= x2 && s.x >= x3 && s.x <= x4)
			return Line(s, s);
		else
			throw NoIntersectionException();
		break;
	}
	case InfLine::posType::overlap: {
		std::vector<Line> lines;
		lines.push_back(*this);
		lines.push_back(line);
		lines.push_back(Line(this->get_start(), line.get_start()));
		lines.push_back(Line(this->get_start(), line.get_stop()));
		lines.push_back(Line(this->get_stop(), line.get_start()));
		lines.push_back(Line(this->get_stop(), line.get_stop()));
		// Get the longest line segment
		std::vector<Line>::iterator maxLine = std::max_element(lines.begin(), lines.end(),
			[](Line l1, Line l2) {return l1.len() < l2.len(); });
		// If the longest line segment is longer than the sum of the input segments
		// - they are separate
		if (maxLine->len() > this->len() + line.len()) {
			throw NoIntersectionException();
		}
		else {
			std::vector<Point> lineEnds;
			lineEnds = { this->get_start(), this->get_stop(),
						line.get_start(), line.get_stop() };
			lineEnds.erase(std::find(lineEnds.begin(), lineEnds.end(), maxLine->get_start()));
			lineEnds.erase(std::find(lineEnds.begin(), lineEnds.end(), maxLine->get_stop()));
			// Return the segment from the remaining points that do NOT belong to the
			// longest segment
			return Line(lineEnds[0], lineEnds[1]);
		}
		break;
	}
	case InfLine::posType::disjoint: {
		throw NoIntersectionException();
		break;
	}
	default: {
		throw NoIntersectionException();
		break;
	}
	}
	/*try
	{
		throw NoIntersectionException();
	}
	catch (const NoIntersectionException& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}*/
}

void Line::move(const Line& line)
{
	start.move(line);
	stop.move(line);
}

void Line::draw_shape(Canvas& canvas)
{
	// draw line segment with respect to canvas pixels/size ratio
	canvas.get_drawer().line_segment(
		int(round(start.x * canvas.get_px_ratio_w())),
		int(round(start.y * canvas.get_px_ratio_h())),
		int(round(stop.x * canvas.get_px_ratio_w())),
		int(round(stop.y * canvas.get_px_ratio_h()))
		);
}


/*
TODO:
 * Run the first version of program with drawing chosen pyramids types on the canvas and
   saving to a file.
 - resolve pyramids color problem
 - complete StepPyramid drawing
 - implement get_area() for pyramids classes
 - try implementing image::resize(float)

 DONE:
 - Line::intersection method - no intersection results in nullptr
 - define Image class
 - define Canvas class
- use a Graphical2DObject class to represent any object that can be drawn
	which will be inherited by Pyramid, Line and Point
 
*/






// Test functions - only for implementation of desired shapes

void draw_circled_line(image_drawer &draw, int x0, int y0, int x1, int y1, int p) {
	float x(x0), y(y0);
	float dx = (x1 - x0) / (float)p;
	float dy = (y1 - y0) / (float)p;
	for (int i = 0; i < p; i++) {
		x += dx, y += dy;
		draw.circle(round(x), round(y), 4);
		//img.set_pixel(unsigned int(round(x)), unsigned int(round(y)), jet_colormap[50]);
	}
 }

void symmetric_pyramid(image_drawer& draw, int x0, int y0, int base, int height) {
	int x1 = x0 + base;
	draw.horiztonal_line_segment(x0, x1, y0);
	int x_top = x0 + base / 2;
	int y_top = y0 + height;
	draw.line_segment(x0, y0, x_top, y_top);
	draw.line_segment(x1, y0, x_top, y_top);	
}

void equilateral_pyramid(image_drawer& draw, int x0, int y0, int side) {
	int x1 = x0 + side;
	draw.horiztonal_line_segment(x0, x1, y0);
	int x_top = x0 + side / 2;
	int y_top = round(y0 + 0.866 * side);
	draw.line_segment(x0, y0, x_top, y_top);
	draw.line_segment(x1, y0, x_top, y_top);
}

void step_pyramid(image_drawer& draw, int x0, int y0, int base, int height, int n_steps) {
	float dx = base / (2.f * n_steps);
	float dy = height / (float)n_steps;
	draw.horiztonal_line_segment(x0, x0 + base, y0);
	float x05 = x0 + dx / 2.f;
	float xn05 = x0 + base - dx / 2.f;
	for (int i = 0; i < n_steps; i++) {
		draw.vertical_line_segment(round(y0 + dy * i), round(y0 + dy * (i + 1)), round(x05 + dx * i));
		draw.vertical_line_segment(round(y0 + dy * i), round(y0 + dy * (i + 1)), round(xn05 - dx * i));
		draw.horiztonal_line_segment(round(x05 + dx * i), round(x05 + dx * (i + 1)), round(y0 + dy * (i + 1)));
		draw.horiztonal_line_segment(round(xn05 - dx * i), round(xn05 - dx * (i + 1)), round(y0 + dy * (i + 1)));
	}
}


int main() {

	Canvas c1(200, 200, 10, 10);
	int base_1 = 10, base_2 = 6;
	//StepPyramid p1(0, 0, base_2, 5, 10);
	SymmetricPyramid p2(base_2, 0, base_1 - base_2, 5);
	EquilateralPyramid p3(0, 0, base_1);
	//p1.set_color(255, 191, 64);
	p2.set_color(255, 223, 64);
	p3.set_color(255, 255, 64);
	
	Image img1;
	img1.add(p3).add(p2);
	//img.resize(1.f);
	img1.draw(c1);
	c1.save("pyramids.bmp");

	/*Canvas c(300, 300, 10, 10);
	Line l1(1, 1, 8, 1);
	l1.set_color(255, 191, 64);
	Line l2(2, 2, 9, 7);
	l2.set_color(0, 255, 0);
	Point p1(2, 8);
	p1.set_color(0, 0, 255);
	Image img;
	img.add(l1).add(l2).add(p1);
	img.draw(c);
	c.save("out1.bmp");*/
	//bitmap_image image(600, 400);
	//image.set_all_channels(240, 240, 240);
	//image_drawer draw(image);
	//draw.pen_width(3);
	//draw.pen_color(240, 240, 20);
	////draw.circle(100, 100, 70);
	////symmetric_pyramid(draw, 100, 100, 300, 300);
	//draw.pen_color(240, 120, 20);
	////equilateral_pyramid(draw, 150, 100, 250);
	//step_pyramid(draw, 60, 60, 200, 250, 10);
	//step_pyramid(draw, 300, 60, 250, 250, 5);
	////draw.pen_width(3);
	////draw.pen_color(100, 255, 100);
	////draw.rectangle(50, 50, 150, 120);
	////draw_circled_line(draw, 100, 550, 500, 200, 20);
	//image.vertical_flip();
	//image.save_image("output2.bmp");


	testing::InitGoogleTest();
	RUN_ALL_TESTS();
	return 0;
}

void Pyramid::draw_shape(Canvas& canvas)
{
	Line base(x, y, x + base_width, y);
	base.draw(canvas);
}

void SymmetricPyramid::draw_shape(Canvas& canvas)
{
	Pyramid::draw_shape(canvas);
	float top_x = x + base_width / 2.f;
	float top_y = y + height;
	Line left(x, y, top_x, top_y);
	Line right(x + base_width, y, top_x, top_y);
	left.draw_shape(canvas);
	right.draw_shape(canvas);
}

void EquilateralPyramid::draw_shape(Canvas& canvas)
{
	Pyramid::draw_shape(canvas);
	float top_x = x + base_width / 2.f;
	float top_y = y + sqrt_3div2 * base_width;
	Line left(x, y, top_x, top_y);
	Line right(x + base_width, y, top_x, top_y);
	left.draw_shape(canvas);
	right.draw_shape(canvas);
}

void StepPyramid::draw_shape(Canvas& canvas)
{
	Pyramid::draw_shape(canvas);

}
