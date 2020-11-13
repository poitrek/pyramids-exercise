package pl.uj.pbienias.pyramids;

public class NoIntersectionException extends Exception {
	
	@Override
	public String toString() {
		return "Exception: the line segments have no intersection";
	}

}
