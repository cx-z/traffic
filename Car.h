#pragma once
#include<string>
#include<vector>

using namespace std;
class Car
{
public:
	int x = 0; //坐标（x,y）
	int y = 0;
	int x_speed = 0;
	int y_speed = 1;
	string up = "North";

	void straight() {
		x += x_speed;
		y += y_speed;
		cout << x << "," << y << endl;
	}

	void steer(string direction) { //汽车选择行驶方向
		if (direction == "West") {
			x_speed = -1;
			y_speed = 0;
		}
		else if (direction == "East") {
			x_speed = 1;
			y_speed = 0;
		}
		else if (direction == "North") {
			x_speed = 0;
			y_speed = 1;
		}
		else if (direction == "South") {
			x_speed = 0;
			y_speed = -1;
		}
		else {
			x_speed = 0;
			y_speed = 0;
		}
	}
};

Car toyota;
vector<Car> nissan(10);

void init_car(Car car) {
	car.x = 0;
	car.y = 1;
	car.x_speed = 0;
	car.y_speed = 1;
	car.up = "North";
}
