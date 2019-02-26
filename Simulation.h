#pragma once
#include"Crossroad.h"
#include"Car.h"
#include<iostream>
#include<queue>

void init_nissan() {
	srand((unsigned int)(time(NULL)));
	for (int i = 1; i <= car_num; i++) {
		cars[i].id = i;
		int j = rand() % 4 + 1;
		switch (j)
		{
		case 1:
			cars[i].x = (rand() % (x_bound / x_unit + 1)) * 10;
			cars[i].y = rand() % (y_bound + 1);
			cars[i].steer("South");
			break;
		case 2:
			cars[i].x = (rand() % (x_bound / x_unit + 1)) * 10;
			cars[i].y = rand() % (y_bound + 1);
			cars[i].steer("North");
			break;
		case 3:
			cars[i].y = (rand() % (y_bound / y_unit + 1)) * 10;
			cars[i].x = rand() % (x_bound + 1);
			cars[i].steer("West");
			break;
		case 4:
			cars[i].y = (rand() % (y_bound / y_unit + 1)) * 10;
			cars[i].x = rand() % (x_bound + 1);
			cars[i].steer("East");
			break;
		}
		cars[i].next_up = cars[i].up;
	}
}

void init_crossroad() { //初始化路口
	for (int i = 0; i <= x_bound / 10; i++) {
		for (int j = 0; j <= y_bound / 10; j++) {
			crossroads[i][j].light_flag = rand() % 13;
			crossroads[i][j].x = i * 10;
			crossroads[i][j].y = j * 10;
			crossroads[i][j].N_road = {};
			crossroads[i][j].S_road = {};
			crossroads[i][j].W_road = {};
			crossroads[i][j].E_road = {};
		}
	}
}

void join_line(Car &car, Crossroad &cross) {
	car.wait_flag = true;
	car.release_flag = false;
	if (car.up == "North") {
		cross.S_road.push(car);
		car.serial_num = cross.S_road.size() + 1;
	}
	else if (car.up == "South") {
		cross.N_road.push(car);
		car.serial_num = cross.N_road.size() + 1;
	}
	else if (car.up == "East") {
		cross.W_road.push(car);
		car.serial_num = cross.W_road.size() + 1;
	}
	else {
		cross.E_road.push(car);
		car.serial_num = cross.E_road.size() + 1;
	}
	if (car.id == 0) {
		cout << "排在第" << car.serial_num << "位" << endl;
	}
}

bool toyota_run(Car &car) {
	if (car.x == x_bound && car.y == y_bound) {
		return true;
	}
	else if (car.x%x_unit == 0 && car.y%y_unit == 0) {
		Crossroad &cross = crossroads[car.x / x_unit][car.y / y_unit];
		cout << "南北灯" << cross.M_light << "\t" << "东西灯" << cross.W_light << endl;
		if (cross.M_light && car.up=="North" && (!cross.S_road.size() || car.release_flag)) {
			if (cross.y != y_bound) {
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
		else if (!cross.M_light && car.up == "North" && (!cross.S_road.size() || car.release_flag)) {
			if (cross.x != x_bound) {
				car.steer("East");
				car.straight();
			}
		}
		else {
			join_line(car, cross);
		}
	}
	else {
		car.straight();
	}
	return false;
}

bool nissan_run(Car &car) {
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
	cout << "南北灯" << cross.M_light << "\t" << "东西灯" << cross.W_light << endl;
	if (cross.S_road.size() && car.id == cross.S_road.front().id) {
		car.next_up = "East";
	}
}

void nissan_wait(Car &car, Crossroad &cross) {

}

void Simulation() {
	srand((unsigned int)(time(NULL)));
	init_crossroad();
	init_nissan();
	bool flag = false;
	for (int i = 0; i < 1000; i++) {
		cout << cars[0].x << "," << cars[0].y << cars[0].up << endl;
		for (int m = 0; m <= x_bound / x_unit; m++) {
			for (int n = 0; n <= y_bound / y_unit; n++) {
				crossroads[m][n].blink();
			}
		}
		if (!cars[0].wait_flag) {
			flag = toyota_run(cars[0]);
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
}