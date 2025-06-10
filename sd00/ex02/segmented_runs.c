/* 
* Find segment
* Check if is valid segment
*
*/

int	count_segments(const int *arr, int size)
{
	int	i = 0;
	int	start = 0;
	int	count = 0;

	while (i < size)
	{
		if (arr[i] == -1)
		{
			if (is_valid())//TODO
				count++;
			start = i;
		}
		i++;
	}
}
