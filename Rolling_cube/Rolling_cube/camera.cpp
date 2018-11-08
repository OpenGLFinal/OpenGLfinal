#include "basic.h"
#include "camera.h"

void Camera::timer()
{
	if (ro < 0)
		ro += 360;
	else if (ro > 270)
		ro -= 360;


	if (ro_left == 1)
	{
		if (ro_big != 0)
		{
			ro -= 5;
			ro_big -= 5;
		}
		else
		{
			ro_left = 0;
		}
	}

	if (ro_right == 1)
	{
		if (ro_big != 0)
		{
			ro += 5;
			ro_big -= 5;
		}
		else
		{
			ro_right = 0;
		}
	}
}