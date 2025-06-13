#include "grade_map.h"

static void	first_mapper(const int *scores, int size, const char **mapped_grades)
{
	for (int i = 0; i < size; i++)
	{
		if (scores[i] < 0 || scores[i] > 100)
			mapped_grades[i] = "Invalid";
		else if (scores[i] >= 97)
			mapped_grades[i] = "A+";
		else if (scores[i] >= 93)
			mapped_grades[i] = "A";
		else if (scores[i] >= 90)
			mapped_grades[i] = "A-";
		else if (scores[i] >= 87)
			mapped_grades[i] = "B+";
		else if (scores[i] >= 83)
			mapped_grades[i] = "B";
		else if (scores[i] >= 80)
			mapped_grades[i] = "B-";
		else if (scores[i] >= 77)
			mapped_grades[i] = "C+";
		else if (scores[i] >= 73)
			mapped_grades[i] = "C";
		else if (scores[i] >= 70)
			mapped_grades[i] = "C-";
		else if (scores[i] >= 67)
			mapped_grades[i] = "D+";
		else if (scores[i] >= 63)
			mapped_grades[i] = "D";
		else if (scores[i] >= 60)
			mapped_grades[i] = "D-";
		else
			mapped_grades[i] = "F";
	}
}

static void	second_mapper(const int *scores, int size, const char **mapped_grades)
{
	for (int i = 0; i < size; i++)
	{
		if (scores[i] < 0 || scores[i] > 100)
			mapped_grades[i] = "Invalid";
		else if (scores[i] >= 60)
			mapped_grades[i] = "P";
		else
			mapped_grades[i] = "F";
	}
}

static void	third_mapper(const int *scores, int size, const char **mapped_grades)
{
	for (int i = 0; i < size; i++)
	{
		if (scores[i] < 0 || scores[i] > 100)
			mapped_grades[i] = "Invalid";
		else if (scores[i] >= 90)
			mapped_grades[i] = "A";
		else if (scores[i] >= 80)
			mapped_grades[i] = "B";
		else if (scores[i] >= 70)
			mapped_grades[i] = "C";
		else if (scores[i] >= 60)
			mapped_grades[i] = "D";
		else
			mapped_grades[i] = "F";
	}
}

void	map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades)
{
	if (mapper == XI1)
		first_mapper(scores, size, mapped_grades);
	else if (mapper == XI2)
		second_mapper(scores, size, mapped_grades);
	else if (mapper == XI3)
		third_mapper(scores, size, mapped_grades);
}
