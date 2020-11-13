package pl.uj.pbienias.pyramids;

/**
 * Class representing an infinite line
 * used to compute Line.intersection()
 * @author Piotr
 *
 */
public class InfLine {
	
	float A, B, C;

	public InfLine(Line L) {
		A = L.getStart().y - L.getStop().y;
		B = L.getStop().x - L.getStart().x;
		C = L.getStart().x * L.getStop().y - L.getStart().y * L.getStop().x;
	}
	
	public enum posType{
		OVERLAP, INTERSECT, DISJOINT;
	}
	
	public posType mutualPosition(InfLine ifL) {
		if (Float.compare(this.A * ifL.B - this.B * ifL.A, 0.f) != 0) {
			return posType.INTERSECT;
		}
		else {
			float coeff1 = (this.A == 0) ? this.B : this.A;
			float coeff2 = (ifL.A == 0) ? ifL.B : ifL.A;
			if (Float.compare(this.C / coeff1, ifL.C / coeff2) == 0)
				return posType.OVERLAP;
			else
				return posType.DISJOINT;
		}
	}
	
	public Point intersection(InfLine ifL) {
		return new Point(
				(this.B * ifL.C - this.C * ifL.B) / (this.A * ifL.B - this.B * ifL.A),
				(this.A * ifL.C - this.C * ifL.A) / (this.B * ifL.A - this.A * ifL.B)
				);
	}

	public float getA() {
		return A;
	}

	public float getB() {
		return B;
	}

	public float getC() {
		return C;
	}

}
