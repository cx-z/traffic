#pragma once
#include"Crossroad.h"
#include"Car.h"
#include"strategy.h"
#include<iostream>
#include<queue>
#include<math.h>

void init_toyota() {
	cars[0].x = 0;
	cars[0].y = 0;
	cars[0].x_speed = 1;
	cars[0].y_speed = 0;
	cars[0].up = "East";
	cars[0].next_up = "East";
	cars[0].wait_flag = false;
	cars[0].release_flag = false;
	cars[0].serial_num = -1;
}

void choose_direction(Car &car, Crossroad &cross) {
	int compare_y = pow(car.dst_y - car.y - 1, 2) - pow(car.dst_y - car.y + 1, 2);
	int compare_x = pow(car.dst_x - car.x - 1, 2) - pow(car.dst_x - car.x + 1, 2);
	if (compare_y<0 && compare_x<0) {
		if (cross.M_light) {
			car.next_up = "North";
		}
		else {
			car.next_up = "East";
		}
	}
	else if (compare_x < 0 && compare_y > 0) {
		if (cross.W_light) {
			car.next_up = "East";
		}
		else {
			car.next_up = "South";
		}
	}
	else if (compare_x > 0 && compare_y < 0) {
		if (cross.W_light) {
			car.next_up = "West";
		}
		else {
			car.next_up = "North";
		}
	}
	else if (compare_x > 0 && compare_y > 0) {
		if (cross.M_light) {
			car.next_up = "South";
		}
		else {
			car.next_up = "West";
		}
	}
	else if (compare_x == 0) {
		if (compare_y < 0) car.next_up = "North";
		else if (compare_y > 0) car.next_up = "South";
	}
	else if (compare_y == 0) {
		if (compare_x < 0) car.next_up = "East";
		else if (compare_x > 0) car.next_up = "West";
	}
}

void init_nissan() {
	for (int i = 1; i <= car_num; i++) {
		cars[i].id = i;
		cars[i].rebirth();
		choose_direction(cars[i], crossroads[cars[i].x / x_unit][cars[i].y / y_unit]);
		cars[i].up = cars[i].next_up;
		cars[i].steer(cars[i].up);
	}
}

void init_crossroad() { //初始化路口
	for (int i = 0; i <= x_bound / x_unit; i++) {
		for (int j = 0; j <= y_bound / y_unit; j++) {
			crossroads[i][j].light_flag = rand() % 13;
			crossroads[i][j].x = i * x_unit;
			crossroads[i][j].y = j * y_unit;
			crossroads[i][j].N_road = {};
			crossroads[i][j].S_road = {};
			crossroads[i][j].W_road = {};
			crossroads[i][j].E_road = {};
		}
	}
}

bool nissan_run(Car &car) {
	if (car.x == car.dst_x && car.y == car.dst_y) {
		car.rebirth();
	}
	else if (car.x > x_bound || car.x<0 || car.y>y_bound || car.y < 0) {
		cout << "一辆NISSAN出界，请检查代码" << endl;
		cout << car.id << "\t" << car.x << "," << car.y << car.up << endl;
		cout << "目的地" << car.dst_x << "," << car.dst_y << endl;
		cout << crossroads[car.x / x_unit][car.y / y_unit].M_light << "\t" << crossroads[car.x / x_unit][car.y / y_unit].W_light << endl;
		return true;
	}
	else if (car.x%x_unit == 0 && car.y%y_unit == 0) {
		Crossroad &cross = crossroads[car.x / x_unit][car.y / y_unit];
		choose_direction(car, cross);
		if (cross.M_light) {
			bool temp_flag = car.up == "North" && (!cross.S_road.size() || car.release_flag) \
				|| car.up == "South" && (!cross.N_road.size() || car.release_flag) || cross.W_light\
				|| car.up == "West" && car.next_up == "North" || car.up == "East" && car.next_up == "South";
			if (temp_flag) {
				car.steer(car.next_up);
				car.straight();
			}
			else {
				join_line(car, cross);
			}
		}
		else if (cross.W_light) {
			bool temp_flag = car.up == "East" && (!cross.W_road.size() || car.release_flag)\
				|| car.up == "West" && (!cross.E_road.size() || car.release_flag)\
				|| car.up == "North" && car.next_up == "East" || car.up == "South" && car.next_up == "West";
			if (temp_flag) {
				car.steer(car.next_up);
				car.straight();
			}
			else {
				join_line(car, cross);
			}
		}
		else {
			bool temp_flag = car.up == "North" && (!cross.S_road.size() || car.release_flag) && car.next_up == "East"\
				|| car.up == "South" && (!cross.N_road.size() || car.release_flag) && car.next_up == "West"\
				|| car.up == "East" && (!cross.W_road.size() || car.release_flag) && car.next_up == "South"\
				|| car.up == "West" && (!cross.E_road.size() || car.release_flag) && car.next_up == "North";
			if (temp_flag) {
				car.steer(car.next_up);
				car.straight();
			}
			else {
				join_line(car, cross);
			}
		}
	}
	else {
		car.straight();
	}
	return false;
}

