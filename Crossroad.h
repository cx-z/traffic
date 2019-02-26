#pragma once
#include<queue>
#include<iostream>
#include"Car.h"

using namespace std;

constexpr int release_num = 10;

class Crossroad
{
public:
	int x; //路口坐标
	int y;
	bool M_light = true; //南北方向红绿灯，红灯为False，绿灯为True
	bool W_light = !M_light; //东西方向红绿灯
	queue<Car> W_road;
	queue<Car> E_road;
	queue<Car> N_road;
	queue<Car> S_road;

	int light_flag = 0;
	void blink() { //红绿灯变换
		bool corner = (x == 0 && y == 0) || (x == x_bound && y == 0) || (x == 0 && y == y_bound) || (x == x_bound && y == y_bound);
		if (corner) {
			M_light = true;
			W_light = true;
		}
		else {
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
		}
		release_car();
	}

	void release_car() {
		//每次绿灯时，排队等待的前十辆车可以起步离开
		if (M_light) {
			int a = (N_road.size() > release_num) ? release_num : N_road.size();
			int b = (S_road.size() > release_num) ? release_num : S_road.size();
			for (int i = 0; i < a; i++) {
				int temp_id = N_road.front().id;
				cars[temp_id].wait_flag = false; 
				cars[temp_id].release_flag = true;
				N_road.pop();		
			}
			for (int i = 0; i < b; i++) { 
				int temp_id = S_road.front().id;
				cars[temp_id].wait_flag = false;
				cars[temp_id].release_flag = true;
				S_road.pop(); 
			}
		}
		else if (W_light) {
			int a = (W_road.size() > release_num) ? release_num : W_road.size();
			int b = (E_road.size() > release_num) ? release_num : E_road.size();
			for (int i = 0; i < a; i++) { 
				int temp_id = W_road.front().id;
				cars[temp_id].wait_flag = false;
				cars[temp_id].release_flag = true;
				W_road.pop(); 
			}
			for (int i = 0; i < b; i++) {
				int temp_id = E_road.front().id;
				cars[temp_id].wait_flag = false;
				cars[temp_id].release_flag = true;
				E_road.pop();
			}
		}
		else {
			if (S_road.size() && S_road.front().next_up == "East" && x != x_bound) {
				int temp_id = S_road.front().id;
				cars[temp_id].wait_flag = false;
				cars[temp_id].release_flag = true;
				S_road.pop();
			}
			if (N_road.size() && N_road.front().next_up == "West" && x != 0) {
				int temp_id = N_road.front().id;
				cars[temp_id].wait_flag = false;
				cars[temp_id].release_flag = true;
				N_road.pop();
			}
			if (W_road.size() && W_road.front().next_up == "South" && y != 0) {
				int temp_id = W_road.front().id;
				cars[temp_id].wait_flag = false;
				cars[temp_id].release_flag = true;
				W_road.pop();
			}
			if (E_road.size() && E_road.front().next_up == "North" && y != y_bound) {
				int temp_id = E_road.front().id;
				cars[temp_id].wait_flag = false;
				cars[temp_id].release_flag = true;
				E_road.pop();
			}
		}
	}
};

Crossroad crossroads[x_bound/x_unit + 1][y_bound/y_unit + 1];
