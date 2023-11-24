#include "Spline.h"

class cardinal_B:public spline
{
public:
	double move;
	double* _a;

	~cardinal_B()
	{
		delete[] _a;
	}

	cardinal_B(int n, double* x, double* fx, double a, double b) :spline(n, x, fx, a, b)
	{
		move = 1 - a;
	}

	virtual double Basis(int i, double x) = 0;
};

class cubic_cardinal_B :public cardinal_B
{
public:
	double Basis(int i, double x) // Example 3.54
	{
		if (x > i - 1 && x <= i)
			return pow(x - i + 1, 3) / 6.0;
		else if (x > i && x <= i + 1)
			return 2.0 / 3 - 0.5 * (x - i + 1) * pow(i + 1 - x, 2);
		else if (x > i + 1 && x <= i + 3)
			return Basis(i, 2 * i + 2 - x);
		else
			return 0;
	}

	cubic_cardinal_B(int n, double* x, double* fx, double a, double b, double fa_diff, double fb_diff)
		// fa_diff represents f'[1], fb_diff represents f'[n]
		:cardinal_B(n, x, fx, a, b)
	{
		Eigen::MatrixXd A(n, n);
		Eigen::VectorXd B(n);
		Eigen::VectorXd X(n);

		// solve for a_0,，，，,a_N-1
		A.setZero();
		B.setZero();
		A(0, 0) = 2; A(0, 1) = 1;
		A(n - 1, n - 2) = 1; A(n - 1, n - 1) = 2;
		for (int i = 1; i <= n - 2; i++)

		{
			A(i, i - 1) = 1;
			A(i, i) = 4;
			A(i, i + 1) = 1;
		}

		B(0) = 3 * fx[1] + fa_diff;
		B(n - 1) = 3 * fx[n] - fb_diff;

		for (int i = 1; i <= n - 2; i++)
		{
			B(i) = 6 * fx[i + 1];
		}

		if (A.fullPivLu().isInvertible())
			X = A.fullPivLu().solve(B);
		else
			cout << "Matrix A is not invertible. The system may not have a unique solution.\n";

		_a = new double[n + 2];
		for (int i = 0; i <= n-1; i++)
		{
			_a[i] = X(i);
		}
		_a[n] = _a[n - 2] + 2 * fb_diff;
		_a[n + 1] = _a[1] - 2 * fa_diff; // a[n+1] represents a[-1]
		
	}

	double solve(double t) // (3.71)
	{
		t += move;

		double S;
		S = _a[n + 1] * Basis(-1, t);
		for (int i = 0; i <= n; i++)
		{
			S += _a[i] * Basis(i, t);
		}
		return S;
	}
};

class quadratic_cardinal_B :public cardinal_B
{
public:
	//double Basis(int i, double x) // Example 3.25, especially for t[i]=i+1/2
	//{
	//	if (x > i - 0.5 && x <= i + 0.5)
	//		return 0.5 * pow(x - i + 0.5, 2);
	//	else if (x > i + 0.5 && x <= i + 1.5)
	//		return 0.5 * (x - i + 0.5) * (i + 1.5 - x) + 0.5 * (i + 2.5 - x) * (x - i - 0.5);
	//	else if (x > i + 1.5 && x <= i + 2.5)
	//		return 0.5 * pow(i + 2.5 - x, 2);
	//	else
	//		return 0;
	//}

	double Basis(int i, double x) // Example 3.53
	{
		if (x > i - 1 && x <= i)
			return 0.5 * pow(x - i + 1, 2);
		else if (x > i && x <= i + 1)
			return 0.75 - pow(x - i - 0.5, 2);
		else if (x > i + 1 && x <= i + 2)
			return 0.5 * pow(i + 2 - x, 2);
		else
			return 0;
	}

	quadratic_cardinal_B(int n, double* x, double* fx, double a, double b, double fa, double fb)
		// fx[i]=f(i+1/2), fa=f(1), fb=f(n)
		:cardinal_B(n, x, fx, a, b)
	{
		Eigen::MatrixXd A(n-1, n-1);
		Eigen::VectorXd B(n-1);
		Eigen::VectorXd X(n-1);

		// solve for a_1,，，，,a_N-1
		A.setZero();
		B.setZero();
		A(0, 0) = 5; A(0, 1) = 1;
		A(n - 2, n - 3) = 1; A(n - 2, n - 2) = 5;
		for (int i = 1; i <= n - 3; i++)
		{
			A(i, i - 1) = 1;
			A(i, i) = 6;
			A(i, i + 1) = 1;
		}

		B(0) = 8 * fx[1] - 2 * fa;
		B(n - 2) = 8 * fx[n - 1] - 2 * fb;
		for (int i = 1; i <= n - 3; i++)
		{
			B(i) = 8 * fx[i+1];
		}

		if (A.fullPivLu().isInvertible())
			X = A.fullPivLu().solve(B);
		else
			cout << "Matrix A is not invertible. The system may not have a unique solution.\n";

		_a = new double[n + 1];
		for (int i = 1; i <= n - 1; i++)
		{
			_a[i] = X(i - 1);
		}
		_a[0] = 2 * fa - _a[1];
		_a[n] = 2 * fb - _a[n - 1];

	}

	double solve(double t) // (3.75)
	{
		t += move;

		double S = 0;
		for (int i = 0; i <= n; i++)
		{
			S += _a[i] * Basis(i, t);
		}
		return S;
	}
};
