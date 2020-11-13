package pl.uj.pbienias.pyramids;

public abstract class Pyramid extends Object2D {
	
	protected Point start;
	protected float baseLength;
	
	public Pyramid(float x, float y, float _baseLength) {
		start = new Point(x, y);
		baseLength = _baseLength;
	}
	
	@Override
	protected void drawShape(Canvas canvas) {
		// TODO Auto-generated method stub
		Line base = new Line(start.x, start.y, start.x + baseLength, start.y);
		base.drawShape(canvas);
		drawShapeOwn(canvas);
	}
	
	public abstract void drawShapeOwn(Canvas canvas);

	@Override
	public Point getPosition() {
		// TODO Auto-generated method stub
		return start;
	}

	@Override
	public void setPosition(Point p) {
		// TODO Auto-generated method stub
		start = p;
	}

	public float getBaseLength() {
		return baseLength;
	}

	public void setBaseLength(float baseLength) {
		this.baseLength = baseLength;
	}
	
	@Override
	public void resize(float scale) {
		baseLength *= scale;
		resizeOwn(scale);
	}
	
	public abstract void resizeOwn(float scale);

}
