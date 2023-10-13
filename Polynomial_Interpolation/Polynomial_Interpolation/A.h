// Newton Formula
#include <iostream>
using namespace std;

class Newton_Formula
{
private:

	double* x; // interpolated value, carried by pointer
	double* fx; // func to interpolated value, carried by pointer
	int n; // the numbers are x_0 to x_n
	double t; //given value, aiming to get f(t)

public:

	Newton_Formula(double* x, double* fx, int n, double t);

	double pai(int k);

	double a(int i, int j);

	double solve();
};

Newton_Formula::Newton_Formula(double* x, double* fx, int n, double t)
{
	this->x = x;
	this->fx = fx;
	this->n = n;
	this->t = t;
}

double Newton_Formula::pai(int k)
{
	double res = 1;
	for (int i = 0; i <= k - 1; i++)
	{
		res *= t - x[i];
	}
	return res;
}

double Newton_Formula::a(int i, int j)
{
	if (i == j)
		return fx[i];
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