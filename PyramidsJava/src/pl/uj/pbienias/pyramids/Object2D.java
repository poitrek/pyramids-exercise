package pl.uj.pbienias.pyramids;

import java.awt.Color;
import java.awt.Graphics2D;

public abstract class Object2D {
		
	protected Color color = new Color(0, 0, 0);
	
	public void draw(Canvas canvas) {
		canvas.getGraphics().setColor(color);
		drawShape(canvas);
	}
	
	protected abstract void drawShape(Canvas canvas);
	
	public abstract Point getPosition();
	
	public abstract void setPosition(Point p);
	
	public void move(Line line) {
		setPosition(getPosition().add(line.getStop()).subtr(line.getStart()));
	}
	
	public abstract float getArea();
	
	public void setColor(int r, int g, int b) {
		color = new Color(r, g, b);
	}
	
	public abstract void resize(float scale);
	
}
