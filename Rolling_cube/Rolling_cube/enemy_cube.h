#pragma once

class Enemy_cube
{
public:
	//����
	int x = 180 * 8;
	int z = 180 * -9;

	int light_x = 180 * 8;
	int light_z = 180 * -9;

	int move_w = 0;
	int move_s = 0;
	int move_a = 0;
	int move_d = 0;
	int move_time = 0;

	int next_move = 0;

	int x_ro = 0;
	int z_ro = 0;


	//�Լ�
	void draw();
	void light_draw();
};