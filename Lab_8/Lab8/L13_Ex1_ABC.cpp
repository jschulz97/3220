// L13_Ex1_ABC.cpp

// By Luis Rivera

//Which methods should be virtual? display resize area destructor

#include <iostream>
#include <cmath>
using namespace std;

class BaseConic {
	protected:
		double x;
		double y;

	public:
		// Notice the default values. They don't need to be 0
		BaseConic(double x0 = 0, double y0 = 0){x = x0; y = y0;}
		virtual ~BaseConic(){};
		void move(double nx, double ny){x = nx; y = ny;}
		virtual double area() = 0; // a pure virtual function ==> ABC
		virtual void display() = 0;
		virtual void resize() = 0;
};



//-------------------------------------------------------ELLIPSE--------------------------------------------------------

class Ellipse : public BaseConic {
	private:
		double a; 	// semi-major axis
		double b; 	// semi-minor axis
		double angle; // orientation angle

	public:
		Ellipse(double x0, double y0, double a0, double b0, double an0);
		~Ellipse(){}
		void resize();
		virtual double area() {return M_PI*a*b;}
		void rotate(double nang){angle += nang;}
		virtual void display();
		void vertices();
};

// Notice the default values. Those are used if no parameter is given when
// an object is created.
// Notice how the BaseConic constructor can be called. If other constructors where defined,
// those could be used instead.
Ellipse::Ellipse(double x0=1,double y0=0,double a0=0,double b0=0,double an0=0) : BaseConic(x0,y0) {
	// x and y are set in the BaseConic constuctor
	a = a0;
	b = b0;
	angle = an0;
}

void Ellipse::display() {
	cout << "x = " << x << ", y = " << y << ", a = " << a << ", b = " << b
		 << ", angle = " << angle << ", Area = " << this->area() << endl;
}

/**
 * Calculates the location of the vertices of the ellipse
 */
void Ellipse::vertices() {
	cout << "Vertices: " << endl << (-a)*cos(angle/360*2*M_PI) + x << "," << (-a)*sin(angle/360*2*M_PI) + y;
	cout << endl << a*cos(angle/360*2*M_PI) + x << "," << a*sin(angle/360*2*M_PI) + y << "\n";
}

/**
 * Resizes the ellipse by prompting a new semi-major and semi-minor axis.
 */
void Ellipse::resize() {
	cout << "\nEnter new semi-major axis: ";
	cin >> a;
	cout << "\nEnter new semi-minor axis: ";
	cin >> b;
}



//-------------------------------------------------------CIRCLE--------------------------------------------------------

class Circle : public BaseConic {
	private:
		double r; 	// radius
		
	public:
		void resize();
		virtual double area() {return M_PI*r*r;}
		Circle(double x0=1,double y0=1,double r0=1) : BaseConic(x0,y0){r = r0;}
		~Circle(){}
		virtual void display();
		string findLoc(double x,double y);
};

void Circle::display() {
	cout << "x = " << x << ", y = " << y << ", r = " << r 
		 << ", Area = " << this->area() << endl;
}

/**
 * Finds the location of a point on the circle using the pythagorean theorem.
 */
string Circle::findLoc(double a,double b) {
	a-=x; //Offset as if circle is at origin
	b-=y;
	double r1 = pow(pow(a,2) + pow(b,2),.5);
	if(r1 < r)
		return "inside";
	else if(r1 > r)
		return "outside";
	else
		return "on";
}

void Circle::resize() {
	cout << "\nEnter new radius: ";
	cin >> r;
}

int main(){
	//BaseConic b0;	// not possible to create an object of the ABC
	Ellipse e0, e1(1), e2(2,3), e3(4,5,6), e4(0,0,4,4,30), e5(0.1,0.2,0.3,0.4,0.5);
	Circle c0, c1(2,-1,5);
		
	e0.display();	e1.display();	e2.display();
	e3.display();	e4.display(); 	e5.display();
	
	cout << "\n--------------------------------------------------------------\n" << endl;
	
	c0.display();	c1.display();

	cout << "\n--------------------------------------------------------------\n" << endl;

	// You CAN use ABC pointers and references
	BaseConic *bptr1 = &e4;
	BaseConic *bptr2 = new Ellipse(1,1,2,3,0.5);
	BaseConic &bref1 = e5;
	bptr1->display();
	bptr2->display();
	bref1.display();
	
	cout << "\n--------------------------------------------------------------\n" << endl;	
	BaseConic *bptr3 = &c0;
	BaseConic *bptr4 = new Circle(-3,0,1.5);
	BaseConic &bref2 = c1;
	bptr3->display();
	bptr4->display();
	bref2.display();
	
	cout << "\n--------------------------------------------------------------\n" << endl;

	cout << "\ne4.display():\n";
	e4.display();
	cout << "\ne4.move(2,1);\n";
	e4.move(2,1);
	cout << "\ne4.display():\n";
	e4.display();

	cout << "\n--------------------------------------------------------------\n" << endl;

	cout << "\ne4.display():\n";
	e4.display();
	cout << "\ne4.rotate(60);\n";
	e4.rotate(60);
	cout << "\ne4.display():\n";
	e4.display();

	cout << "\n--------------------------------------------------------------\n" << endl;

	cout << "e4.vertices():\n";
	e4.vertices();
	cout << "\ne4.rotate(-60);\n";
	e4.rotate(-60);
	cout << "\ne4.display():\n";
	e4.display();
	cout << "\ne4.vertices():\n";
	e4.vertices();

	cout << "\n--------------------------------------------------------------\n" << endl;

	cout << "\nc1.display();\n";
	c1.display();
	cout << "\nc1.resize();\n";
	c1.resize();
	cout << "\nc1.display();\n";
	c1.display();

	cout << "\n--------------------------------------------------------------\n" << endl;

	cout << "\nEnter a point, x: ";
	int x,y;
	cin >> x;
	cout << "y: ";
	cin >> y;
	cout << "\nc1.findLoc(" << x << "," << y << ");\n";
	cout << "The point is " << c1.findLoc(x,y) << " the circle c1.\n";

	cout << "\n--------------------------------------------------------------\n" << endl;

	delete bptr2;
	delete bptr4;
}
