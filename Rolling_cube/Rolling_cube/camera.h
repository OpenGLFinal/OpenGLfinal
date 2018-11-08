#pragma once

class Camera
{
public:
	//변수
	int x = 0;
	int z = 0;
	int ro = 90;
	int ro_left = 0;
	int ro_right = 0;
	int ro_big = 0;
	

	//함수
	void timer();
};