#pragma once


class Main_cube
{
public:
	GLuint main_cube_sp[1];

	//변수
	int x = 0;
	int z = 0;

	int move_w = 0;
	int move_w_time = 0;
	int move_s = 0;
	int move_s_time = 0;
	int move_a = 0;
	int move_a_time = 0;
	int move_d = 0;
	int move_d_time = 0;

	int x_ro = 0;
	int z_ro = 0;
	
	int cookie_num = 0; //몇번째 배열에 쿠키를 생성할지
	int cookie_x[100];
	int cookie_z[100];
	int cookie_active[100];
	int cookie_time[100]; //시간이 다되면 쿠키가 사라짐

	int invisibl = 0;//투명상태

	//함수
	void draw();
	void cookie_draw();
	void cookie_make();
};