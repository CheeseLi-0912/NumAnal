// Hermite interpolation

class Hermite
{
private:

	double* x; // interpolated value, carried by pointer
	double* fx; // func to interpolated value, carried by pointer
	double* fx_d1; // func'd to interpolated value, carried by pointer
	int n; // the numbers are x_0 to x_n
	double t; //given value, aiming to get f(t)

	int* index; // transfer 0,1,，，，,n to 0,0,1,1,，，，,n,n

public:

	Hermite(double* x, double* fx, double* fx_d1, int n) // n+1 numbers, 2n+2 restrictions
	{
		this->x = x;
		this->fx = fx;
		this->fx_d1 = fx_d1;
		this->n = n;

		index = new int[2 * n + 2];
		for (int i = 0; i <= n; i++)
		{
			index[2 * i] = i;
			index[2 * i + 1] = i;
		}	
	}

	~Hermite()
	{
		delete[] index;
	}

	double pai(int k)
	{
		double res = 1;
		for (int i = 0; i <= k - 1; i++)
		{
			res *= (t - x[index[i]]);
		}
		return res;
	}

	double a(int* index, int n) // divided difference of n numbers
	{
		if (n == 1)
			return fx[*index];
		else if (n == 2 && *index == *(index + 1))
			return fx_d1[*index];
		else
			return (a(index + 1, n - 1) - a(index, n - 1)) / (x[*(index + n - 1)] - x[*index]);
	}

	double solve(double t_0)
	{
		t = t_0;
		double res = 0;
		for (int k = 0; k <= 2 * n + 1; k++)
		{
			res += a(index, k + 1) * pai(k);
		}
		return res;
	}
};