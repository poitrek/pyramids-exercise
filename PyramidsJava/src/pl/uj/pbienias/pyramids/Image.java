package pl.uj.pbienias.pyramids;
import java.util.ArrayList;

public class Image {

	private ArrayList<Object2D> objects;
	
	public Image() {
		// TODO Auto-generated constructor stub
		objects = new ArrayList<Object2D>();
	}
	
	public Image add(Object2D obj) {
		objects.add(obj);
		return this;
	}
	
	public void draw(Canvas canvas) {
		for (Object2D obj : objects) {
			obj.draw(canvas);
		}
	}
	
	public void resize(float scale) {
		for (Object2D obj : objects) {
			obj.setPosition(obj.getPosition().scale(scale));
			obj.resize(scale);
		}
	}

}
