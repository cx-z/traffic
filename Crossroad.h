#pragma once
#include<vector>
#include"Car.h"

using namespace std;

constexpr int queue = 3;

class Crossroad
{
public:
	int x; //路口坐标
	int y;
	bool M_light = true; //南北方向红绿灯，红灯为False，绿灯为True
	bool W_light = !M_light; //东西方向红绿灯
	vector<Car> W_road;
	vector<Car> E_road;
	vector<Car> N_road;
	vector<Car> S_road;

	int light_flag = 0;
	void blink() { //红绿灯变换
		light_flag = light_flag % 13;
		if (light_flag > 7) {
			M_light = true;
			W_light = false;
		}
		else if (light_flag < 5) {
			M_light = false;
			W_light = true;
		}
		else {
			M_light = false;
			W_light = false;
		}
		light_flag++;
		release_car();
	}

	void release_car() {
		//每次绿灯时，排队等待的前十辆车可以起步离开
		if (M_light) {
			int a = (N_road.size() > queue) ? queue : N_road.size();
			int b = (S_road.size() > queue) ? queue : S_road.size();
			N_road.erase(N_road.begin(), N_road.begin() + a);
			S_road.erase(S_road.begin(), S_road.begin() + b);
		}
		else if (W_light) {
			int a = (W_road.size() > queue) ? queue : W_road.size();
			int b = (E_road.size() > queue) ? queue : E_road.size();
			W_road.erase(W_road.begin(), W_road.begin() + a);
			E_road.erase(E_road.begin(), E_road.begin() + b);
		}
	}
};

Crossroad crossroads[x_bound/unit_street + 1][y_bound/unit_street + 1];

void init_crossroad() { //初始化路口
	srand((unsigned int)(time(NULL)));
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
