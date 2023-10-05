#include "A.h"
const double L = 10;
const double r = 1;
const double V = 12.4;

class E1 :public Bisection_Method
{
	virtual double f(double x)
	{
		return L * (0.5 * PI * r * r - r * r * asin(x / r) - x * sqrt(r * r - x * x)) - V;
	}
public:
	E1(double a = 0, double b = r) :Bisection_Method(a, b)
	{}
};

class E2 :public Newton_Method
{
	virtual double f(double x)
	{
		return L * (0.5 * PI * r * r - r * r * asin(x / r) - x * sqrt(r * r - x * x)) - V;
	}

	virtual double f_diff(double x)
	{
		return L * (-r / sqrt(1 - pow(x / r, 2)) - sqrt(r * r - x * x) + x * x / sqrt(r * r - x * x));
	}
public:
	E2(double x_0 = 0) :Newton_Method(x_0)
	{}
};

class E3 :public Secant_Method
{
	virtual double f(double x)
	{
		return L * (0.5 * PI * r * r - r * r * asin(x / r) - x * sqrt(r * r - x * x)) - V;
	}
public:
	E3(double x_0 = r/2, double x_1 = r) :Secant_Method(x_0, x_1)
	{}
};
int main()
{
	EquationSolver* s;

	E1 e1;
	E2 e2;
	E3 e3;

	s = &e1;
	cout << s->solve() << endl;

	s = &e2;
	cout << s->solve() << endl;

	s = &e3;
	cout << s->solve() << endl;

	return 0;
}