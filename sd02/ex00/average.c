#include "average.h"

static void	validator(int number, int *sum, int *validate)
{
	if (number >= 0 && number <= 100)
	{
		*sum += number;
		*validate += 1;
	}
	return ;
}

float	average(const int *arr, int size)
{
	float	sum;
	float	validate;
	float	average;

	sum = 0;
	validate = 0;
	for (int i = 0; i < size; i++)
		validator(arr[i], &sum, &validate);
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
