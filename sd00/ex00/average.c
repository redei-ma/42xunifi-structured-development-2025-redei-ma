#include "average.h"

float average(const int *arr, int size)
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

/* int main(int ac, char **av)
{
	if (ac < 2)
	{
		return (1);
	}
	int arr[ac - 1];
	for (int i = 0; i < ac - 1; i++)
	{
		arr[i] = atoi(av[i + 1]);
	}
	float avg = average(arr, ac - 1);
	printf("Average: %.2f\n", avg);
	return (0);
} */
