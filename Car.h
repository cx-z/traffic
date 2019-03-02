#pragma once
#include<string>
#include<iostream>
#include<time.h>

using namespace std;

constexpr int x_bound = 200;
constexpr int y_bound = 200;
constexpr int x_unit = 20; //街道单位长度是20
constexpr int y_unit = 20;
constexpr int car_num = 50000;

class Car
{
public:
	int id = 0; //身份标识
	int x = 0; //坐标（x,y）
	int y = 0;
	int x_speed = 0; //x与y方向的速度
	int y_speed = 1;
	string up = "East"; //当前行驶方向
	string next_up = "East"; //下一步要走的方向
	bool wait_flag = false; //是否正在路口等待
	bool release_flag = false; //是否离开队列
	int serial_num = -1; //在队列中的位置，-1表示刚进入队列，排在最后一位
	int dst_x = 200; //目的地
	int dst_y = 200;

	void straight() {
		x += x_speed;
		y += y_speed;
		serial_num = -1;
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

	void rebirth() {
		x = (rand() % (x_bound / x_unit)) * x_unit;
		y = (rand() % (y_bound / y_unit)) * y_unit;
		dst_x = (rand() % (x_bound / x_unit)) * x_unit;
		dst_y = (rand() % (y_bound / y_unit)) * y_unit;
		wait_flag = false;
		release_flag = false;
		serial_num = -1;
	}

	
};

Car cars[car_num+1];
