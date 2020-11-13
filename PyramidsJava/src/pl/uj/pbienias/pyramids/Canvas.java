package pl.uj.pbienias.pyramids;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;
import java.awt.image.RenderedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class Canvas {

	private BufferedImage image;
	private Graphics2D graphics;

	private int pixelsWidth, pixelsHeight;
	private float sizeWidth, sizeHeight;
	private float pxRatioWidth, pxRatioHeight;
	
	public float getPxRatioWidth() {
		return pxRatioWidth;
	}

	public float getPxRatioHeight() {
		return pxRatioHeight;
	}

	public Graphics2D getGraphics() {
		return graphics;
	}

	public Canvas(int px_w, int px_h, float size_w, float size_h) {
		image = new BufferedImage(px_w, px_h, BufferedImage.TYPE_INT_RGB);
		graphics = image.createGraphics();
		graphics.setColor(Color.white);
		graphics.fillRect(0, 0, px_w, px_h);
		pixelsWidth = px_w; pixelsHeight = px_h;
		sizeWidth = size_w; sizeHeight = size_h;
		pxRatioWidth = px_w / size_w;
		pxRatioHeight = px_h / size_h;
	}
	
	public void drawLine(float x1, float y1, float x2, float y2) {
		graphics.drawLine(Math.round(x1 * pxRatioWidth), Math.round(y1 * pxRatioHeight),
				  		  Math.round(x2 * pxRatioWidth), Math.round(y2 * pxRatioHeight));
	}
	
	public void drawPoint(float x, float y) {
		int ix = Math.round(x * pxRatioWidth);
		int iy = Math.round(y * pxRatioHeight);
		graphics.drawLine(ix, iy, ix, iy);
	}
	
	public void save(String str) {
		graphics.dispose();
		AffineTransform flipTransform = AffineTransform.getScaleInstance(1,  -1);
		flipTransform.translate(0, -image.getHeight(null));
		AffineTransformOp op = new AffineTransformOp(flipTransform, AffineTransformOp.TYPE_NEAREST_NEIGHBOR);
		RenderedImage rendImage = op.filter(image, null);
		File file = new File(str);
		try {
			ImageIO.write(rendImage, "png", file);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	
}
