import java.util.Scanner;

class Shape {
	public float height,base, radius;
    int side;

	Scanner s = new Scanner(System.in);
	void setArea(float h, float b) {
		System.out.print("Area of Triangle: "+0.5*b*h);
	}

    void setArea(int s) {
		System.out.print("Area of Square: "+s*s);
    }

    void setArea(float r) {
		System.out.print("Area of Circle: "+ r*r*3.14);
	}
}

class Triangle extends Shape{
	void getInputs() {
		System.out.print("\nEnter Height and Base of Triangle:\n");
		super.height = s.nextFloat();
		super.base = s.nextFloat();
		setArea(height,base);
	}
}

class Square extends Shape{
	void getInputs() {
		System.out.print("\n\nEnter Side of Square:");
		super.side = s.nextInt();
		setArea(side);
	}
}

class Circle extends Shape{
	void getInputs() {
		System.out.print("\n\nEnter Radius of Circle:");
		super.radius = s.nextFloat();
		setArea(radius);
	}
}

public class Tester{
	public static void main(String[] args) {

        Triangle triangle = new Triangle();
		triangle.getInputs();

        Square square = new Square();
		square.getInputs();

		Circle circle = new Circle();
		circle.getInputs();
    }
}