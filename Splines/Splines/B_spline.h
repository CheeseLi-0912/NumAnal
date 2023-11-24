#include "Spline.h"

class B_spline:public spline
{
public:
	int d; // the dimension of S (S_d^d-1)
	double* u; // knot points

	~B_spline()
	{
		delete[] u;
	}

	B_spline(int n, int d, double* x, double* fx, double a, double b) :spline(n, x, fx, a, b)
		// ensure d<=n
	{
		this->d = d;
		u = new double[n + d + 2];
		for (int i = 1; i <= n + d + 1; i++)
		{
			u[i] = a + (b - a) * (i - 1) / (n + d);
		}
	}

	double B_Basis(int i, int d, double t)
	{
		if (d == 0)
		{
			if (t >= u[i] && t < u[i + 1])
				return 1;
			else
				return 0;
		}
		else
		{
			return (t - u[i]) / (u[i + d] - u[i]) * B_Basis(i, d - 1, t)
				+ (u[i + d + 1] - t) / (u[i + d + 1] - u[i + 1]) * B_Basis(i + 1, d - 1, t);
		}
	}

	double solve(double t)
	{
		double res = 0;
		for (int i = 1; i <= n; i++)
		{
			res += fx[i] * B_Basis(i, d, t);
		}
		return res;
	}
};