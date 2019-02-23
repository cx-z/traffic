// Traffic.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include"Car.h"
#include"Crossroad.h"
#include<vector>

bool my_find(vector<Car> &vec, Car &car) { //查找汽车是否在队列中
	for (auto iter = vec.begin(); iter < vec.end(); iter++) {
		if (iter->id == car.id) return true;
	}
	return false;
}

void wait(Car &car, Crossroad &crossroad) {
	car.x_speed = 0;
	car.y_speed = 0;
	//每次绿灯时，排队等待的前十辆车可以起步离开
	if (crossroad.M_light) {
		if (crossroad.N_road.size() > 10)
			crossroad.N_road.erase(crossroad.N_road.begin(), crossroad.N_road.begin() + 10);
		else
			crossroad.N_road.clear();
		if (crossroad.S_road.size() > 10)
			crossroad.S_road.erase(crossroad.S_road.begin(), crossroad.S_road.begin() + 10);
		else
			crossroad.S_road.clear();
	}
	else if (crossroad.W_light) {
		if (crossroad.W_road.size() > 10)
			crossroad.W_road.erase(crossroad.W_road.begin(), crossroad.W_road.begin() + 10);
		else
			crossroad.W_road.clear();
		if (crossroad.E_road.size() > 10)
			crossroad.E_road.erase(crossroad.E_road.begin(), crossroad.E_road.begin() + 10);
		else
			crossroad.E_road.clear();
	}
	else if (!car.wait_flag) { //等红灯时，如果汽车没有在排队，进入队列，且等待状态为真
		if (car.up == "North") crossroad.S_road.push_back(car);
		else if (car.up == "South") crossroad.N_road.push_back(car);
		else if (car.up == "West") crossroad.E_road.push_back(car);
		else if (car.up == "East") crossroad.W_road.push_back(car);
		else cout << "汽车行驶方向有误，请检查代码。" << endl;
		car.wait_flag = true;
	}
}

void judge_wait(Car &car, Crossroad &crossroad) {
	bool N_flag = my_find(crossroad.N_road, car);
	bool S_flag = my_find(crossroad.S_road, car);
	bool W_flag = my_find(crossroad.W_road, car);
	bool E_flag = my_find(crossroad.E_road, car);
	//car.wait_flag为真，则汽车正在排队中
	car.wait_flag = N_flag || S_flag || W_flag || E_flag;
}

