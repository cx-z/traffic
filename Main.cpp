// Traffic.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include"Simulation.h"
#include<time.h>
#include<fstream>
#include<Windows.h>

int main()
{
	srand((unsigned int)(time(NULL)));
	int num1 = 0;
	int num2 = 0;
	ofstream ofile;
	ofile.open("data.txt");
	for (int k = 0; k < 100; k++) {
		DWORD start = GetTickCount();
		int temp = Simulation1();
		DWORD end = GetTickCount();
		DWORD time = end - start;
		cout << "用时" << time/1000 << "秒" << endl;
		num1 += temp;
		ofile << temp << "\t";
		if ((k + 1) % 10 == 0) ofile << endl;
	}
		
	/*ofile << "----------------------------" << endl;
	for (int k = 0; k < 10; k++) {
		//DWORD start = GetTickCount();
		int temp = Simulation2();
		//DWORD end = GetTickCount();
		//DWORD time = end - start;
		//cout << "用时" << time/1000 << "秒" << endl;
		num2 += temp;
		ofile << temp << "\t";
		if ((k + 1) % 10 == 0) ofile << endl;
	}
	ofile << "----------------------------" << endl;*/
	cout << "策略1平均用时" << num1 / 100 << endl;
	//cout << "策略2平均用时" << num2 / 10 << endl;
}
