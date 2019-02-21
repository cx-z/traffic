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
	bool W_light = true; //����������̵�
	vector<Car> W_road = {};
	vector<Car> E_road = {};
	vector<Car> N_road = {};
	vector<Car> S_road = {};
};

Crossroad crossroads[3][3];

void init_crossroad() { //��ʼ��·��
	for (int i = 0; i <= x_bound % 10; i++) {
		for (int j = 0; j <= y_bound % 10; j++) {
			crossroads[i][j].x = i * 10;
			crossroads[i][j].y = j * 10;
		}
	}
}