bool nissan_run(Car &car) {
	if (car.x < x_bound && car.y < y_bound && car.x>0 && car.y>0) {
		if (car.x%unit_street == 0 && car.y%unit_street == 0) {
			judge_wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			car.choose_direction();
			cout << crossroads[car.x / unit_street][car.y / unit_street].W_light << endl;
			cout << car.x_speed << endl;
			cout << car.next_up << endl;
			if (crossroads[car.x/unit_street][car.y/unit_street].M_light && !car.wait_flag) { //如果南北向是绿灯
				bool temp_flag = car.next_up == "North" || car.next_up == "South" || \
					(car.up == "South" || car.next_up == "West") || (car.up == "North" || car.next_up == "East");
				if (temp_flag) {
					car.steer(car.next_up);
					car.straight();
				}
				else {
					wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
				}
			}
			else if (crossroads[car.x/unit_street][car.y/unit_street].W_light && !car.wait_flag) { //如果东西向是绿灯
				bool temp_flag = (car.next_up == "West" || car.next_up == "East") || \
					(car.up == "West" || car.next_up == "North") || (car.up == "East" || car.next_up == "South");
				if (temp_flag) {
					car.steer(car.next_up);
					car.straight();
				}
				else {
					wait(car, crossroads[car.x%unit_street][car.y%unit_street]);
				}
			}
			else { //如果南北向与东西向都是红灯，等待
				wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			}
		}
		else {
			car.straight();
		}
	}
	else if (car.x == x_bound && car.y < y_bound && car.y>0) {
		cout << "右边界" << endl;
		if (car.y%unit_street == 0) { //在路口
			judge_wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			car.choose_direction();
			if (crossroads[car.x/unit_street][car.y/unit_street].M_light && !car.wait_flag) { //如果南北向是绿灯
				bool temp_flag = car.next_up == "North" || car.next_up == "South" || (car.up == "South" || car.next_up == "West");
				if (temp_flag) {
					car.steer(car.next_up);
					car.straight();
				}
				else {
					wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
				}
			}
			else if (crossroads[car.x/unit_street][car.y/unit_street].W_light && !car.wait_flag) { //如果东西向是绿灯
				if (car.next_up == "West") {
					car.steer(car.next_up);
					car.straight();
				}
				else {
					wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
				}
			}
			else { //如果南北向与东西向都是红灯，等待
				wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			}
		}
		else {
			car.straight();
		}
	}
	else if (car.x < x_bound && car.y == y_bound && car.x>0) {
		cout << "到达上边界" << endl;
		if (car.x%unit_street == 0) { //在路口
			judge_wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			car.choose_direction();
			if (crossroads[car.x/unit_street][car.y/unit_street].M_light && !car.wait_flag) { //如果南北向是绿灯
				if (car.next_up == "South") {
					car.steer(car.next_up);
					car.straight();
				}
				else {
					wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
				}
			}
			else if (crossroads[car.x/unit_street][car.y/unit_street].W_light && !car.wait_flag) { //如果东西向是绿灯
				bool temp_flag = car.next_up == "East" || car.next_up == "West" || (car.up == "East" || car.next_up == "South");
				if (temp_flag) {
					car.steer(car.next_up);
					car.straight();
				}
				else {
					wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
				}
			}
			else { //如果南北向与东西向都是红灯，等待
				wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			}
		}
		else {
			car.straight();
		}
	}
	else if(car.x==0 && car.y<y_bound && car.y>0){
		cout << "左边界" << endl;
		if (car.y%unit_street == 0) { //在路口
			judge_wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			car.choose_direction();
			if (crossroads[car.x/unit_street][car.y/unit_street].M_light && !car.wait_flag) { //如果南北向是绿灯
				bool temp_flag = car.next_up == "North" || car.next_up == "South" || (car.up == "North" || car.next_up == "East");
				if (temp_flag) {
					car.steer(car.next_up);
					car.straight();
				}
				else {
					wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
				}
			}
			else if (crossroads[car.x/unit_street][car.y/unit_street].W_light && !car.wait_flag) { //如果东西向是绿灯
				if (car.next_up == "East") {
					car.steer(car.next_up);
					car.straight();
				}
				else {
					wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
				}
			}
			else { //如果南北向与东西向都是红灯，等待
				wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			}
		}
		else {
			car.straight();
		}
	}
	else if (car.x < x_bound && car.y == 0 && car.x>0) {
		cout << "下边界" << endl;
		if (car.x%unit_street == 0) { //在路口
			judge_wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			car.choose_direction();
			if (crossroads[car.x/unit_street][car.y/unit_street].M_light && !car.wait_flag) { //如果南北向是绿灯
				if (car.next_up == "North") {
					car.steer(car.next_up);
					car.straight();
				}
				else {
					wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
				}
			}
			else if (crossroads[car.x/unit_street][car.y/unit_street].W_light && !car.wait_flag) { //如果东西向是绿灯
				bool temp_flag = car.next_up == "East" || car.next_up == "West" || (car.up == "West" || car.next_up == "North");
				if (temp_flag) {
					car.steer(car.next_up);
					car.straight();
				}
				else {
					wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
				}
			}
			else { //如果南北向与东西向都是红灯，等待
				wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			}
		}
		else {
			car.straight();
		}
	}
	else if (car.x == x_bound && car.y == y_bound) {
		judge_wait(car,crossroads[car.x/unit_street][car.y/unit_street]);
		car.choose_direction();
		cout << car.next_up << "----" << endl;
		if (crossroads[car.x/unit_street][car.y/unit_street].M_light && !car.wait_flag) {
			if (car.next_up == "South") {
				car.steer(car.next_up);
				car.straight();
			}
			else {
				wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			}
		}
		else if (crossroads[car.x/unit_street][car.y/unit_street].W_light && !car.wait_flag) {
			if (car.next_up == "West") {
				car.steer(car.next_up);
				car.straight();
			}
			else {
				wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			}
		}
		else {
			wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
		}
	}
	else if (car.x == 0 && car.y == y_bound) {
		judge_wait(car, crossroads[0][car.y/unit_street]);
		car.choose_direction();
		if (crossroads[0][car.y/unit_street].M_light && !car.wait_flag) {
			bool temp_flag = car.next_up == "South" || (car.up == "North" || car.next_up == "East");
			if (temp_flag) {
				car.steer(car.next_up);
				car.straight();
			}
			else {
				wait(car, crossroads[0][car.y/unit_street]);
			}
		}
		else if (crossroads[0][car.y/unit_street].W_light && !car.wait_flag) {
			if (car.next_up == "East") {
				car.steer(car.next_up);
				car.straight();
			}
			else {
				wait(car, crossroads[0][car.y/unit_street]);
			}
		}
		else {
			wait(car, crossroads[0][car.y/unit_street]);
		}
	}
	else if (car.x == x_bound && car.y == 0) {
		judge_wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
		car.choose_direction();
		if (crossroads[car.x/unit_street][0].M_light && !car.wait_flag) {
			if (car.next_up == "North") {
				car.steer(car.next_up);
				car.straight();
			}
			else {
				wait(car, crossroads[car.x/unit_street][0]);
			}
		}
		else if (crossroads[car.x/unit_street][0].W_light && !car.wait_flag) {
			if (car.next_up == "West") {
				car.steer(car.next_up);
				car.straight();
			}
			else {
				wait(car, crossroads[car.x/unit_street][0]);
			}
		}
		else {
			wait(car, crossroads[car.x/unit_street][0]);
		}
	}
	else if (car.x == 0 && car.y == 0) {
		judge_wait(car, crossroads[0][0]);
		car.choose_direction();
		if (crossroads[0][0].M_light && !car.wait_flag) {
			if (car.next_up == "North") {
				car.steer(car.next_up);
				car.straight();
			}
			else {
				wait(car, crossroads[0][0]);
			}
		}
		else if (crossroads[0][0].W_light && !car.wait_flag) {
			bool temp_flag = car.next_up == "East" || (car.up == "West" || car.next_up == "North");
			if (temp_flag) {
				car.steer(car.next_up);
				car.straight();
			}
			else {
				wait(car, crossroads[0][0]);
			}
		}
		else {
			wait(car, crossroads[0][0]);
		}
	}
	else {
		cout << "一辆nissan出界，请检查代码。" << endl;
		return true;
	}
	return false;
}

