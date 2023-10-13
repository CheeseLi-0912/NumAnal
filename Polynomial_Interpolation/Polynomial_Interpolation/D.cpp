// Hermite interpolation
#include "A.h"
#include "Hermite_Polynomial.h"

int main()
{
	const int N = 5;
	double time[N] = { 0, 3, 5, 8, 13 };
	double dis[N] = { 0, 225, 383, 623, 993 };
	double vel[N] = { 75, 77, 80, 74, 72 };
	double t = 10;

	Hermite_Interpolation a_position(time, dis, vel, N - 1, t);
	cout << a_position.solve() << endl;

	double delta = 0.00001;
	Hermite_Interpolation a_speed1(time, dis, vel, N - 1, t);
	Hermite_Interpolation a_speed2(time, dis, vel, N - 1, t+delta);
	double a_speed = (a_speed2.solve() - a_speed1.solve()) / delta;
	cout << a_speed << endl;

	bool flag = false;
	for (double t = 3; t <= 8; t = t + delta)
	{
		Hermite_Interpolation a_speed1(time, dis, vel, N - 1, t);
		Hermite_Interpolation a_speed2(time, dis, vel, N - 1, t + delta);
		a_speed = (a_speed2.solve() - a_speed1.solve()) / delta;
		if (a_speed > 81)
		{
			flag = true;
			break;
		}
	}
	cout << "Exceed: " << flag << endl;
	return 0;
}