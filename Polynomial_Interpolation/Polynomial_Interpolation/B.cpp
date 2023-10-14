#include "A.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
using namespace std;

const int N = 9;
double x[N] = {};
double fx[N] = {};
int n;

void data_file_1();
void data_file_2();
void data_file_3();
void data_file_4();

int main()
{
    //export data when n=2,4,6,8, for later graph
    data_file_1();
    data_file_2();
    data_file_3();
    data_file_4();

    // Define the Gnuplot script as a string
    std::ostringstream gnuplotScript;
    gnuplotScript << "set terminal wxt\n";
    gnuplotScript << "set title 'Assignment B'\n";
    gnuplotScript << "plot \
        'output_B1.txt' with lines lw 2 title 'n=2',\
        'output_B2.txt' with lines lw 2 title 'n=4',\
        'output_B3.txt' with lines lw 2 title 'n=6',\
        'output_B4.txt' with lines lw 2 title 'n=8',\
             1/(1+x*x) with lines lw 5 title 'f(x)'\n";

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
    // Create an output file stream and open a file for writing
    ofstream outputFile("output_B1.txt");

    // Check if the file was successfully opened
    if (!outputFile.is_open()) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    // Data to export
    n = 2;

    for (int i = 0; i <= n; i++)
    {
        x[i] = -5 + 10.0 * i / n;
        fx[i] = 1.0 / (1 + x[i] * x[i]);
    }

    Newton_Formula B(x, fx, n);

    // Write the data to the file
    for (double t = -5; t <= 5; t = t + 0.1)
    {
        outputFile << t << " " << B.solve(t) << endl;
    }

    // Close the file
    outputFile.close();
}

void data_file_2()
{
    ofstream outputFile("output_B2.txt");

    if (!outputFile.is_open()) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    n = 4;

    for (int i = 0; i <= n; i++)
    {
        x[i] = -5 + 10.0 * i / n;
        fx[i] = 1.0 / (1 + x[i] * x[i]);
    }

    Newton_Formula B(x, fx, n);

    for (double t = -5; t <= 5; t = t + 0.1)
    {
        outputFile << t << " " << B.solve(t) << endl;
    }

    outputFile.close();
}

void data_file_3()
{
    ofstream outputFile("output_B3.txt");

    if (!outputFile.is_open()) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    n = 6;

    for (int i = 0; i <= n; i++)
    {
        x[i] = -5 + 10.0 * i / n;
        fx[i] = 1.0 / (1 + x[i] * x[i]);
    }

    Newton_Formula B(x, fx, n);

    for (double t = -5; t <= 5; t = t + 0.1)
    {
        outputFile << t << " " << B.solve(t) << endl;
    }

    outputFile.close();
}

void data_file_4()
{
    ofstream outputFile("output_B4.txt");

    if (!outputFile.is_open()) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    n = 8;

    for (int i = 0; i <= n; i++)
    {
        x[i] = -5 + 10.0 * i / n;
        fx[i] = 1.0 / (1 + x[i] * x[i]);
    }

    Newton_Formula B(x, fx, n);

    for (double t = -5; t <= 5; t = t + 0.1)
    {
        outputFile << t << " " << B.solve(t) << endl;
    }

    outputFile.close();
}