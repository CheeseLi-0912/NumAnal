#include "A.h"

class B1 :public Bisection_Method
{
	virtual double f(double x)
	{
		return 1 / x - tan(x);
	}
public:
	B1(double a = 0, double b = PI / 2) :Bisection_Method(a, b)
	{}
};

class B2 :public Bisection_Method
{
	virtual double f(double x)
	{
		return 1 / x - pow(2, x);
	}
public:
	B2(double a = 0, double b = 1) :Bisection_Method(a, b)
	{}
};

class B3 :public Bisection_Method
{
	virtual double f(double x)
	{
		return pow(2, -x) + exp(x) + 2 * cos(x) - 6;
	}
public:
	B3(double a = 1, double b = 3) :Bisection_Method(a, b)
	{}
};

class B4 :public Bisection_Method
{
	virtual double f(double x)
	{
		return (x * x * x + 4 * x * x + 3 * x + 5) / (2 * x * x * x - 9 * x * x + 18 * x - 2);
	}
public:
	B4(double a = 0, double b = 4) :Bisection_Method(a, b)
	{}
};

int main()
{
	EquationSolver* s;

	B1 b1;
	B2 b2;
	B3 b3;
	B4 b4;

	s = &b1;
	cout << s->solve() << endl;

	s = &b2;
	cout << s->solve() << endl;

	s = &b3;
	cout << s->solve() << endl;

	s = &b4;
	cout << s->solve() << endl;

	return 0;
}