#include "average.h"

float	average(const int *arr, int size)
{
	int		i;
	float	sum;
	float	validate;
	float	average;

	i = 0;
	sum = 0;
	validate = 0;
	while (i < size)
	{
		if (arr[i] >= 0 && arr[i] <= 100)
		{
			sum += arr[i];
			validate += 1;
		}
		i++;
	}
	if (validate == 0)
		return (0);
	average = sum / validate;
	return (average);
}
