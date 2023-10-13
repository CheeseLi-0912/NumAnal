// Hermite interpolation
#include <iostream>
using namespace std;

class Hermite_Interpolation
{
private:

	double* x; // interpolated value, carried by pointer
	double* x_diff; // derivative of interpolated value, carried by pointer
	int n; // the numbers are x_0 to x_n
	double t; //given value, aiming to get f(t)

public:

	virtual double f(double x) = 0;

	Hermite_Interpolation(double* x, double* x_diff, int n, double t);

	double pai(int k);

	double a(int i, int j);

	double solve();
};

Hermite_Interpolation::Hermite_Interpolation(double* x, double* x_diff, int n, double t)
{
	this->x = x;
	this->x_diff = x_diff;
	this->n = n;
	this->t = t;
}

double Hermite_Interpolation::pai(int k)
{
	double res = 1;
	for (int i = 0; i <= k - 1; i++)
	{
		res *= (t - x[i])*(t - x_diff[i]);
	}
	return res;
}

double Hermite_Interpolation::a(int i, int j, int n)
{
	if (i == j && n==2)
		return f(x_diff[i]);
	else
		return (a(i + 1, j) - a(i, j - 1)) / (x[j] - x[i]);
}

double Newton_Formula::solve()
{
	double res = 0;
	for (int k = 0; k <= n; k++)
	{
		res += a(0, k) * pai(k);
	}
	return res;
}