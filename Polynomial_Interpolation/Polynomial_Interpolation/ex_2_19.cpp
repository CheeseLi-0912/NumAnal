#include "A.h"

class B1 :public Newton_Formula
{
public:
	/*virtual double f(double x)
	{
		int _x = x;
		switch (_x)
		{
		case 0:
			return 6;
		case 1:
			return -3;
		case 2:
			return -6;
		case 3:
			return 9;
		default:
			return 0;
		}
	}*/

	B1(double* x, double* fx, int n, double t) :Newton_Formula(x,fx, n,t)
	{}

};

int main()
{
	Newton_Formula* s;
	double x[4] = { 0, 1, 2, 3 };
	double fx[4] = { 6,-3,-6,9 };
	B1 b1(x, fx, 3, 1.5);

	s = &b1;
	cout << s->solve() << endl;

	return 0;
}