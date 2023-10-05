#include "A.h"

class C :public Newton_Method
{
	virtual double f(double x)
	{
		return x - tan(x);
	}

	virtual double f_diff(double x)
	{
		return -pow(tan(x), 2);
	}
public:
	C(double x_0) :Newton_Method(x_0)
	{}
};

int main()
{
	EquationSolver* s;

	C c1(4.5);
	C c2(7.7);

	s = &c1;
	cout << s->solve() << endl;

	s = &c2;
	cout << s->solve() << endl;

	return 0;
}