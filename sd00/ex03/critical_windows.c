#include "critical_windows.h"

static int	validate_windows(const int *readings, int start, int end)
{
	int	sum = 0;
	int	critical_reading = 0;

	for (int i = start; i <= end; i++)
	{
		if (readings[i] > 150)
			return (0);
		else if (readings[i] >= 70)
			critical_reading++;
		sum += readings[i];
	}
	if (critical_reading < 3 || sum / 5 < 90)
		return (0);
	return (1);
}

int	count_critical_windows(const int *readings, int size)
{
	int	count = 0;

	if (size < 5)
		return (0);
	for (int i = 0; i <= size - 5; i++)
	{
		if (validate_windows(readings, i, i + 4))
			count++;
	}
	return (count);
}
