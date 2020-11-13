package pl.uj.pbienias.pyramids;

import java.util.ArrayList;

public class Line extends Object2D {
	
	private Point start, stop;
	
	public Line(float x1, float y1, float x2, float y2) {
		start = new Point(x1, y1);
		stop = new Point(x2, y2);
	}
	
	public Line(Point _start, Point _stop) {
		start = _start;
		stop = _stop;
	}
	
	public Point getStart() {
		return start;
	}

	public void setStart(Point start) {
		this.start = start;
	}

	public Point getStop() {
		return stop;
	}

	public void setStop(Point stop) {
		this.stop = stop;
	}

	public float dx() {
		return stop.x - start.x;
	}
	
	public float dy() {
		return stop.y - start.y;
	}
	
	public boolean isPoint() {
		return start.equals(stop);
	}
	
	public Point getMiddle() {
		return new Point((start.x + stop.x) / 2.f, (start.y + stop.y) / 2.f);
	}
	
	public float len() {
		float dx = dx(), dy = dy();
		return (float)Math.sqrt(dx * dx + dy * dy);
	}
	
	public Line intersection(Line line) throws NoIntersectionException {
		InfLine ifL1 = new InfLine (this);
		InfLine ifL2 = new InfLine (line);
		switch (ifL1.mutualPosition(ifL2)) {
		case INTERSECT:
			Point s = ifL1.intersection(ifL2);
			float x1 = Math.min(this.start.x, this.stop.x);
			float x2 = Math.max(this.start.x, this.stop.x);
			float x3 = Math.min(line.start.x, line.stop.x);
			float x4 = Math.max(line.start.x, line.stop.x);
			if (s.x >= x1 && s.x <= x2 && s.x >= x3 && s.x <= x4)
				return new Line(s, s);
			else
				throw new NoIntersectionException();
		case OVERLAP:
			ArrayList<Line> lines = new ArrayList<Line>();
			lines.add(line);
			lines.add(new Line(this.start, line.start));
			lines.add(new Line(this.start, line.stop));
			lines.add(new Line(this.stop, line.start));
			lines.add(new Line(this.stop, line.stop));
			// Get the longest line segment
			Line maxLine = this;
			for (Line l : lines)
				if (l.len() > maxLine.len())
					maxLine = l;
			// If the longest line segment is longer than the sum of the input segments
			// - they are separate
			if (maxLine.len() > this.len() + line.len()) {
				throw new NoIntersectionException();
			}
			else {
				ArrayList<Point> lineEnds = new ArrayList<Point>();
				lineEnds.add(this.start);
				lineEnds.add(this.stop);
				lineEnds.add(line.start);
				lineEnds.add(line.stop);
				lineEnds.remove(maxLine.start);
				lineEnds.remove(maxLine.stop);
				return new Line(lineEnds.get(0), lineEnds.get(1));
			}
		case DISJOINT:
			throw new NoIntersectionException();
		default:
			throw new NoIntersectionException();
		}
	}

	@Override
	protected void drawShape(Canvas canvas) {
		// TODO Auto-generated method stub
		canvas.drawLine(start.x, start.y, stop.x, stop.y);
	}

	@Override
	public Point getPosition() {
		// TODO Auto-generated method stub
		return start;
	}

	@Override
	public void setPosition(Point p) {
		// TODO Auto-generated method stub
		stop = stop.subtr(start).add(p);
		start = p;
	}

	@Override
	public float getArea() {
		// TODO Auto-generated method stub
		return 0.f;
	}
	
	@Override
	public void resize(float scale) {
		stop.x = start.x + scale * dx();
		stop.y = start.y + scale * dy();
	}
	
	@Override
	public String toString() {
		return "Line(" + start.x + ", " + start.y + ", " + stop.x + ", " + stop.y + ")";
	}

}
