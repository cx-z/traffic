// Traffic.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include"Car.h"
#include"Crossroad.h"
#include<vector>

void cross(Car &car, Crossroad &crossroad) {  //穿过十字路口
	if (car.up == "North") {
		if (crossroad.M_light) {
			car.steer("North");
		}
		else {
			car.steer("East");
			car.up == "East";
		}
	}
	if (car.up == "East") {
		if (crossroad.W_light) {
			car.steer("East");
		}
		else {
			car.steer("North");
			car.up == "North";
		}
	}
	car.straight();
}

void Troad(Car &car, Crossroad &crossroad) { //穿过T字路口
	if (car.up == "North" and car.x == x_bound) { //在右边界
		if (crossroad.M_light) {  //如果是绿灯，直行
			car.steer("North");
			crossroad.S_road = {}; //排队车辆清空
		}
		else { //如果是红灯，排队等待
			car.y_speed = 0;
			crossroad.S_road.push_back(car);
		}
	}
	else if (car.up == "North" && car.x == 0) { //在左边界
		if (crossroad.M_light) {
			car.steer("North");
			crossroad.S_road = {}; //排队车辆清空
		}
		else { //如果是红灯，右转
			car.steer("East");
		}
	}
	else if (car.up == "East" && car.y == y_bound) { //在上边界
		if (crossroad.W_light) { //如果是绿灯，直行
			car.steer("East");
			crossroad.W_road = {}; //排队车辆清空
		}
		else { //如果是红灯，排队等待
			car.x_speed = 0;
			crossroad.W_road.push_back(car);
		}
	}
	else if (car.up == "East" && car.y == 0) { //在下边界
		if (crossroad.W_light) {
			car.steer("East");
			crossroad.W_road = {}; //排队车辆清空
		}
		else { //如果是红灯，排队等待
			car.steer("North");
			car.straight();
		}
	}
	car.straight();
}

bool run(Car &car) {
	if (car.x == 0) { //汽车在左边界
		if (car.y%unit_street == 0 && car.y != y_bound && car.y != 0) {
			Troad(car, crossroads[car.x%unit_street][car.y%unit_street]);
			//cout << "xspeed,yspeed" << car.x_speed << "," << car.y_speed << endl;
		}
		else if (car.y%unit_street == 0 && car.y == y_bound) { //到达左上角，右拐
			car.steer("East");
			car.straight();
		}
		else {
			car.straight();
			//cout << "xspeed,yspeed" << car.x_speed << "," << car.y_speed << endl;
		}
	}
	else if (car.y == 0) { //汽车在下边界
		if (car.x%unit_street == 0 && car.x != x_bound) {
			Troad(car, crossroads[car.x%unit_street][car.y%unit_street]);
			//cout << "xspeed,yspeed" << car.x_speed << "," << car.y_speed << endl;
		}
		else if (car.x == x_bound) { //到达右下角，左拐
			car.steer("East");
			car.straight();
		}
		else {
			car.straight();
			//cout << "xspeed,yspeed" << car.x_speed << "," << car.y_speed << endl;
		}
	}
	else if (car.x < x_bound && car.y != 0 && car.y < y_bound) {
		if (car.x%unit_street == 0 && car.y%unit_street == 0) {
			cross(car, crossroads[car.x%unit_street][car.y%unit_street]);
			//cout << "xspeed,yspeed" << car.x_speed << "," << car.y_speed << endl;
		}
		else {
			car.straight();
			//cout << "xspeed,yspeed" << car.x_speed << "," << car.y_speed << endl;
		}
	}
	else if (car.x == x_bound && car.y < y_bound) {
		if (car.y%unit_street == 0) {
			Troad(car, crossroads[car.x%unit_street][car.y%unit_street]);
		}
		else {
			car.straight();
		}
	}
	else if (car.x < x_bound && car.y == y_bound) {
		if (car.x%unit_street == 0) {
			Troad(car, crossroads[car.x%unit_street][car.y%unit_street]);
		}
		else {
			car.straight();
		}
	}
	else if (car.x == x_bound && car.y == y_bound) {
		car.x_speed = 0;
		car.y_speed = 0;
		cout << "测试汽车已到达终点" << endl;
		return true;
	}
	else {
		cout << "测试汽车出界，请检查代码" << endl;
		return true;
	}
	return false;
}

int main()
{
	init_crossroad();
	bool flag = false;
	for (int i = 0; i < 41; i++) {
		flag = run(toyota);
		if (flag) break;
	}
}
