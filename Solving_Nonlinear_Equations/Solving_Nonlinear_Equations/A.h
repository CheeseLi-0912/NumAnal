//update again?
#define PI 3.14159265358979323846
const int  max_itr = 1000;
const double min_err_f = 0.000001;
const double min_err_x = 0.000001;

#include <iostream>
#include <cmath>
using namespace std;

class EquationSolver
{
public:
	virtual double f(double x) = 0;
	virtual double solve() = 0;
};

class Bisection_Method :public EquationSolver
{
	double a;
	double b;
	int sgn(double x)
	{
		if (x < 0) return -1;
		if (x == 0) return 0;
		if (x > 0) return 1;
	}

public:
	Bisection_Method(double a, double b)
	{
		this->a = a;
		this->b = b;
	}

	virtual double solve()
	{
		double h, c;
		double u, v, w;

		u = f(a);
		v = f(b);
		for (int k = 0; k <= max_itr; k++)
		{
			h = b - a;
			c = a + h / 2;
			if (abs(h) < min_err_x || k == max_itr)
				break;
			w = f(c);
			if (abs(w) < min_err_f)
				break;
			else if (sgn(w) != sgn(u))
			{
				b = c;
				v = w;
			}
			else
			{
				a = c;
				u = w;
			}
		}
		return c;
	}
};

class Newton_Method :public EquationSolver
{
	double x_0;

public:
	virtual double f_diff(double x) = 0;

	Newton_Method(double x_0)
	{
		this->x_0 = x_0;
	}

	virtual double solve()
	{
		double x;
		double u;

		x = x_0;
		for (int k = 0; k <= max_itr; k++)
		{
			u = f(x);
			if (abs(u) < min_err_f)
				break;
			x = x - u / f_diff(x);
		}
		return x;
	}
};

class Secant_Method :public EquationSolver
{
	double x_0;
	double x_1;

public:
	Secant_Method(double x_0, double x_1)
	{
		this->x_0 = x_0;
		this->x_1 = x_1;
	}

	virtual double solve()
	{
		double x_n, x_n_1;
		double u, v, s;

		x_n = x_1;
		x_n_1 = x_0;
		u = f(x_n);
		v = f(x_n_1);

		for (int k = 2; k <= max_itr; k++)
		{
			s = (x_n - x_n_1) / (u - v);
			x_n_1 = x_n;
			v = u;
			x_n = x_n - u * s;
			if (abs(x_n - x_n_1) < min_err_x)
				break;
			u = f(x_n);
			if (abs(u) < min_err_f)
				break;
		}
		return x_n;
	}
};
