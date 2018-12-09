#pragma once

class Maps
{
public:
	GLuint map_sp[1];

	//변수
	int map[map_length][map_length];
	int map2[map_length][map_length];

	int tunnel_x[3];
	int tunnel_z[3];

	int fire_active[4];
	int fire_x[4];
	int fire_z[4];

	int key = 1;

	//함수
	void draw();
	void light_draw();
};