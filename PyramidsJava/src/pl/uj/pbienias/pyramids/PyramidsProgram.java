package pl.uj.pbienias.pyramids;

//import javax.imageio.ImageIO;
//
//import java.awt.Graphics2D;
//import java.awt.Shape;
//import java.awt.geom.AffineTransform;
//import java.awt.geom.Point2D;
//import java.awt.Color;
//import java.awt.image.AffineTransformOp;
//import java.awt.image.BufferedImage;
//import java.awt.image.RenderedImage;
//import java.io.File;
import java.io.IOException;

public class PyramidsProgram {

	public static void main(String[] args) throws IOException {
		
		
		Canvas canvas = new Canvas(200, 200, 10, 10);
		int base_1 = 10; int base_2 = 6;
		StepPyramid p1 = new StepPyramid(0, 0, base_2, 5, 10);
		SymmetricPyramid p2 = new SymmetricPyramid(base_2, 0, base_1-base_2, 5);
		EquilateralPyramid p3 = new EquilateralPyramid(0, 0, base_1);
		p1.setColor(255, 191, 64);
		p2.setColor(255, 223, 64);
		p3.setColor(255, 255, 64);
		Image img = new Image();
		img.add(p3).add(p2).add(p1);
		img.resize(1.f);
		img.draw(canvas);
		canvas.save("pyramid1.png");
		

//		int width = 200;
//		int height = 200;
//		// 1
//		BufferedImage bufferedImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
//		// 2
//		AffineTransform tx = AffineTransform.getScaleInstance(1, -1);
//		System.out.println(tx);
//		tx.translate(0, -bufferedImage.getHeight(null));
//		AffineTransformOp op = new AffineTransformOp(tx, AffineTransformOp.TYPE_NEAREST_NEIGHBOR);
////		bufferedImage = op.filter(bufferedImage, null);
//		Graphics2D g2d = bufferedImage.createGraphics();
//		System.out.println(g2d.getTransform());
//		g2d.setColor(Color.white);
////		g2d.setTransform(new AffineTransform(-1.f, 0.f, 0.f, 1.f, 0.f, 0.f));
//		
//		g2d.fillRect(0, 0, width, height);
//		g2d.setColor(new Color(255, 191, 64));
////		g2d.draw((Shape) new java.awt.Point(20, 40));
//		g2d.drawLine(20, 20, 160, 20);
//		g2d.drawLine(20, 20, 100, 120);
//		g2d.drawLine(160, 20, 100, 120);
//		g2d.setColor(new Color(255, 255, 64));
//		System.out.println(g2d.getTransform());
////		g2d.fillOval(0, 0, width, height);
//
//		g2d.dispose();
//		RenderedImage rendImage = op.filter(bufferedImage, null);
//
//		File file = new File("newimage.png");
//		ImageIO.write(rendImage, "png", file);
//
//		file = new File("newimage.jpg");
//		ImageIO.write(rendImage, "jpg", file);
//		System.out.println("saved image.");

	}

}