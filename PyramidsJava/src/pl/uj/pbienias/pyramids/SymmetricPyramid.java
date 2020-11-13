package pl.uj.pbienias.pyramids;

public class SymmetricPyramid extends Pyramid {

	private float height;
	
	public SymmetricPyramid(float x, float y, float _baseLength, float _height) {
		super(x, y, _baseLength);
		height = _height;
	}

	@Override
	public void drawShapeOwn(Canvas canvas) {
		float topX = start.x + baseLength / 2.f;
		float topY = start.y + height;
		Line left = new Line(start.x, start.y, topX, topY);
		Line right = new Line(start.x + baseLength, start.y, topX, topY);
		left.drawShape(canvas);
		right.drawShape(canvas);
	}

	@Override
	public float getArea() {
		return 0.5f * height * baseLength;
	}

	public float getHeight() {
		return height;
	}

	public void setHeight(float height) {
		this.height = height;
	}

	@Override
	public void resizeOwn(float scale) {
		height *= scale;
	}
	
	

}
