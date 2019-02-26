#pragma once
#include"Crossroad.h"
#include"Car.h"
#include"strategy.h"
#include<iostream>
#include<queue>

void init_nissan() {
	for (int i = 1; i <= car_num; i++) {
		cars[i].id = i;
		int j = rand() % 4;
		switch (j)
		{
		case 0:
			cars[i].x = (rand() % (x_bound / x_unit)) * x_unit;
			cars[i].y = rand() % y_bound + 1;
			cars[i].up = "South";
			break;
		case 1:
			cars[i].x = (rand() % (x_bound / x_unit)) * x_unit;
			cars[i].y = rand() % y_bound;
			cars[i].up = "North";
			break;
		case 2:
			cars[i].y = (rand() % (y_bound / y_unit)) * y_unit;
			cars[i].x = rand() % x_bound + 1;
			cars[i].up = "West";
			break;
		case 3:
			cars[i].y = (rand() % (y_bound / y_unit)) * y_unit;
			cars[i].x = rand() % x_bound;
			cars[i].up = "East";
			break;
		}
		cars[i].steer(cars[i].up);
		cars[i].next_up = cars[i].up;
	}
}

void init_crossroad() { //��ʼ��·��
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
	if (car.x > x_bound || car.x<0 || car.y>y_bound || car.y < 0) {
		cout << "һ��NISSAN���磬�������" << endl;
		cout << car.id << "\t" << car.x << "," << car.y << car.up << endl;
		cout << crossroads[car.x / x_unit][car.y / y_unit].M_light << "\t" << crossroads[car.x / x_unit][car.y / y_unit].W_light << endl;
		return true;
	}
	if (car.x%x_unit == 0 && car.y%y_unit == 0) {
		car.choose_direction();
		Crossroad &cross = crossroads[car.x / x_unit][car.y / y_unit];
		if (cross.M_light) {
			bool temp_flag = car.up == "North" && (!cross.S_road.size() || car.release_flag) \
				|| car.up == "South" && (!cross.N_road.size() || car.release_flag) || cross.W_light;
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
				|| car.up == "West" && (!cross.E_road.size() || car.release_flag);
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
	//cout << "�ϱ���" << cross.M_light << "\t" << "������" << cross.W_light << endl;
	if (cross.S_road.size() && car.id == cross.S_road.front().id) {
		car.next_up = "East";
	}
}

void nissan_wait(Car &car, Crossroad &cross) {
	
}

int Simulation1() {
	//srand((unsigned int)(time(NULL)));
	init_crossroad();
	init_nissan();
	bool flag = false;
	int i = 0;
	for (; i < 2000; i++) {
		//cout << cars[0].x << "," << cars[0].y << cars[0].up << endl;
		for (int m = 0; m <= x_bound / x_unit; m++) {
			for (int n = 0; n <= y_bound / y_unit; n++) {
				crossroads[m][n].blink();
			}
		}
		if (!cars[0].wait_flag) {
			flag = toyota_run1(cars[0]);
			//flag = toyota_run2(cars[0]);
		}
		else {
			toyota_wait(cars[0], crossroads[cars[0].x / x_unit][cars[0].y / y_unit]);
		}
		for (int j = 1; j <= car_num; j++) {
		//for (int j = 9; j < 10;j++) {
			if (!cars[j].wait_flag) {
				flag = flag || nissan_run(cars[j]);
			}
			/*else {
				nissan_wait(cars[j], crossroads[cars[j].x / x_unit][cars[j].y / y_unit]);
			}*/
		}
		if (flag) {
			cout << "��ʱ" << i << "����λʱ�䡣" << endl;
			break;
		}
	}
	if (cars[0].x != x_bound || cars[0].y != y_bound) {
		//cout << "��������δ���ڹ涨ʱ���ڵ����յ�" << endl;
	}
	return i;
}

int Simulation2() {
	//srand((unsigned int)(time(NULL)));
	init_crossroad();
	init_nissan();
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
			/*else {
				nissan_wait(cars[j], crossroads[cars[j].x / x_unit][cars[j].y / y_unit]);
			}*/
		}
		if (flag) {
			cout << "��ʱ" << i << "����λʱ�䡣" << endl;
			break;
		}
	}
	if (cars[0].x != x_bound || cars[0].y != y_bound) {
		//cout << "��������δ���ڹ涨ʱ���ڵ����յ�" << endl;
	}
	return i;
}