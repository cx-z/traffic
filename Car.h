#pragma once
#include<string>
#include<iostream>
#include<time.h>

using namespace std;

constexpr int x_bound = 200;
constexpr int y_bound = 200;
constexpr int x_unit = 20; //�ֵ���λ������20
constexpr int y_unit = 20;
constexpr int car_num = 50000;

class Car
{
public:
	int id = 0; //��ݱ�ʶ
	int x = 0; //���꣨x,y��
	int y = 0;
	int x_speed = 0; //x��y������ٶ�
	int y_speed = 1;
	string up = "East"; //��ǰ��ʻ����
	string next_up = "East"; //��һ��Ҫ�ߵķ���
	bool wait_flag = false; //�Ƿ�����·�ڵȴ�
	bool release_flag = false; //�Ƿ��뿪����
	int serial_num = -1; //�ڶ����е�λ�ã�-1��ʾ�ս�����У��������һλ
	int dst_x = 200; //Ŀ�ĵ�
	int dst_y = 200;

	void straight() {
		x += x_speed;
		y += y_speed;
		serial_num = -1;
		//release_flag = false;
	}

	void steer(string direction) { //����ѡ����ʻ����
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
