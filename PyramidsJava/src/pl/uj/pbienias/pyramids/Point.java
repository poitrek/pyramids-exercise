package pl.uj.pbienias.pyramids;

public class Point extends Object2D {
	
	public float x;
	public float y;
	
	public Point add(Point p) {
		return new Point(x + p.x, y + p.y);
	}
	
	public Point subtr(Point p) {
		return new Point(x - p.x, y - p.y);
	}
	
	public Point scale(float f) {
		return new Point(x * f, y * f);
	}
	
	public Point() {
		x = 0.f; y = 0.f;
	}
	
	public Point(float _x, float _y) {
		x = _x;
		y = _y;
	}
	
	@Override
	public boolean equals(Object obj) {
		// TODO Auto-generated method stub
		if (obj == this)
			return true;
		else {
			if (!(obj instanceof Point))
				return false;
			else {
				Point p = (Point)obj;
				return (this.x == p.x && this.y == p.y);
			}
		}
	}

	@Override
	protected void drawShape(Canvas canvas) {
		// TODO Auto-generated method stub
		canvas.drawPoint(x, y);
	}

	@Override
	public Point getPosition() {
		// TODO Auto-generated method stub
		return this;
	}

	@Override
	public void setPosition(Point p) {
		// TODO Auto-generated method stub
		x = p.x;
		y = p.y;
	}

	@Override
	public float getArea() {
		// TODO Auto-generated method stub
		return 0.f;
	}
	
	@Override
	public void resize(float scale) {
		return;
	}
	
	


}
