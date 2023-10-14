// Hermite interpolation

class Hermite_Interpolation
{
private:

	double* x; // interpolated value, carried by pointer
	double* fx; // func to interpolated value, carried by pointer
	double* fx_d1; // func'd to interpolated value, carried by pointer
	int n; // the numbers are x_0 to x_n
	double t; //given value, aiming to get f(t)

public:

	Hermite_Interpolation(double* x, double* fx, double* fx_d1, int n)
	{
		this->x = x;
		this->fx = fx;
		this->fx_d1 = fx_d1;
		this->n = n;
	}

	double solve(double t_0) // the algorithm is learned from CSDN, as Handbook's doesn't give directly
	{
		t = t_0;
		double res = 0;
		for (int i = 0; i <= n; i++)
		{
			double h = 1;
			double a = 0;
			for (int j = 0; j <= n; j++)
			{
				if (i != j)
				{
					h = h * ((t - x[j]) * (t - x[j])) * 1.0 / ((x[i] - x[j]) * (x[i] - x[j]));
					a = a + 1.0 / (x[i] - x[j]);
				}
			}
			res = res + h * ((x[i] - t) * (2 * a * fx[i] - fx_d1[i]) + fx[i]);
		}
		return res;
	}
};

