#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, char* argv[])
{
	// 구구단 5단
	ofstream fout("Gugudan.txt");
	if (!fout)
	{
		cout << "Cannot open Gugudan file!" << endl;
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			fout << "5 * " << i + 1 << " = ";
			fout << (i + 1) * 5 << endl;
		}
	}
	fout.close();

	// 2의 n승
	fout.open("Power.txt");
	if (!fout)
	{
		cout << "Cannot open Power txt file!" << endl;
	}
	else
	{
		for (int n = 0; n < 11; n++)
		{
			fout << n << ", " << pow(2., (double)n) << endl;
		}
	}
	fout.close();

	// Sinwave
	fout.open("Sinwave.txt");
	if (!fout)
	{
		cout << "Cannot open Sinwave file!" << endl;
	}
	else
	{
		double A = 10000.;
		double f1 = 220., f2 = 330., f3 = 440., f4 = 600., fs = 44100.;
		double dt = 1. / fs;
		double PI = 3.14159265358979;
		for (double t=0; t<.01; t+=dt)
		{
			fout << t << ", "
				<< A * sin(2. * PI * f1 * t) << ', '
				<< A * sin(2. * PI * f2 * t) << ', '
				<< A * sin(2. * PI * f3 * t) << ', '
				<< A * sin(2. * PI * f4 * t) << endl;
		}
	}
	fout.close();
}