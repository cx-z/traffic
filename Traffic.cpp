// Traffic.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include"Car.h"
#include"Crossroad.h"
#include<vector>

void wait(Car &car, Crossroad &crossroad) {
	car.x_speed = 0;
	car.y_speed = 0;
}

bool toyota_run(Car &car) {
	cout << car.x << "," << car.y << endl;
	if (car.x < x_bound && car.y < y_bound) {
		if (car.x%unit_street == 0 && car.y%unit_street == 0) {
			if (crossroads[car.x%unit_street][car.y%unit_street].M_light) { //如果南北向是绿灯，向北走
				car.steer("North");
				car.straight();
			}
			else if (car.up=="North" || crossroads[car.x%unit_street][car.y%unit_street].W_light) { //如果东西向是绿灯，向东走
				car.steer("East");
				car.straight();
			}
			else { //如果南北向与东西向都是红灯，等待
				wait(car, crossroads[car.x%unit_street][car.y%unit_street]);
			}
		}
		else {
			car.straight();
		}
	}
	else if (car.x == x_bound && car.y < y_bound) {
		car.steer("North"); //在右边界方向始终为朝北
		if (car.y%unit_street == 0) { //在路口
			if (crossroads[car.x%unit_street][car.y%unit_street].M_light) { //如果南北向是绿灯，向北走
				car.straight();
			}
			else { //其余情况都等待
				wait(car, crossroads[car.x%unit_street][car.y%unit_street]);
			}
		}
		else {
			car.straight();
		}
	}
	else if (car.x < x_bound && car.y == y_bound) {
		car.steer("East"); //在上边界方向始终朝东
		if (car.x%unit_street == 0) { //在路口
			if (crossroads[car.x%unit_street][car.y%unit_street].W_light) { //如果东西向是绿灯，向东走
				car.straight();
			}
			else { //其余情况都等待
				wait(car, crossroads[car.x%unit_street][car.y%unit_street]);
			}
		}
		else {
			car.straight();
		}
	}
	else if (car.x == x_bound && car.y == y_bound) {
		cout << "测试汽车到达终点" << endl;
		return true;
	}
	else {
		cout << "测试汽车出界，请检查代码。" << endl;
		return true;
	}
	return false;
}

int main()
{
	init_crossroad();
	bool flag = false;
	for (int i = 0; i < 100; i++) {
		for (int m = 0; m <= x_bound % unit_street; m++) {
			for (int n = 0; n <= y_bound % unit_street; n++) {
				crossroads[m][n].blink();
			}
		}
		flag = toyota_run(toyota);
		if (flag) {
			cout << "耗时" << i << "个单位时间。" << endl;
			break;
		}
	}
}
