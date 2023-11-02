#include <iostream>
#include <Eigen/Dense>
using namespace std;

int main()
{
	int n = 2;
	Eigen::MatrixXd A(n, n);
	A(0, 0) = 1; A(0, 1) = 1; A(1, 0) = 2; A(1, 1) = 3;
	cout << A << endl;
	return 0;
}