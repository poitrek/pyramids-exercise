package pl.uj.pbienias.pyramids;

public class EquilateralPyramid extends Pyramid {

	private final static float sqrt3div2 = 0.866f;
	
	public EquilateralPyramid(float x, float y, float _sideLength) {
		super(x, y, _sideLength);
	}

	@Override
	public void drawShapeOwn(Canvas canvas) {
		float topX = start.x + baseLength / 2.f;
		float topY = start.y + EquilateralPyramid.sqrt3div2 * baseLength;
		Line left = new Line(start.x, start.y, topX, topY);
		Line right = new Line(start.x + baseLength, start.y, topX, topY);
		left.drawShape(canvas);
		right.drawShape(canvas);
	}

	@Override
	public float getArea() {
		return 0.5f * EquilateralPyramid.sqrt3div2 * baseLength * baseLength;
	}

	@Override
	public void resizeOwn(float scale) {
		return;
	}

}
