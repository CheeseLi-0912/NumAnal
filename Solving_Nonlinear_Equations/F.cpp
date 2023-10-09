//update?
#include "A.h"

class F
{
	double l;
	double h;
	double D;
	double beta;

	double A;
	double B;
	double C;
	double E;

public:
	double _f(double x)
	{	
		return A * sin(x) * cos(x) + B * sin(x) * sin(x) - C * cos(x) - E * sin(x);
	}

	double _f_diff(double x)
	{
		return A * cos(2 * x) + 2 * B * sin(x) * cos(x) + C * sin(x) - E * cos(x);
	}

	F(double l, double h, double D, double beta)
	{
		this->l = l;
		this->h = h;
		this->D = D;
		this->beta = beta;

		A = l * sin(beta);
		B = l * cos(beta);
		C = (h + D / 2) * sin(beta) - D * tan(beta) / 2;
		E = (h + D / 2) * cos(beta) - D / 2;
	}
};

class F1 :public F, public Newton_Method
{
public:
	F1(double l = 89, double h = 49, double D = 55, double beta = 11.5 * PI / 180, double x_0 = 33 * PI / 180)
		:F(l, h, D, beta),Newton_Method(x_0)
	{}
	virtual double f(double x)
	{
		return _f(x);
	}
	virtual double f_diff(double x)
	{
		return _f_diff(x);
	}
};

class F2 :public F, public Newton_Method
{
public:
	F2(double l = 89, double h = 49, double D = 30, double beta = 11.5 * PI / 180, double x_0 = 33 * PI / 180)
		:F(l, h, D, beta), Newton_Method(x_0)
	{}

	virtual double f(double x)
	{
		return _f(x);
	}

	virtual double f_diff(double x)
	{
		return _f_diff(x);
	}
};

class F3 :public F, public Secant_Method
{
public:
	F3(double l = 89, double h = 49, double D = 30, double beta = 11.5 * PI / 180,
		double x_0 = 70 * PI / 180, double x_1 = 75 * PI / 180)
		:F(l, h, D, beta), Secant_Method(x_0, x_1)
	{}

	virtual double f(double x)
	{
		return _f(x);
	}
};

int main()
{
	EquationSolver* s;

	F1 f1;
	F2 f2;
	F3 f3;

	s = &f1;
	cout << s->solve() << endl;

	s = &f2;
	cout << s->solve() << endl;

	s = &f3;
	cout << s->solve() << endl;

	return 0;
}
