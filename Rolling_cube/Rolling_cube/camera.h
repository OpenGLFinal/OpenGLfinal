#pragma once

class Camera
{
public:
	//����
	int x = -9 * 180;
	int z = 8 * 180;
	int ro = 90;
	int ro_left = 0;
	int ro_right = 0;
	int ro_big = 0;
	

	//�Լ�
	void timer();
};