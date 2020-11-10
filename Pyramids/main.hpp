#pragma once
#include <exception>
#include <vector>
#include "bitmap_image.hpp"


struct Point;
class Line;


class Canvas {
	bitmap_image btp_image;
	image_drawer* drawer;
	const int px_w, px_h;
	const float size_w, size_h;
	// Pixel / size ratio
	float px_ratio_w, px_ratio_h;

public:
	Canvas(int _px_w, int _px_h, float _size_w, float _size_h)
		: px_w(_px_w), px_h(_px_h), size_w(_size_w), size_h(_size_h)
	{
		drawer = new image_drawer(btp_image);
		drawer->pen_width(2);
		drawer->pen_color(0, 0, 0);
		btp_image.setwidth_height(px_w, px_h);
		btp_image.set_all_channels(255, 255, 255);
		px_ratio_w = (float)px_w / size_w;
		px_ratio_h = (float)px_h / size_h;
	}

	image_drawer& get_drawer() {
		return *drawer;
	}

	float get_px_ratio_w() const {
		return px_ratio_w;
	}

	float get_px_ratio_h() const {
		return px_ratio_h;
	}

	~Canvas() {
		delete drawer;
	}
	void save(const std::string path) {
		btp_image.vertical_flip();
		btp_image.save_image(path);
	}
};



class Object2D {
	struct Color {
		int r, g, b;
	} color;
protected:
	virtual void draw_shape(Canvas& canvas) = 0;

public:
	virtual void draw(Canvas& canvas) {
		// set the drawer color (for each derived class)
		canvas.get_drawer().pen_color(color.r, color.g, color.b);
		// call the abstract function to draw shape (different for
		// each derived class)
		draw_shape(canvas);
	}
	virtual Point get_position() = 0;
	virtual void move(const Line& line) = 0;
	virtual float get_area() = 0;
	void set_color(int r, int g, int b) {
		color.r = r;
		color.g = g;
		color.b = b;
	}
};


struct Point : public Object2D{
//public:
	float x;
	float y;
	Point(float, float);
	bool operator ==(const Point& p);
	Point operator +(const Point& p);
	Point operator -(const Point& p);
	virtual Point get_position() { return *this; }
	virtual void move(const Line& line);
	virtual float get_area() { return 0.f; };
	/*float getX() const;
	float getY() const;
	void setX(float _x);
	void setY(float _y);*/
private:
	virtual void draw_shape(Canvas& canvas);
};

struct matrix2d {
	static float det(float a, float b, float c, float d);
	static float det(Point P1, Point P2);
};
	
// Class representing a line (segment)
class Line : public Object2D {
	// Vertices of the line
	Point start, stop;
public:
	Line(Point _start, Point _stop)
		: start(_start), stop(_stop) {}
	Line(float x1, float y1, float x2, float y2)
		: start(x1, y1), stop(x2, y2) {}
	void set_start(const Point& p) { start = p; }
	void set_stop(const Point& p) { stop = p; }
	Point get_start() const { return start; }
	Point get_stop() const { return stop; }
	float dx() const { return stop.x - start.x; }
	float dy() const { return stop.y - start.y; }
	bool operator ==(const Line& l);
	bool is_end(Point p);
	bool is_point() { return start == stop; }
	Point get_middle();
	float len();
	Line intersection(Line line);
	virtual void draw_shape(Canvas& canvas);
	virtual void move(const Line& line);
	virtual Point get_position() {
		return start.get_position();
	}
	virtual float get_area() { return 0.f; }
};

// Structure representing an infinite line
class InfLine {
	friend class Line;

	float A, B, C;
public:
	// Construct Infinite line from two points
	InfLine(const Point& P1, const Point& P2);
	// Construct infinite line from line segment
	InfLine(const Line& L) {
		A = L.get_start().y - L.get_stop().y;
		B = L.get_stop().x - L.get_start().x;
		C = matrix2d::det(L.get_start(), L.get_stop());
	}

	enum posType {
		overlap, intersect, disjoint
	};

	// Find the mutual position of two lines (overlapping, intersecting, or disjoint)
	InfLine::posType mutualPosition(const InfLine& ifL);

	// Returns the intersection point between two lines. If there is no intersection,
	// or the lines are disjoint, the behaviour is undefined.
	Point intersection(const InfLine& ifL);
};


struct NoIntersectionException : public std::exception {
	const char* what() const throw () {
		return "The line segments have no intersection.";
	}
};


class Pyramid : public Object2D {
protected:
	float x, y;
	float base_length;
	virtual void draw_shape(Canvas& canvas);

public:
	Pyramid(float _x, float _y, float _base_length)
		: x(_x), y(_y), base_length(_base_length) {}

	virtual Point get_position() {
		return Point(x, y);
	}
	
	virtual void move(const Line& line) {
		x += line.dx(), y += line.dy();
	}

	virtual void resize(float scale) {}
	virtual float get_area() = 0;

	void set_base_length(float width) {
		base_length = width;
	}

	float get_base_length() {
		return base_length;
	}

};


class SymmetricPyramid : public Pyramid {
	float height;
	virtual void draw_shape(Canvas& canvas);

public:
	SymmetricPyramid(float x, float y, float _base_length, float _height)
		:Pyramid(x, y, _base_length), height(_height) {}

	void set_height(float _height) {
		height = _height;
	}
	float get_height() {
		return height;
	}

	virtual float get_area() {
		return 0.5f * height * base_length;
	}

};

class EquilateralPyramid : public Pyramid {
	const float sqrt_3div2 = 0.866f;
	virtual void draw_shape(Canvas& canvas);

public:
	EquilateralPyramid(float x, float y, float side_length)
		:Pyramid(x, y, side_length) {}

	virtual float get_area() {
		return 0.5f * sqrt_3div2 * base_length * base_length;
	}
};

class StepPyramid : public Pyramid {
	float height;
	int step_num;
	virtual void draw_shape(Canvas& canvas);
public:
	StepPyramid(float x, float y, float _base_length, float _height, int _step_num)
		:Pyramid(x, y, _base_length), height(_height), step_num(_step_num) {}

	void set_height(float _height) {
		height = _height;
	}
	float get_height() {
		return height;
	}

	virtual float get_area() {
		float dx = base_length / (2.f * step_num);
		float dy = height / (float)step_num;
		return dx * dy * step_num * step_num;
		/// Inefficient AS F*
		/*float area = 0.f;
		for (int i = 0; i < step_num; i++) {
			area += dy * dx * (2 * i + 1);
		}
		return area;*/
	}

};

class Image {
	std::vector<Object2D*> objects;

public:
	Image& add(Object2D& obj) {
		objects.push_back(&obj);
		return *this;
	}

	void draw(Canvas& canvas) {
		for (Object2D* obj : objects) {
			obj->draw(canvas);
		}
	}

};
