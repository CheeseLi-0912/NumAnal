#include "A.h"
#include <fstream>
#include <string>

class B :public Newton_Formula
{
public:
	/*virtual double f(double x)
	{
		return 1.0 / (1 + x * x);
	}*/

	B(double* x, double* fx, int n, double t) :Newton_Formula(x, fx, n, t)
	{}

};

int main()
{
	Newton_Formula* s;
	double x[4] = { 0, 1, 2, 3 };
	B1 b1(x, 3, 1.5);

	s = &b1;
	cout << s->solve() << endl;
	 
	////plot

	//FILE* pipe = popen("gnuplot", "w"); /* 以可写方式打开gnuplot终端，如果pipe为空则说明打开失败，可能是因为未将gnuplot设置在PATH环境变量中 */
	//set xrange[-5:5];
	//fprintf(pipe, "plot 1.0/(1+x*x)\n"); /* 将gnuplot的画图命令输出到管道中，命令需要以换行符结束 */
	//fprintf(pipe, "pause mouse\n"); /* 使用此命令可以让画图窗口停留，作用为等待用户点击鼠标后关闭窗口 */
	//pclose(pipe); /* 关闭pipe管道，gnuplot退出 */

	return 0;
}