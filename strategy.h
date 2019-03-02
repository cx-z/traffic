#pragma once
#include"Car.h"
#include"Crossroad.h"
#include<iostream>
#include<queue>

using namespace std;

void join_line(Car &car, Crossroad &cross) {
	car.wait_flag = true;
	car.release_flag = false;
	if (car.up == "North") {
		cross.S_road.push(car);
		car.serial_num = cross.S_road.size();
	}
	else if (car.up == "South") {
		cross.N_road.push(car);
		car.serial_num = cross.N_road.size();
	}
	else if (car.up == "East") {
		cross.W_road.push(car);
		car.serial_num = cross.W_road.size();
	}
	else {
		cross.E_road.push(car);
		car.serial_num = cross.E_road.size();
	}
	/*if (car.id == 0) {
		cout << "排在第" << car.serial_num << "位" << endl;
	}*/
}

void strategy1(Car &car) {
	Crossroad &cross = crossroads[car.x / x_unit][car.y / y_unit];
	//cout << "南北灯" << cross.M_light << "\t" << "东西灯" << cross.W_light << endl;
	if (cross.M_light && car.up == "North") {
		if (cross.y != y_bound && (!cross.S_road.size() || car.release_flag)) {
			car.steer("North");
			car.straight();
		}
		else {
			car.steer("East");
			car.straight();
		}
	}
	else if (cross.W_light && car.up == "East" && (!cross.W_road.size() || car.release_flag)) {
		if (cross.y != y_bound) {
			car.steer("North");
			car.straight();
		}
		else {
			car.steer("East");
			car.straight();
		}
	}
	else if (!cross.M_light && car.up == "North") {
		if (cross.x != x_bound) {
			car.steer("East");
			car.straight();
		}
	}
	else {
		join_line(car, cross);
	}
}

void navigate(Car &car, int p, int q) {
	if (car.x == x_bound) { car.next_up = "North"; }
	else if (car.y == y_bound) { car.next_up = "East"; }
	else {
		int M_flag = 6 - (crossroads[p][q + 1].light_flag + y_unit) % 13;
		int W_flag = 6 - (crossroads[p + 1][q].light_flag + x_unit) % 13;
		if (W_flag <= 0 && M_flag < 0) {
			car.next_up = "East";
		}
		else {
			car.next_up = "North";
		}
	}
	car.steer(car.next_up);
	car.straight();
}

void strategy2(Car &car) {
	int a = car.x / x_unit;
	int b = car.y / y_unit;
	//cout << "南北灯" << crossroads[a][b].M_light << "\t" << "东西灯" << crossroads[a][b].W_light << endl;
	if (crossroads[a][b].M_light && car.up == "North" && (!crossroads[a][b].S_road.size() || car.release_flag)) {
		if (crossroads[a][b].y != y_bound) {
			navigate(car, a, b);
		}
		else {
			car.steer("East");
			car.straight();
		}
	}
	else if (crossroads[a][b].W_light && car.up == "East" && (!crossroads[a][b].W_road.size() || car.release_flag)) {
		if (crossroads[a][b].x != x_bound) {
			navigate(car, a, b);
		}
		else {
			car.steer("North");
			car.straight();
		}
	}
	else if (!crossroads[a][b].M_light && car.up == "North" && (!crossroads[a][b].S_road.size() || car.release_flag)) {
		if (crossroads[a][b].x != x_bound) {
			car.steer("East");
			car.straight();
		}
	}
	else {
		join_line(car, crossroads[a][b]);
	}
}

bool toyota_run1(Car &car) {
	if (car.x == x_bound && car.y == y_bound) {
		return true;
	}
	else if (car.x > x_bound || car.x<0 || car.y>y_bound || car.y < 0) {
		cout << "测试汽车出界，请检查代码" << endl;
		return true;
	}
	else if (car.x%x_unit == 0 && car.y%y_unit == 0) {
		strategy1(car);
	}
	else {
		car.straight();
	}
	return false;
}

bool toyota_run2(Car &car) {
	if (car.x == x_bound && car.y == y_bound) {
		return true;
	}
	else if (car.x > x_bound || car.x<0 || car.y>y_bound || car.y < 0) {
		cout << "测试汽车出界，请检查代码" << endl;
		return true;
	}
	else if (car.x%x_unit == 0 && car.y%y_unit == 0) {
		strategy2(car);
	}
	else {
		car.straight();
	}
	return false;
}
