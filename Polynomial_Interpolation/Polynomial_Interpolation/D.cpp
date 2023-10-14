#include "Hermite_Polynomial.h"
#include <iostream>
using namespace std;

int main()
{
	const int N = 5;
	double time[N] = { 0, 3, 5, 8, 13 };
	double dis[N] = { 0, 225, 383, 623, 993 };
	double vel[N] = { 75, 77, 80, 74, 72 };
	double t = 10;

	Hermite_Interpolation a_position(time, dis, vel, N - 1);
	cout << "t=10 position: " << a_position.solve(t) << endl;

	double delta = 0.00001;
	Hermite_Interpolation a_speed(time, dis, vel, N - 1);
	double _a_speed = (a_speed.solve(t+delta) - a_speed.solve(t)) / delta;
	cout << "t=10 speed: " << _a_speed << endl;

	bool flag = false;
	for (double t = 3; t <= 8; t = t + delta)
	{
		_a_speed = (a_speed.solve(t + delta) - a_speed.solve(t)) / delta;
		if (_a_speed > 81)
		{
			flag = true;
			break;
		}
	}
	cout << "Exceed 81: ";
	if (flag) cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}