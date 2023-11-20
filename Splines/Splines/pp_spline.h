#include "Spline.h"

class linear_spline :public spline // S_1^0
{
public:
	linear_spline(int n, double* x, double* fx, double a, double b) :spline(n, x, fx, a, b)
	{}

	double spline_s(int i, double t)
	{
		return (fx[i + 1] - fx[i]) / (x[i + 1] - x[i]) * (t - x[i]) + fx[i];
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

class cubic_spline:public spline // S_3^2
{
public:
	double* fx_d1; // single divided difference of fx, fx_d1[i] = f(x[i-1],x[i])
	double* fx_d2; // double divided difference of fx, fx_d2[i] = f(x[i-1],x[i],x[i+1])
	double* miu;
	double* lambda;
	double* m;
	double* M;

	~cubic_spline()
	{
		delete[] fx_d1;
		delete[] fx_d2;
		delete[] miu;
		delete[] lambda;
		delete[] m;
		delete[] M;
		
	}

	cubic_spline(int n, double* x, double* fx, double a, double b, double fa_diff, double fb_diff)
		:spline(n, x, fx, a, b)
	{

		// divided difference list
		fx_d1 = new double[n + 2];
		fx_d1[1] = fa_diff;
		for (int i = 2; i <= n; i++)
		{
			fx_d1[i] = (fx[i] - fx[i - 1]) / (x[i] - x[i - 1]);
		}
		fx_d1[n + 1] = fb_diff;

		fx_d2 = new double[n + 1];
		fx_d2[1] = (fx_d1[2] - fx_d1[1]) / (x[2] - x[1]);
		for (int i = 2; i <= n - 1; i++)
		{
			fx_d2[i] = (fx_d1[i + 1] - fx_d1[i]) / (x[i + 1] - x[i - 1]);
		}
		fx_d2[n] = (fx_d1[n + 1] - fx_d1[n]) / (x[n] - x[n - 1]);

		// parameters for matrix A
		miu=new double[n];
		lambda=new double[n];
		for (int i = 2; i <= n - 1; i++)
		{
			miu[i] = (x[i] - x[i - 1]) / (x[i + 1] - x[i - 1]);
			lambda[i] = (x[i + 1] - x[i]) / (x[i + 1] - x[i - 1]);
		}
	}

	double spline_s(int i, double t)
	{
		return fx[i] + m[i] * (t - x[i]) + 0.5 * M[i] * pow(t - x[i], 2) + 1.0 / 6 * (M[i + 1] - M[i]) / (x[i + 1] - x[i]) * pow(t - x[i], 3); // (3.14)
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

class complete_cubic_spline:public cubic_spline
{
public:
	complete_cubic_spline(int n, double* x, double* fx, double a, double b, double fa_diff, double fb_diff)
		:cubic_spline(n, x, fx, a, b, fa_diff, fb_diff)
	{
		Eigen::MatrixXd A(n, n);
		Eigen::VectorXd B(n);
		Eigen::VectorXd X(n);

		// solve for m_1,，，，,m_n
		A.setZero();
		B.setZero();
		A(0, 0) = 1;
		A(n - 1, n - 1) = 1;
		for (int i = 1; i <= n - 2; i++)
		{
			A(i, i - 1) = lambda[i + 1];
			A(i, i) = 2;
			A(i, i + 1) = miu[i + 1];
		}

		B(0) = fa_diff; // boundary condition for complete cubie spline
		B(n - 1) = fb_diff;
		for (int i = 1; i <= n - 2; i++)
		{
			B(i) = 3 * miu[i + 1] * fx_d1[i + 2] + 3 * lambda[i + 1] * fx_d1[i + 1]; // (3.3)
		}

		if (A.fullPivLu().isInvertible())
			X = A.fullPivLu().solve(B);
		else
			cout << "Matrix A is not invertible. The system may not have a unique solution.\n";

		m = new double[n + 1];
		for (int i = 1; i <= n; i++)
		{
			m[i] = X(i - 1);
		}

		// solve for M_1,，，，,M_n
		A.setZero();
		B.setZero();

		A(0, 0) = 2; A(0, 1) = 1;
		for (int i = 1; i <= n - 2; i++)
		{
			A(i, i - 1) = miu[i + 1];
			A(i, i) = 2;
			A(i, i + 1) = lambda[i + 1];
		}
		A(n - 1, n - 2) = 1; A(n - 1, n - 1) = 2;

		for (int i = 0; i <= n - 1; i++)
		{
			B(i) = 6 * fx_d2[i + 1];
		}

		if (A.fullPivLu().isInvertible())
			X = A.fullPivLu().solve(B);
		else
			cout << "Matrix A is not invertible. The system may not have a unique solution.\n";

		M = new double[n + 1];
		for (int i = 1; i <= n; i++)
		{
			M[i] = X(i - 1);
		}
	}
};

class specified_2d_cubic_spline :public cubic_spline
{
public:
	specified_2d_cubic_spline(int n, double* x, double* fx, double a, double b, 
		double fa_diff, double fb_diff,double fa_2_diff,double fb_2_diff)
		:cubic_spline(n, x, fx, a, b, fa_diff, fb_diff)
	{
		Eigen::MatrixXd A(n, n);
		Eigen::VectorXd B(n);
		Eigen::VectorXd X(n);

		// solve for M_1,，，，,M_n
		A.setZero();
		B.setZero();

		A(0, 0) = 1; A(n - 1, n - 1) = 1;
		for (int i = 1; i <= n - 2; i++)
		{
			A(i, i - 1) = miu[i + 1];
			A(i, i) = 2;
			A(i, i + 1) = lambda[i + 1];
		}

		B(0) = fa_2_diff; B(n - 1) = fb_2_diff;
		for (int i = 1; i <= n - 2; i++)
		{
			B(i) = 6 * fx_d2[i + 1];
		}

		if (A.fullPivLu().isInvertible())
			X = A.fullPivLu().solve(B);
		else
			cout << "Matrix A is not invertible. The system may not have a unique solution.\n";

		M = new double[n + 1];
		for (int i = 1; i <= n; i++)
		{
			M[i] = X(i - 1);
		}

		// solve for m_1,，，，,m_n
		A.setZero();
		B.setZero();
		A(0, 0) = -1; A(0, 1) = 1;
		A(n - 1, n - 2) = -1; A(n - 1, n - 1) = 1;
		for (int i = 1; i <= n - 2; i++)
		{
			A(i, i - 1) = lambda[i + 1];
			A(i, i) = 2;
			A(i, i + 1) = miu[i + 1];
		}

		B(0) = 0.5 * (M[2] + M[1]) * (x[2] - x[1]); // boundary condition for sepcified 2d cubic spline
		B(n - 1) = 0.5 * (M[n] + M[n - 1]) * (x[n] - x[n - 1]);
		for (int i = 1; i <= n - 2; i++)
		{
			B(i) = 3 * miu[i + 1] * fx_d1[i + 2] + 3 * lambda[i + 1] * fx_d1[i + 1]; // (3.3)
		}

		if (A.fullPivLu().isInvertible())
			X = A.fullPivLu().solve(B);
		else
			cout << "Matrix A is not invertible. The system may not have a unique solution.\n";

		m = new double[n + 1];
		for (int i = 1; i <= n; i++)
		{
			m[i] = X(i - 1);
		}
	}
};

class natural_cubic_spline :public specified_2d_cubic_spline
{
public:
	natural_cubic_spline(int n, double* x, double* fx, double a, double b, double fa_diff, double fb_diff)
		:specified_2d_cubic_spline(n, x, fx, a, b, fa_diff, fb_diff, 0, 0)
	{}
};
