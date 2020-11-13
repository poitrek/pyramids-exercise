#include "main.hpp"
#include <iostream>
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>


void Object2D::move(const Line& line)
{
	set_position(get_position() + line.get_stop() - line.get_start());
}


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

Point Point::operator*(const float f)
{
	return Point(f * x, f * y);
}

void Point::draw_shape(Canvas& canvas)
{
	canvas.get_drawer().plot_pixel(
		int(round(x * canvas.get_px_ratio_w())), 
		int(round(y * canvas.get_px_ratio_h())));
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
		float x1 = fmin(this->start.x, this->stop.x);
		float x2 = fmax(this->start.x, this->stop.x);
		float x3 = fmin(line.start.x, line.stop.x);
		float x4 = fmax(line.start.x, line.stop.x);
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
		lines.push_back(Line(this->start, line.start));
		lines.push_back(Line(this->start, line.stop));
		lines.push_back(Line(this->stop, line.start));
		lines.push_back(Line(this->stop, line.stop));
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

 DONE:
 - Line::intersection method - no intersection results in nullptr
 - define Image class
 - define Canvas class
- use a Graphical2DObject class to represent any object that can be drawn
	which will be inherited by Pyramid, Line and Point
 - complete StepPyramid drawing
 * Run the first version of program with drawing chosen pyramids types on the canvas and
   saving to a file.
 - resolve pyramids color problem
 - implement get_area() for pyramids classes
 - try implementing image::resize(float)

*/


int main() {
	Canvas canvas(200, 200, 10, 10);
	int base_1 = 10, base_2 = 6;
	StepPyramid p1(0, 0, base_2, 5, 10);
	SymmetricPyramid p2(base_2, 0, base_1 - base_2, 5);
	EquilateralPyramid p3(0, 0, base_1);
	p1.set_color(255, 191, 64);
	p2.set_color(255, 223, 64);
	p3.set_color(255, 255, 64);
	
	Image img;
	img.add(p3).add(p2).add(p1);
	img.resize(1.f);
	img.draw(canvas);
	canvas.save("pyramids.png");

	Canvas c1(500, 500, 10, 10);
	Canvas c2(500, 500, 10, 10);
	Canvas c3(500, 500, 10, 10);
	img.draw(c1);
	img.resize(1.5f);
	img.draw(c2);
	img.resize(0.5f);
	p2.move(Line(0.f, 0.f, 2.f, 1.f));
	img.draw(c3);
	c1.save("pyr1.png");
	c2.save("pyr2.png");
	c3.save("pyr3.png");

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
	//image.save_image("output2.bmp");
	
	//testing::InitGoogleTest();
	//RUN_ALL_TESTS();
	return 0;
}

void SymmetricPyramid::draw_shape_own(Canvas& canvas)
{
	float top_x = start.x + base_length / 2.f;
	float top_y = start.y + height;
	Line left(start.x, start.y, top_x, top_y);
	Line right(start.x + base_length, start.y, top_x, top_y);
	left.draw_shape(canvas);
	right.draw_shape(canvas);
}

void EquilateralPyramid::draw_shape_own(Canvas& canvas)
{
	float top_x = start.x + base_length / 2.f;
	float top_y = start.y + sqrt_3div2 * base_length;
	Line left(start.x, start.y, top_x, top_y);
	Line right(start.x + base_length, start.y, top_x, top_y);
	left.draw_shape(canvas);
	right.draw_shape(canvas);
}

void StepPyramid::draw_shape_own(Canvas& canvas)
{
	float dx = base_length / (2.f * step_num);
	float dy = height / (float)step_num;
	float x05 = start.x + dx / 2.f;
	float xn05 = start.x + base_length - dx / 2.f;
	for (int i = 0; i < step_num; i++) {
		float y_i = start.y + dy * (i + 1);
		Line (x05 + dx * i, y_i, x05 + dx * (i+1), y_i).draw_shape(canvas);
		Line (xn05 - dx * i, y_i, xn05 - dx * (i + 1), y_i).draw_shape(canvas);
		float x_i = x05 + dx * i;
		float xn_i = xn05 - dx * i;
		Line (x_i, y_i - dy, x_i, y_i).draw_shape(canvas);
		Line (xn_i, y_i - dy, xn_i, y_i).draw_shape(canvas);
	}
}
