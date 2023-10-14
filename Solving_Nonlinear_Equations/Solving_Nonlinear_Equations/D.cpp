//update?
#include "A.h"

class D1 :public Secant_Method
{
	virtual double f(double x)
	{
		return sin(x / 2) - 1;
	}
public:
	D1(double x_0 = 0, double x_1 = PI / 2) :Secant_Method(x_0, x_1)
	{}
};

class D2 :public Secant_Method
{
	virtual double f(double x)
	{
		return exp(x) - tan(x);
	}
public:
	D2(double x_0 = 1, double x_1 = 1.4) :Secant_Method(x_0, x_1)
	{}
};

class D3 :public Secant_Method
{
	virtual double f(double x)
	{
		return x * x * x - 12 * x * x + 3 * x + 1;
	}
public:
	D3(double x_0 = 0, double x_1 = -0.5) :Secant_Method(x_0, x_1)
	{}
};

int main()
{
	EquationSolver* s;

	D1 d1;
	D2 d2;
	D3 d3;

	s = &d1;
	cout << s->solve() << endl;

	s = &d2;
	cout << s->solve() << endl;

	s = &d3;
	cout << s->solve() << endl;

	return 0;
}
