#include <iostream>
#include <cmath>
#include <Eigen/Dense>
using namespace std;
const int N = 10000;

class complete_cubic_spline
{
private:
	int n;
	double* x;
	double* fx;
	double* fx_d1;
	double* fx_d2;
	double* M;
public:
	virtual double function(double x) = 0; 
	virtual double function_d1(double x) = 0;

	complete_cubic_spline(double* x, int n)
	{
		this->n = n;
		this->x = x;

		fx = new double[n + 1];
		for (int i = 1; i <= n; i++)
		{
			fx[i] = function(x[i]);
		}

		fx_d1 = new double[n + 2];
		fx_d1[1] = function_d1(x[1]);
		for (int i = 2; i <= n; i++)
		{
			fx_d1[i] = (fx[i] - fx[i - 1]) / (x[i] - x[i - 1]);
		}
		fx_d1[n+1] = function_d1(x[n]);

		fx_d2 = new double[n + 1];
		fx_d2[1] = (fx_d1[2] - fx_d1[1]) / (x[2] - x[1]);
		for (int i = 2; i <= n - 1; i++)
		{
			fx_d2[i] = (fx_d1[i + 1] - fx_d1[i]) / (x[i + 1] - x[i - 1]);
		}
		fx_d2[n] = (fx_d1[n + 1] - fx_d1[n]) / (x[n] - x[n - 1]);

		double* miu = new double[n];
		double* lambda = new double[n];
		for (int i = 2; i <= n - 1; i++)
		{
			miu[i] = (x[i] - x[i - 1]) / (x[i + 1] - x[i - 1]);
			lambda[i] = (x[i + 1] - x[i]) / (x[i + 1] - x[i - 1]);
		}

		Eigen::MatrixXd A(n, n);
		Eigen::VectorXd b(n);
		Eigen::VectorXd X(n);

		A(0, 0) = 2; A(0, 1) = 1;
		for (int i = 1; i <= n - 2; i++)
		{
			A(i, i - 1) = miu[i+1];
			A(i, i) = 2;
			A(i, i + 1) = lambda[i+1];
		}
		A(n - 1, n - 2) = 1; A(n - 1, n - 1) = 2;

		for (int i = 0; i <= n - 1; i++)
		{
			b[i] = 6 * fx_d2[i+1];
		}

		if (A.fullPivLu().isInvertible())
			X = A.fullPivLu().solve(b);
		else
			cout << "Matrix A is not invertible. The system may not have a unique solution.\n";

		M = new double[n + 1];
		for (int i = 1; i <= n; i++)
		{
			M[i] = X(i - 1);
		}
	}

	double spline_s(int i, double t)
	{
		return function(x[i]) + function_d1(x[i]) * (t - x[i]) + 0.5 * M[i] * pow(t - x[i], 2) + 1.0 / 6 * (M[i + 1] - M[i]) / (x[i + 1] - x[i]) * pow(t - x[i], 3);
	}

	double solve(double t)
	{
		int i;
		for (i = 1; i <= n - 1; i++)
		{
			if ((t > x[i] || t == x[i]) && t < x[i + 1])
				break;
		}
		return spline_s(i, t);
	}
};
