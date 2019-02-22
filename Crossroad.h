#pragma once
#include<vector>
#include"Car.h"

using namespace std;

constexpr int x_bound = 20;
constexpr int y_bound = 20;
constexpr int unit_street = 10; //�ֵ���λ������10

class Crossroad
{
public:
	int x; //·������
	int y;
	bool M_light = true; //�ϱ�������̵ƣ����ΪFalse���̵�ΪTrue
	bool W_light = !M_light; //����������̵�
	vector<Car> W_road = {};
	vector<Car> E_road = {};
	vector<Car> N_road = {};
	vector<Car> S_road = {};

	int light_flag = 0;
	void blink() { //���̵Ʊ任
		light_flag = light_flag % 11;
		if (light_flag < 5) {
			M_light = true;
			W_light = false;
		}
		else if (light_flag == 5) {
			M_light = false;
			W_light = false;
		}
		else {
			M_light = false;
			W_light = true;
		}
		light_flag++;
	}
};

Crossroad crossroads[x_bound%unit_street + 1][y_bound%unit_street + 1];

void init_crossroad() { //��ʼ��·��
	for (int i = 0; i <= x_bound % 10; i++) {
		for (int j = 0; j <= y_bound % 10; j++) {
			crossroads[i][j].x = i * 10;
			crossroads[i][j].y = j * 10;
		}
	}
}

