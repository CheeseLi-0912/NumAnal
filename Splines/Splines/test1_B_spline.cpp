#include "B_spline.h"

double f(double x)
{
	return 1.0/(1+x*x);
}

int n;
int d;
double x[NUM_MAX];
double fx[NUM_MAX];
double a = -5;
double b = 5;

int main()
{
	n = 11;
	d = 3;

	for (int i = 1; i <= n; i++)
	{
		x[i] = a + (b - a) * (i - 1) / (n - 1);
	}
	for (int i = 1; i <= n; i++)
	{
		fx[i] = f(x[i]);
	}

	B_spline s1(n, d, x, fx, a, b);
	s1.interpolate_for_graph("test1_B_spline1.txt");

	n = 21;
	d = 3;

	for (int i = 1; i <= n; i++)
	{
		x[i] = a + (b - a) * (i - 1) / (n - 1);
	}
	for (int i = 1; i <= n; i++)
	{
		fx[i] = f(x[i]);
	}

	B_spline s2(n, d, x, fx, a, b);
	s2.interpolate_for_graph("test1_B_spline2.txt");

	n = 41;
	d = 3;

	for (int i = 1; i <= n; i++)
	{
		x[i] = a + (b - a) * (i - 1) / (n - 1);
	}
	for (int i = 1; i <= n; i++)
	{
		fx[i] = f(x[i]);
	}

	B_spline s3(n, d, x, fx, a, b);
	s3.interpolate_for_graph("test1_B_spline3.txt");

	// Define the Gnuplot script as a string
	std::ostringstream gnuplotScript;
	gnuplotScript << "set terminal wxt\n";
	gnuplotScript << "set title 'Test B Spline for varying n'\n";
	gnuplotScript << "plot \
        'test1_B_spline1.txt' with lines lw 1 title 'n=11, d=3',\
		'test1_B_spline2.txt' with lines lw 1 title 'n=21, d=3',\
		'test1_B_spline3.txt' with lines lw 1 title 'n=41, d=3',\
           1/(1+x*x) with points pointtype 3 pointsize 0.5 title 'f(x)'\n";

	// Create a temporary Gnuplot script file
	std::ofstream scriptFile("temp_plot_data_files.plt");
	scriptFile << gnuplotScript.str();
	scriptFile.close();

	// Use Gnuplot to execute the script
	system("gnuplot -persist temp_plot_data_files.plt");

	
	return 0;
}