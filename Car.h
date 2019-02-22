#pragma once
#include<string>
#include<iostream>

using namespace std;

constexpr int x_bound = 20;
constexpr int y_bound = 20;
constexpr int unit_street = 10; //街道单位长度是10

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
		switch (i) {
		case 0:
			next_up = string("South");
		case 1:
			next_up = string("North");
		case 2:
			next_up = string("West");
		case 3:
			next_up = string("East");
		}
	}


};

Car toyota;
Car nissan[10];

void init_nissan() {
	for (int i = 0; i < 10; i++) {
		nissan[i].id = i + 1;
		int j = rand() % 4 + 1;
		switch (j)
		{
		case 1:
			//nissan[i].x = rand() % (x_bound % unit_street + 1) * 10;
			nissan[i].x = (rand() % 3) * 10;
			nissan[i].y = rand() % (y_bound + 1);
			nissan[i].steer("South");
		case 2:
			nissan[i].x = (rand() % 3) * 10;
			nissan[i].y = rand() % (y_bound + 1);
			nissan[i].steer("North");
		case 3:
			nissan[i].y = (rand() % 3) * 10;
			nissan[i].x = rand() % (x_bound + 1);
			nissan[i].steer("West");
		case 4:
			nissan[i].y = (rand() % 3) * 10;
			nissan[i].x = rand() % (x_bound + 1);
			nissan[i].steer("East");
		}
		nissan[i].next_up = nissan[i].up;
	}
}

