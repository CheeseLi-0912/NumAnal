//#include "A.h"
#include <fstream>
#include <string>
#include <stdio.h>
//class B :public Newton_Formula
//{
//public:
//	virtual double f(double x)
//	{
//		return 1.0 / (1 + x * x);
//	}
//
//	B(double* x, int n, double t) :Newton_Formula(x, n, t)
//	{}
//
//};

int main()
{
	//Newton_Formula* s;
	//double x[4] = { 0, 1, 2, 3 };
	//B1 b1(x, 3, 1.5);

	//s = &b1;
	//cout << s->solve() << endl;
	// 
	//plot

	FILE* pipe = _popen("gnuplot", "w"); /* �Կ�д��ʽ��gnuplot�նˣ����pipeΪ����˵����ʧ�ܣ���������Ϊδ��gnuplot������PATH���������� */
	fprintf(pipe, "plot sin(x)\n"); /* ��gnuplot�Ļ�ͼ����������ܵ��У�������Ҫ�Ի��з����� */
	fprintf(pipe, "pause mouse\n"); /* ʹ�ô���������û�ͼ����ͣ��������Ϊ�ȴ��û��������رմ��� */
	_pclose(pipe); /* �ر�pipe�ܵ���gnuplot�˳� */

	return 0;
}