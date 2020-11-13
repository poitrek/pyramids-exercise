package pl.uj.pbienias.pyramids;

public class StepPyramid extends Pyramid {

	private float height;
	private int stepNum;
	
	public StepPyramid(float x, float y, float _baseLength, float _height, int _stepNum) {
		super(x, y, _baseLength);
		height = _height;
		stepNum = _stepNum;
		// TODO Auto-generated constructor stub
	}

	@Override
	public void drawShapeOwn(Canvas canvas) {
		// TODO Auto-generated method stub
		float dx = baseLength / (2.f * stepNum);
		float dy = height / stepNum;
		float x05 = start.x + dx / 2.f;
		float xn05 = start.x + baseLength - dx / 2.f;
		for (int i = 0; i < stepNum; i++) {
			float y_i = start.y + dy * (i + 1);
			new Line (x05 + dx * i, y_i, x05 + dx * (i+1), y_i).drawShape(canvas);
			new Line (xn05 - dx * i, y_i, xn05 - dx * (i + 1), y_i).drawShape(canvas);
			float x_i = x05 + dx * i;
			float xn_i = xn05 - dx * i;
			new Line (x_i, y_i - dy, x_i, y_i).drawShape(canvas);
			new Line (xn_i, y_i - dy, xn_i, y_i).drawShape(canvas);
		}
	}

	public float getHeight() {
		return height;
	}

	public void setHeight(float height) {
		this.height = height;
	}

	@Override
	public float getArea() {
		float dx = baseLength / (2.f * stepNum);
		float dy = height / stepNum;
		return dx * dy * stepNum * stepNum;
	}

	@Override
	public void resizeOwn(float scale) {
		height *= scale;
	}

}
