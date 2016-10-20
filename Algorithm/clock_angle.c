/*#include <stdio.h>

float calculate_angle(int hour, int minute)
{
	float hour_hand;
	float minute_hand;
	float angle;

	hour_hand = (hour * 30) + (minute * 0.5);
	minute_hand = minute * 6;
	
	if(hour_hand > minute_hand)
	{
		angle = hour_hand - minute_hand;
	}

	else
	{
		angle = minute_hand - hour_hand;
	}

	if(angle > 180)
	{
		angle = 360 - angle;
	}

	return angle;
}

int main()
{
	int hour;
	int minute;
	float angle;

	printf("hour : ");
	scanf("%d", &hour);
	printf("minute : ");
	scanf("%d", &minute);

	angle = calculate_angle(hour, minute);

	printf("hour = %d, minute = %d, angle = %.2f\n", hour, minute, angle);

	return 0;
}*/