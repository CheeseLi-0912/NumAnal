#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <Eigen/Dense>
using namespace std;
const double MIN_PICK = 1e-2; // distance of two neighbor points in interpolate_for_graph
const int NUM_MAX = 10000; // the max capability for interpolated knots

//enum SplineType {
//	ppForm,
//	BForm,
//	cardinalB
//};
//template < int Dim, int Order, SplineType t >

class spline
{
public:

	int n; // the number of knots
	double* x; // the list of knots' values
	double* fx; // the list of functioned knots' values
	double a; // left end-points of the whole interval
	double b; // right end-points of the whole interval

	virtual double solve(double t) = 0; // get the value of spline(t)

	spline(int n, double* x, double* fx, double a, double b)
	{
		this->n = n;
		this->x = x;
		this->fx = fx;
		this->a = a;
		this->b = b;		
	}

	void interpolate_for_graph(double a, double b, string file_name)
		// generate data for graph in txt file
	{
		ofstream outputFile(file_name);
		if (!outputFile.is_open()) {
			cerr << "Failed to open the output file." << endl;
			return;
		}

		for (double t = a; t <= b; t = t + MIN_PICK)
		{
			outputFile << t << " " << solve(t) << endl;
		}
		outputFile.close();
	}
};
