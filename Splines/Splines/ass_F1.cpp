#include "Spline.h"

int n;
int i;

double Basis(double x, int n)
{
	if (x >= 0)
		return pow(x, n);
	else
		return 0;
}

double dd(double* t, int n, int i, int N, double x) // divided difference of t[i],t[i+1],¡¤¡¤¡¤,t[i+N-1]
{
	if (N == 1)
		return Basis(t[i] - x, n);
	else
		return (dd(t, n, i + 1, N - 1, x) - dd(t, n, i, N - 1, x)) / (t[i + N - 1] - t[i]);
}


double TPF(double* t, int n, int i, int N, double x) // truncated power function
{
	return (t[i + n] - t[i - 1]) * dd(t, n, i - 1, N, x);
}

void interpolate_for_graph(string file_name, double* t, int n, int i, int N)
// generate data for graph in txt file
{
	ofstream outputFile(file_name);
	if (!outputFile.is_open()) {
		cerr << "Failed to open the output file." << endl;
		return;
	}

	for (double x = t[0]; x <= t[n+2]; x = x + MIN_PICK)
	{
		outputFile << x << " " << TPF(t,n,i,N,x) << endl;
	}
	outputFile.close();
}

int main()
{
	n = 1;

	double t1[NUM_MAX] = {}; // there should be 2n+4 elements
	for (int i = 0; i <= 2*n+3; i++)
		t1[i] = i;

	string file_name;
	string title;
	for (int N = 1; N <= n + 2; N++)
	{
		for (int i = 1; i <= n+3-N; i++)
		{
			string file_name = "F_" + to_string(i+N-1) + to_string(N) + to_string(n) + ".txt";
			interpolate_for_graph(file_name, t1, n, i+1, N);

			//title = "Figure [" + to_string(i) + "," + to_string(N) + "] in DDT of n=" + to_string(n);	
		}
	}

	// Define the Gnuplot script as a string
	std::ostringstream gnuplotScript;
	gnuplotScript << "set terminal wxt\n";
	gnuplotScript << "set title ''\n";
	gnuplotScript << "plot \
			'F_111.txt' with lines lw 2 title '111'\n"; // change the file_name to graph all
			// In the file name, the first two numbers refer to the coordinate of graph in DDT;
			// the last number refers to n

		  //'F_211.txt' with lines lw 1 title '211',\
			'F_311.txt' with lines lw 1 title '311',\
			'F_221.txt' with lines lw 1 title '221',\
			'F_321.txt' with lines lw 1 title '321',\
			'F_331.txt' with lines lw 1 title '331'\n";

	// Create a temporary Gnuplot script file
	std::ofstream scriptFile("temp_plot_data_files.plt");
	scriptFile << gnuplotScript.str();
	scriptFile.close();

	// Use Gnuplot to execute the script
	system("gnuplot -persist temp_plot_data_files.plt");
	return 0;
}