#include "A.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
using namespace std;

const int N = 7;
double Day[N] = {0,6,10,13,17,20,28};
double Sp1[N] = {6.67,17.3,42.7,37.3,30.1,29.3,28.7};
double Sp2[N] = { 6.67,16.1,18.9,15.0,10.6,9.44,8.89 };

Newton_Formula _Sp1(Day, Sp1, N - 1);
Newton_Formula _Sp2(Day, Sp2, N - 1);

void data_file_1();
void data_file_2();

int main()
{
    /*
    * Assignment E(a)
    */
    data_file_1();
    data_file_2();

    // Define the Gnuplot script as a string
    std::ostringstream gnuplotScript;
    gnuplotScript << "set terminal wxt\n";
    gnuplotScript << "set title 'Assignment E(a)'\n";
    gnuplotScript << "plot \
        'output_E1.txt' with lines lw 2 title 'Sp1',\
        'output_E2.txt' with lines lw 2 title 'Sp2'\n";

    // Create a temporary Gnuplot script file
    std::ofstream scriptFile("temp_plot_data_files.plt");
    scriptFile << gnuplotScript.str();
    scriptFile.close();

    // Use Gnuplot to execute the script
    system("gnuplot -persist temp_plot_data_files.plt");

    /*
    * Assignment E(b)
    */
    double t = 28 + 15;

    cout << "Weights of two samples after another 15 days: " << endl;
    cout << _Sp1.solve(t) << endl;
    cout << _Sp2.solve(t) << endl;
    cout << "They are both too heavy, which means they have died from the high amount of tannin." << endl;

    return 0;
}

void data_file_1()
{
    ofstream outputFile("output_E1.txt");
    if (!outputFile.is_open()) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    for (double t = 0; t <= 28; t = t + 0.1)
    {
        outputFile << t << " " << _Sp1.solve(t) << endl;
    }

    outputFile.close();
}

void data_file_2()
{
    ofstream outputFile("output_E2.txt");
    if (!outputFile.is_open()) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    for (double t = 0; t <= 28; t = t + 0.1)
    {
        outputFile << t << " " << _Sp2.solve(t) << endl;
    }

    outputFile.close();
}