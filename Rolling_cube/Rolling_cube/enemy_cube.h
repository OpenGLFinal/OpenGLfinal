#pragma once

class Enemy_cube
{
public:
	//변수
	int x = 0;
	int z = 0;

	int move_w = 0;
	int move_s = 0;
	int move_a = 0;
	int move_d = 0;
	int move_time = 0;

	int next_move = 0;

	int x_ro = 0;
	int z_ro = 0;


	//함수
	void draw();
};