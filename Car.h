#pragma once
#include<string>
#include<iostream>
#include<time.h>

using namespace std;

constexpr int x_bound = 30;
constexpr int y_bound = 30;
constexpr int unit_street = 10; //街道单位长度是10
constexpr int car_num = 10000;

class Car
{
public:
	int id = 0; //身份标识
	int x = 0; //坐标（x,y）
	int y = 0;
	int x_speed = 0;
	int y_speed = 1;
	string up = "North";
	string next_up = "North";
	bool wait_flag = false;
	int serial_num = 100;

	void straight() {
		x += x_speed;
		y += y_speed;
	}

	void steer(string direction) { //汽车选择行驶方向
		if (direction == "West") {
			x_speed = -1;
			y_speed = 0;
			up = "West";
		}
		else if (direction == "East") {
			x_speed = 1;
			y_speed = 0;
			up = "East";
		}
		else if (direction == "North") {
			x_speed = 0;
			y_speed = 1;
			up = "North";
		}
		else if (direction == "South") {
			x_speed = 0;
			y_speed = -1;
			up = "South";
		}
		else {
			x_speed = 0;
			y_speed = 0;
		}
	}

	void choose_direction() {
		int i = rand() % 4;
		if (i == 0) next_up = "South";
		else if (i == 1) next_up = "North";
		else if (i == 2) next_up = "East";
		else next_up = "West";
	}
};

Car toyota;
Car nissan[car_num];

void init_nissan() {
	srand((unsigned int)(time(NULL)));
	for (int i = 0; i < car_num; i++) {
		nissan[i].id = i + 1;
		int j = rand() % 4 + 1;
		switch (j)
		{
		case 1:
			nissan[i].x = (rand() % (x_bound / unit_street + 1)) * 10;
			//nissan[i].x = (rand() % 3) * 10;
			nissan[i].y = rand() % (y_bound + 1);
			nissan[i].steer("South");
			break;
		case 2:
			nissan[i].x = (rand() % (x_bound / unit_street + 1)) * 10;
			nissan[i].y = rand() % (y_bound + 1);
			nissan[i].steer("North");
			break;
		case 3:
			nissan[i].y = (rand() % (y_bound / unit_street + 1)) * 10;
			nissan[i].x = rand() % (x_bound + 1);
			nissan[i].steer("West");
			break;
		case 4:
			nissan[i].y = (rand() % (y_bound / unit_street + 1)) * 10;
			nissan[i].x = rand() % (x_bound + 1);
			nissan[i].steer("East");
			break;
		}
		nissan[i].next_up = nissan[i].up;
	}
}
