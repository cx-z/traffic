#pragma once
#include<string>
#include<iostream>
#include<time.h>

using namespace std;

constexpr int x_bound = 200;
constexpr int y_bound = 200;
constexpr int x_unit = 20; //街道单位长度是20
constexpr int y_unit = 20;
constexpr int car_num = 1;

class Car
{
public:
	int id = 0; //身份标识
	int x = 0; //坐标（x,y）
	int y = 0;
	int x_speed = 0;
	int y_speed = 1;
	string up = "East";
	string next_up = "East";
	bool wait_flag = false;
	bool release_flag = false;
	int serial_num = -1;

	void straight() {
		x += x_speed;
		y += y_speed;
		//release_flag = false;
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
	}

	void choose_direction() {
		bool flag = true;
		while (flag) {
			int i = rand() % 4;
			if (i == 0 && y > 0) { next_up = "South"; flag = false; }
			else if (i == 1 && y < y_bound) { next_up = "North"; flag = false; }
			else if (i == 2 && x < x_bound) { next_up = "East"; flag = false; }
			else if (i == 3 && x > 0) { next_up = "West"; flag = false; }
		}
	}
};

Car cars[car_num+1];
