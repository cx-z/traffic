// Traffic.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include"Car.h"
#include"Crossroad.h"
#include<vector>

bool my_find(vector<Car> &vec, Car &car) { //查找汽车是否在队列中
	for (auto iter = vec.begin(); iter < vec.end(); iter++) {
		if (iter->id == car.id) {
			car.serial_num = iter - vec.begin();
			return true;
		}
	}
	return false;
}

void wait(Car &car, Crossroad &crossroad) {
	car.x_speed = 0;
	car.y_speed = 0;
	if (!car.wait_flag && !crossroad.M_light && !crossroad.W_light) { //等红灯时，如果汽车没有在排队，进入队列，且等待状态为真
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
			if (crossroads[car.x/unit_street][car.y/unit_street].M_light && !car.wait_flag) { //如果南北向是绿灯
				bool temp_flag = car.next_up == "North" || car.next_up == "South" || \
					(car.up == "South" && car.next_up == "West") || (car.up == "North" && car.next_up == "East");
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
		if (car.y%unit_street == 0) { //在路口
			judge_wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			car.choose_direction();
			if (crossroads[car.x/unit_street][car.y/unit_street].M_light && !car.wait_flag) { //如果南北向是绿灯
				bool temp_flag = car.next_up == "North" || car.next_up == "South" || (car.up == "South" && car.next_up == "West");
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
				bool temp_flag = car.next_up == "East" || car.next_up == "West" || (car.up == "East" && car.next_up == "South");
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
		if (car.y%unit_street == 0) { //在路口
			judge_wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			car.choose_direction();
			if (crossroads[car.x/unit_street][car.y/unit_street].M_light && !car.wait_flag) { //如果南北向是绿灯
				bool temp_flag = car.next_up == "North" || car.next_up == "South" || (car.up == "North" && car.next_up == "East");
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
				bool temp_flag = car.next_up == "East" || car.next_up == "West" || (car.up == "West" && car.next_up == "North");
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
			bool temp_flag = car.next_up == "South" || (car.up == "North" && car.next_up == "East");
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
			bool temp_flag = car.next_up == "East" || (car.up == "West" && car.next_up == "North");
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
		cout << car.id << ":" << car.x << "\t" << car.y << endl;
		return true;
	}
	return false;
}

bool toyota_run(Car &car) {
	cout << "toyota\t" << car.x << "," << car.y << "\t" << car.up << "\t";
	if (car.wait_flag) {
		cout << "在排队：";
		Crossroad cross = crossroads[car.x / unit_street][car.y / unit_street];
		cout << "在队列中是第" << car.serial_num << "位" << "\t";
		cout << "南队" << cross.S_road.end() - cross.S_road.begin() << "\t" << cross.S_road.size() << "\t";
		cout << "北队" << cross.N_road.end() - cross.N_road.begin() << "\t" << cross.N_road.size() << "\t";
		cout << "东队" << cross.E_road.end() - cross.E_road.begin() << "\t" << cross.E_road.size() << "\t";
		cout << "西队" << cross.W_road.end() - cross.W_road.begin() << "\t" << cross.W_road.size() << "\t";
	}
	cout << endl;
	if (car.x < x_bound && car.y < y_bound) {
		if (car.x%unit_street == 0 && car.y%unit_street == 0) {
			cout << "南北灯" << crossroads[car.x / unit_street][car.y / unit_street].M_light << "\t";
			cout << "东西灯" << crossroads[car.x / unit_street][car.y / unit_street].W_light << endl;
			judge_wait(car, crossroads[car.x/unit_street][car.y/unit_street]);
			if (crossroads[car.x/unit_street][car.y/unit_street].M_light && !car.wait_flag) { //如果南北向是绿灯，向北走
				car.steer("North");
				car.straight();
			}
			else if (crossroads[car.x/unit_street][car.y/unit_street].W_light && !car.wait_flag) { //如果东西向是绿灯，向东走
				car.steer("East");
				car.straight();
			}
			else { //如果南北向与东西向都是红灯，等待
				if (car.up == "North" && !car.wait_flag) {
					car.steer("East");
					car.straight();
				}
				else {
					wait(car, crossroads[car.x / unit_street][car.y / unit_street]);
				}
			}
		}
		else {
			car.straight();
		}
	}
	else if (car.x == x_bound && car.y < y_bound) {
		car.steer("North"); //在右边界方向始终为朝北
		if (car.y%unit_street == 0) { //在路口
			cout << "南北灯" << crossroads[car.x / unit_street][car.y / unit_street].M_light << "\t";
			cout << "东西灯" << crossroads[car.x / unit_street][car.y / unit_street].W_light << endl;
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
		if (car.x%unit_street == 0) { //在路口
			cout << "南北灯" << crossroads[a][b].M_light << "\t";
			cout << "东西灯" << crossroads[a][b].W_light << endl;
			judge_wait(car, crossroads[a][b]); 
			if (car.up == "North" && !car.wait_flag) { //如果原方向是北，改向东行驶，不必等绿灯
				car.steer("East");
				car.straight();
			}
			else if (crossroads[a][b].W_light && !car.wait_flag) { //如果东西向是绿灯，向东走
				car.steer("East"); //在上边界方向始终朝东
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
	srand((unsigned int)(time(NULL)));
	for (int i = 0; i < 1000; i++) {
		//cout << "nissan29\t" << nissan[28].x << "," << nissan[28].y << nissan[28].next_up<< endl;
		for (int m = 0; m <= x_bound / unit_street; m++) {
			for (int n = 0; n <= y_bound / unit_street; n++) {
				crossroads[m][n].blink();
			}
		}
		flag = toyota_run(toyota);
		for (int j = 0; j < car_num; j++) {
			flag = flag || nissan_run(nissan[j]);
		}
		if (flag) {
			cout << "耗时" << i << "个单位时间。" << endl;
			break;
		}
		if (!flag && i == 999)
			cout << "测试汽车未能在规定时间到达终点。" << endl;
	}
}