bool toyota_run(Car &car) {
	//cout << "toyota\t" << car.x << "," << car.y << "\t" << car.x_speed << "," << car.y_speed << endl;
	if (car.x < x_bound && car.y < y_bound) {
		if (car.x%unit_street == 0 && car.y%unit_street == 0) {
			judge_wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			if (crossroads[car.x/unit_street][car.y/unit_street].M_light && !car.wait_flag) { //如果南北向是绿灯，向北走
				car.steer("North");
				car.straight();
			}
			else if (car.up=="North" || crossroads[car.x/unit_street][car.y/unit_street].W_light && !car.wait_flag) { //如果东西向是绿灯，向东走
				car.steer("East");
				car.straight();
			}
			else { //如果南北向与东西向都是红灯，等待
				wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			}
		}
		else {
			car.straight();
		}
	}
	else if (car.x == x_bound && car.y < y_bound) {
		car.steer("North"); //在右边界方向始终为朝北
		if (car.y%unit_street == 0) { //在路口
			judge_wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			if (crossroads[car.x/unit_street][car.y/unit_street].M_light && !car.wait_flag) { //如果南北向是绿灯，向北走
				car.straight();
			}
			else { //其余情况都等待
				wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			}
		}
		else {
			car.straight();
		}
	}
	else if (car.x < x_bound && car.y == y_bound) {
		int a = car.x / unit_street;
		int b = car.y / unit_street;
		//car.steer("East"); //在上边界方向始终朝东
		if (car.x%unit_street == 0) { //在路口
			judge_wait(car, crossroads[a][b]);
			if (crossroads[a][b].W_light && !car.wait_flag) { //如果东西向是绿灯，向东走
				car.steer("East");
				car.straight();
			}
			else { //其余情况都等待
				wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			}
		}
		else {
			car.straight();
		}
	}
	else if (car.x == x_bound && car.y == y_bound) {
		cout << "测试汽车到达终点" << endl;
		return true;
	}
	else {
		cout << "测试汽车出界，请检查代码。" << endl;
		return true;
	}
	return false;
}

int main()
{
	init_crossroad();
	init_nissan();
	
	bool flag = false;
	for (int i = 0; i < 100; i++) {
		//cout << "nissan1\t" << nissan[0].x << "," << nissan[0].y  << endl;

		cout << "nissan3\t" << nissan[2].x << "," << nissan[2].y << nissan[2].next_up<< endl;
		for (int m = 0; m <= x_bound / unit_street; m++) {
			for (int n = 0; n <= y_bound / unit_street; n++) {
				crossroads[m][n].blink();
			}
		}
		flag = toyota_run(toyota);
		nissan_run(nissan[2]);
		/*for (int j = 0; j < 10; j++) {
			flag = flag || nissan_run(nissan[j]);
		}*/
		if (flag) {
			cout << "耗时" << i << "个单位时间。" << endl;
			break;
		}
	}
}
