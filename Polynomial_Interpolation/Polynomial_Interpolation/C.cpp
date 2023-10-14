#include "A.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#define PI 3.141592654

using namespace std;

const int N = 20;
double x[N] = {};
double fx[N] = {};
int n;

void data_file_1();
void data_file_2();
void data_file_3();
void data_file_4();

int main()
{
    //export data when n=5,10,15,20, for later graph
    data_file_1();
    data_file_2();
    data_file_3();
    data_file_4();

    // Define the Gnuplot script as a string
    std::ostringstream gnuplotScript;
    gnuplotScript << "set terminal wxt\n";
    gnuplotScript << "set title 'Assignment C'\n";
    gnuplotScript << "plot \
        'output_C1.txt' with lines lw 2 title 'n=5',\
        'output_C2.txt' with lines lw 2 title 'n=10',\
        'output_C3.txt' with lines lw 2 title 'n=15',\
        'output_C4.txt' with lines lw 2 title 'n=20',\
           1/(1+25*x*x) with points pointtype 3 pointsize 1 title 'f(x)'\n";

    // Create a temporary Gnuplot script file
    std::ofstream scriptFile("temp_plot_data_files.plt");
    scriptFile << gnuplotScript.str();
    scriptFile.close();

    // Use Gnuplot to execute the script
    system("gnuplot -persist temp_plot_data_files.plt");

    return 0;
}

void data_file_1()
{
    ofstream outputFile("output_C1.txt");
    if (!outputFile.is_open()) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    n = 5;

    for (int i = 1; i <= n; i++)
    {
        x[i-1] = cos((2 * i - 1) * PI / (2 * n));
        fx[i-1] = 1.0 / (1 + 25 * x[i-1] * x[i-1]);
    }

    Newton_Formula B(x, fx, n-1);

    for (double t = -1; t <= 1; t = t + 0.01)
    {
        outputFile << t << " " << B.solve(t) << endl;
    }

    outputFile.close();
}

void data_file_2()
{
    ofstream outputFile("output_C2.txt");
    if (!outputFile.is_open()) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    n = 10;

    for (int i = 1; i <= n; i++)
    {
        x[i - 1] = cos((2 * i - 1) * PI / (2 * n));
        fx[i - 1] = 1.0 / (1 + 25 * x[i - 1] * x[i - 1]);
    }

    Newton_Formula B(x, fx, n - 1);

    for (double t = -1; t <= 1; t = t + 0.01)
    {
        outputFile << t << " " << B.solve(t) << endl;
    }

    outputFile.close();
}

void data_file_3()
{
    ofstream outputFile("output_C3.txt");
    if (!outputFile.is_open()) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    n = 15;

    for (int i = 1; i <= n; i++)
    {
        x[i - 1] = cos((2 * i - 1) * PI / (2 * n));
        fx[i - 1] = 1.0 / (1 + 25 * x[i - 1] * x[i - 1]);
    }

    Newton_Formula B(x, fx, n - 1);

    for (double t = -1; t <= 1; t = t + 0.01)
    {
        outputFile << t << " " << B.solve(t) << endl;
    }

    outputFile.close();
}

void data_file_4()
{
    ofstream outputFile("output_C4.txt");
    if (!outputFile.is_open()) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    n = 20;

    for (int i = 1; i <= n; i++)
    {
        x[i - 1] = cos((2 * i - 1) * PI / (2 * n));
        fx[i - 1] = 1.0 / (1 + 25 * x[i - 1] * x[i - 1]);
    }

    Newton_Formula B(x, fx, n - 1);

    for (double t = -1; t <= 1; t = t + 0.01)
    {
        outputFile << t << " " << B.solve(t) << endl;
    }

    outputFile.close();
}