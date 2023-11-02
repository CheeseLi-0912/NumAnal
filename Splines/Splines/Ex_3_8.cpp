#include "pp_spline.h"

class spline :public complete_cubic_spline
{
public:
	virtual double function(double x)
	{
		return log(x);
	}

	virtual double function_d1(double x)
	{
		return 1.0 / x;
	}

	spline(double* x, int n):complete_cubic_spline(x, n)
	{}
};

int main()
{
	//complete_cubic_spline *s;
	int n = 4;
	double x[5] = {0,1,2,3,7}; // the first 0 is to occupy an index
	complete_cubic_spline s1(x, n);
	//s = &s1;
	cout << s1.solve(5) << endl;
	return 0;
}