#include "first_last.h"

void	first_last(int arr[], int size, int target, int *first, int *last)
{
	int	i;

	i = 0;
	*first = -1;
	*last = -1;
	while (i < size)
	{
		if (arr[i] == target)
		{
			if (*first == -1)
				*first = i;
			*last = i;
		}
		i++;
	}
}
