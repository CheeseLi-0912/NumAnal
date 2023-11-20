#include "pp_spline.h"
#define PI 3.1415926535
const double epi = 1e-2; // for derivative calculation

double f_x(double u)
{
	return sqrt(3) * cos(u);
}
double f_y(double u)
{
	return 2.0 / 3 * (sqrt(abs(sqrt(3) * cos(u))) - sqrt(3) * sin(u));
}

int n;
double u[NUM_MAX];
double x[NUM_MAX];
double y[NUM_MAX];
double a = PI / 2;
double b = 3 * PI / 2;
double fa_diff_x, fb_diff_x;
double fa_diff_y, fb_diff_y;

void interpolate(int n, string file_name);

int main()
{
	fa_diff_x = (f_x(a + epi) - f_x(a)) / epi;
	fb_diff_x = (f_x(b) - f_x(b - epi)) / epi;
	fa_diff_y = (f_y(a + epi) - f_y(a)) / epi; // fa_diff_y and fb_diff_y is infinite actually
	fb_diff_y = (f_y(b) - f_y(b - epi)) / epi;

	n = 10 / 2 + 1;
	interpolate(n, "E1.txt");
	n = 40 / 2 + 1;
	interpolate(n, "E2.txt");
	n = 160 / 2 + 1;
	interpolate(n, "E3.txt");

	// Define the Gnuplot script as a string
	std::ostringstream gnuplotScript;
	gnuplotScript << "set terminal wxt\n";
	gnuplotScript << "set title 'Assignment E'\n";
	gnuplotScript << "plot \
		'output_E1.txt' with lines lw 1 title 'n=10',\
        'output_E2.txt' with lines lw 1 title 'n=40',\
		'output_E3.txt' with lines lw 1 title 'n=160',\n";

	// Create a temporary Gnuplot script file
	std::ofstream scriptFile("temp_plot_data_files.plt");
	scriptFile << gnuplotScript.str();
	scriptFile.close();

	// Use Gnuplot to execute the script
	system("gnuplot -persist temp_plot_data_files.plt");

	return 0;
}


void interpolate(int n,string file_name)
{
	ofstream outputFile(file_name);
	if (!outputFile.is_open()) {
		cerr << "Failed to open the output file." << endl;
		return;
	}

	for (int i = 1; i <= n; i++) // knots on left of y axis
	{
		u[i] = a + (i - 1) * (b - a) / (n - 1);
		x[i] = f_x(u[i]);
		y[i] = f_y(u[i]);
	}

	natural_cubic_spline E_x(n, u, x, a, b, fa_diff_x, fb_diff_x);
	natural_cubic_spline E_y(n, u, y, a, b, fa_diff_y, fb_diff_y);

	for (double t = a; t <= b; t = t + MIN_PICK)
	{
		outputFile << E_x.solve(t) << " " << E_y.solve(t) << endl;
	}

	for (double t = a; t <= b; t = t + MIN_PICK)
	{
		outputFile << -E_x.solve(t) << " " << E_y.solve(t) << endl;
	}
	outputFile.close();
}