void toyota_wait(Car &car, Crossroad &cross) {
	//cout << "南北灯" << cross.M_light << "\t" << "东西灯" << cross.W_light << endl;
	if (car.up=="North") {
		car.steer("East");
		car.straight();
		car.release_flag = false;
		car.wait_flag = false;
	}
}

void nissan_wait(Car &car, Crossroad &cross) {
	choose_direction(car, cross);
	bool temp_flag = car.up == "North"&&car.next_up == "East" || car.up == "East"&&car.next_up == "South"\
		|| car.up == "South"&&car.next_up == "West" || car.up == "West"&&car.next_up == "North";
	if (temp_flag) {
		car.steer(car.next_up);
		car.straight();
		car.release_flag = false;
		car.wait_flag = false;
	}
}

void nissan_wait2(Car &car) {
	int compare_y = pow(car.dst_y - car.y - 1, 2) - pow(car.dst_y - car.y + 1, 2);
	int compare_x = pow(car.dst_x - car.x - 1, 2) - pow(car.dst_x - car.x + 1, 2);
	if (compare_y < 0 && compare_x < 0) {
		if (car.up=="North") {
			car.steer("East");
			car.straight();
			car.release_flag = false;
			car.wait_flag = false;
		}
		else {
			car.next_up = "North";
		}
	}
	else if (compare_x < 0 && compare_y > 0) {
		if (car.up == "East") {
			car.steer("South");
			car.straight();
			car.release_flag = false;
			car.wait_flag = false;
		}
		else {
			car.next_up = "East";
		}
	}
	else if (compare_x > 0 && compare_y < 0) {
		if (car.up == "West") {
			car.steer("North");
			car.straight();
			car.release_flag = false;
			car.wait_flag = false;
		}
		else {
			car.next_up = "West";
		}
	}
	else if (compare_x > 0 && compare_y > 0) {
		if (car.up == "South") {
			car.steer("West");
			car.straight();
			car.release_flag = false;
			car.wait_flag = false;
		}
		else {
			car.next_up = "South";
		}
	}
	else if (compare_x == 0) {
		if (compare_y < 0) car.next_up = "North";
		else if (compare_y > 0) car.next_up = "South";
	}
	else if (compare_y == 0) {
		if (compare_x < 0) car.next_up = "East";
		else if (compare_x > 0) car.next_up = "West";
	}
}

int Simulation1() {
	init_crossroad();
	init_nissan();
	init_toyota();
	bool flag = false;
	int i = 0;
	for (; i < 2000; i++) {
		//cout << cars[0].x << "," << cars[0].y << "\t" << cars[0].up << "," << cars[0].next_up << endl;
		//cout << "排在第"<<cars[2372].serial_num << "\t";
		//cout << "目的地" << cars[2372].dst_x << ',' << cars[2372].dst_y << endl;
		//cout << cars[0].x << "," << cars[0].y << cars[0].up << endl;
		for (int m = 0; m <= x_bound / x_unit; m++) {
			for (int n = 0; n <= y_bound / y_unit; n++) {
				crossroads[m][n].blink();
			}
		}
		if (!cars[0].wait_flag) {
			flag = toyota_run1(cars[0]);
		}
		else {
			toyota_wait(cars[0], crossroads[cars[0].x / x_unit][cars[0].y / y_unit]);
		}
		for (int j = 1; j <= car_num; j++) {
			if (!cars[j].wait_flag) {
				flag = flag || nissan_run(cars[j]);
			}
			else {
				//nissan_wait(cars[j], crossroads[cars[j].x / x_unit][cars[j].y / y_unit]);
				nissan_wait2(cars[j]);
			}
		}
		if (flag) {
			cout << "耗时" << i << "个单位时间。" << endl;
			break;
		}
	}
	if (cars[0].x != x_bound || cars[0].y != y_bound) {
		cout << "测试汽车未能在规定时间内到达终点" << endl;
	}
	return i;
}

int Simulation2() {
	init_crossroad();
	init_nissan();
	init_toyota();
	bool flag = false;
	int i = 0;
	for (; i < 2000; i++) {
		//cout << cars[0].x << "," << cars[0].y << cars[0].up << endl;
		for (int m = 0; m <= x_bound / x_unit; m++) {
			for (int n = 0; n <= y_bound / y_unit; n++) {
				crossroads[m][n].blink();
			}
		}
		if (!cars[0].wait_flag) {;
			flag = toyota_run2(cars[0]);
		}
		else {
			toyota_wait(cars[0], crossroads[cars[0].x / x_unit][cars[0].y / y_unit]);
		}
		for (int j = 1; j <= car_num; j++) {
			if (!cars[j].wait_flag) {
				flag = flag || nissan_run(cars[j]);
			}
			else {
				nissan_wait(cars[j], crossroads[cars[j].x / x_unit][cars[j].y / y_unit]);
			}
		}
		if (flag) {
			cout << "耗时" << i << "个单位时间。" << endl;
			break;
		}
	}
	if (cars[0].x != x_bound || cars[0].y != y_bound) {
		cout << "测试汽车未能在规定时间内到达终点" << endl;
	}
	return i;
}