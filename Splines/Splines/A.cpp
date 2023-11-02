#include "pp_spline.h"

class spline :public complete_cubic_spline
{
public:
	virtual double function(double x)
	{
		return 1.0 / (1 + 25 * x * x);
	}

	virtual double function_d1(double x)
	{
		return -50.0 * x / pow(1 + 25 * x * x, 2);
	}

	spline(double* x, int n) :complete_cubic_spline(x, n)
	{}
};

int main()
{
	int n = 6;
	double x[N];
	//x[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		x[i] = -1 + 2.0 * (i - 1) / (n-1);
	}
	complete_cubic_spline s1(x, n);

	cout << s1.solve(0.99) << endl;
	return 0;
}