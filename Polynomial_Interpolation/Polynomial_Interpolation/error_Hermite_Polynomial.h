// Hermite interpolation
#include <iostream>
using namespace std;

class Hermite_Interpolation
{
private:

	double* x; // interpolated value, carried by pointer
	double* fx; // func to interpolated value, carried by pointer
	double* fx_d1; // func'd to interpolated value, carried by pointer
	int n; // the numbers are x_0 to x_n
	double t; //given value, aiming to get f(t)

	int* x_for_a; //index series for a

public:

	//virtual double f(double x) = 0;

	Hermite_Interpolation(double* x, double* fx, double* fx_d1, int n, double t);

	double pai(int k);

	double a(int* x_for_a, int n);

	double solve();
};

Hermite_Interpolation::Hermite_Interpolation(double* x, double* fx, double* fx_d1, int n, double t)
{
	this->x = x;
	this->fx = fx;
	this->fx_d1 = fx_d1;
	this->n = n;
	this->t = t;

	for (int i = 0; i <= n; i++)
	{
		x_for_a[2 * i] = i;
		x_for_a[2 * i + 1] = i;
	}
}

double Hermite_Interpolation::pai(int k)
{
	double res = 1;
	for (int i = 0; i <= k - 1; i++)
	{
		res *= (t - x[i]) * (t - x[i]);
	}
	return res;
}

double Hermite_Interpolation::a(int* x_for_a, int n) // 0,0,¡¤¡¤¡¤,n,n
{
	if (n == 1)
		return fx[*x_for_a];
	else if (n == 2 && *x_for_a == *(x_for_a + 1))
		return fx_d1[*x_for_a];
	else
		return (a(x_for_a + 1, n - 1) - a(x_for_a, n - 1)) / (*(x_for_a + n - 1) - *x_for_a);
}

double Hermite_Interpolation::solve()
{
	double res = 0;
	for (int k = 0; k <= n; k++)
	{
		res += a(x_for_a, 2 * k + 2) * pai(k);
	}
	return res;
}