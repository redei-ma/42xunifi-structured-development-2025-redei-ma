#include "segmented_runs.h"

static int	is_valid(const int *arr, int start, int end)
{
	int	count = 0;

	if (start >= end)
		return (0);
	while (arr[start] == -1)
		start++;
	while (start < end)
	{
		if (arr[start] < arr[start + 1] && arr[start] != -1)
			count++;
		else
			count = 0;
		if (count > 1)
			return (1);
		start++;
	}
	return (0);
}

int	count_segments(const int *arr, int size)
{
	int	i = 0;
	int	start = 0;
	int	count = 0;

	while (i < size)
	{
		if (arr[i] == -1)
		{
			if (is_valid(arr, start, i))
				count++;
			start = i + 1;
		}
		i++;
	}
	if (start < size && is_valid(arr, start, size))
		count++;
	return (count);
}
