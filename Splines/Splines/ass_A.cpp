#include "pp_spline.h"

double f(double x)
{
	return 1.0 / (1 + 25 * x * x);
}

double f_d1(double x)
{
	return -50.0 * x / pow(1 + 25 * x * x, 2);
}

int n;
double x[NUM_MAX];
double fx[NUM_MAX];
double a = -1; // given by json file ?
double b = 1; // given by json file ?
double fa_diff = f_d1(a);
double fb_diff = f_d1(b);
double mid_point;
double max_error;
string file_name;
string i_to_s;

int main()
{
	//// Read the JSON file
	//ifstream file("A_input.json");
	//if (!file.is_open()) {
	//	cerr << "Error opening file." << endl;
	//	return 1;
	//}

	//// Read the content of the file into a string
	//string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));

	//// Parse the JSON content
	//string err;
	//auto json = json11::Json::parse(content, err);

	//// Check for parsing errors
	//if (!err.empty()) {
	//	cerr << "Error parsing JSON: " << err << endl;
	//	return 1;
	//}

	//// Access parameters from the JSON object
	//a = json["a"].int_value();
	//b = json["b"].int_value();

	//// above is input by json file

	for (int i = 1; i <= 5; i++)
	{
		i_to_s = to_string(i);
		file_name = "A" + i_to_s + ".txt";

		n = 5 * pow(2, i-1) + 1;

		for (int i = 1; i <= n; i++) // knots on [-1,1]
		{
			x[i] = a + (b - a) * (i - 1) / (n - 1);
		}
		for (int i = 1; i <= n; i++)
		{
			fx[i] = f(x[i]);
		}

		complete_cubic_spline s(n, x, fx, a, b, fa_diff, fb_diff);
		s.interpolate_for_graph(file_name);

		max_error = 0;
		for (int i = 1; i <= n - 1; i++)
		{
			mid_point = 0.5 * (x[i] + x[i + 1]);
			max_error = max(max_error, s.solve(mid_point) - f(mid_point));
		}
		cout << "max error of n=" << n << ": " << max_error << endl;
	}

	// Define the Gnuplot script as a string
	std::ostringstream gnuplotScript;
	gnuplotScript << "set terminal wxt\n";
	gnuplotScript << "set title 'Assignment A'\n";
	gnuplotScript << "plot \
        'A1.txt' with lines lw 1 title 'n=6',\
        'A2.txt' with lines lw 1 title 'n=11',\
        'A3.txt' with lines lw 1 title 'n=21',\
        'A4.txt' with lines lw 1 title 'n=41',\
		'A5.txt' with lines lw 1 title 'n=81',\
           1/(1+25*x*x) with points pointtype 3 pointsize 0.5 title 'f(x)'\n";

	// Create a temporary Gnuplot script file
	std::ofstream scriptFile("temp_plot_data_files.plt");
	scriptFile << gnuplotScript.str();
	scriptFile.close();

	// Use Gnuplot to execute the script
	system("gnuplot -persist temp_plot_data_files.plt");

	return 0;
}