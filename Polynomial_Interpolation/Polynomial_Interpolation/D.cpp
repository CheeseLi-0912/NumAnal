#include "Hermite_Polynomial.h"

int main()
{
	double time[5] = { 0, 3, 5, 8, 13 };
	double dis[5] = { 0, 225, 383, 623, 993 };
	double vel[5] = { 75, 77, 80, 74, 72 };
	double t = 10;

	Hermite_Interpolation a_position(time, dis, vel, 5, t);
	cout << a_position.solve() << endl;

	return 0;
}