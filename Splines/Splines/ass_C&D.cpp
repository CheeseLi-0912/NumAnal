#include "B_spline.h"

double f(double x)
{
	return 1.0 / (1 + pow(x, 2));
}

double f_d1(double x)
{
	return -2.0 * x / pow(1 + pow(x, 2), 2);
}

int n = 11;
double x[NUM_MAX];
double fx[NUM_MAX];
double a = -5;
double b = 5;
string file;
string i_to_s;

int main()
{
	// cubic
	i_to_s = to_string(1);
	file = "C" + i_to_s + ".txt";

	for (int i = 1; i <= n; i++) // knots on [-5,5]
	{
		x[i] = a + (b - a) * (i - 1) / (n - 1);
	}
	for (int i = 1; i <= n; i++)
	{
		fx[i] = f(x[i]);
	}

	cubic_cardinal_B_spline s1(n, x, fx, a, b, f_d1(a), f_d1(b));
	s1.interpolate_for_graph(a, b, file);

	// quadratic
	i_to_s = to_string(2);
	file = "C" + i_to_s + ".txt";

	for (int i = 1; i <= n - 1; i++) // knots on [-5,5]
	{
		x[i] = a + (b - a) * (i - 1) / (n - 1) + 0.5;
	}
	for (int i = 1; i <= n - 1; i++)
	{
		fx[i] = f(x[i]);
	}
		
	quadratic_cardinal_B_spline s2(n, x, fx, a, b, f(a), f(b));
	s2.interpolate_for_graph(a, b, file);

	// Define the Gnuplot script as a string
	std::ostringstream gnuplotScript;
	gnuplotScript << "set terminal wxt\n";
	gnuplotScript << "set title 'Assignment C'\n";
	gnuplotScript << "plot \
        'C1.txt' with lines lw 1 title 'cubic',\
        'C2.txt' with lines lw 1 title 'quadratic',\
           1/(1+x*x) with points pointtype 3 pointsize 0.5 title 'f(x)'\n";

	// Create a temporary Gnuplot script file
	std::ofstream scriptFile("temp_plot_data_files.plt");
	scriptFile << gnuplotScript.str();
	scriptFile.close();

	// Use Gnuplot to execute the script
	system("gnuplot -persist temp_plot_data_files.plt");

	// Assignment D
	double sites[7] = { -3.5,-3,-0.5,0,0.5,3,3.5 };

	cout << "Error for cubic cardinal B spline:" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "x = " << sites[i] << ":" << endl;
		cout << abs(f(sites[i]) - s1.solve(sites[i])) << endl;
	}
	cout << endl;
	cout << "Error for quadratic cardinal B spline:" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "x = " << sites[i] << ":" << endl;
		cout << abs(f(sites[i]) - s2.solve(sites[i])) << endl;
	}

	return 0;
}