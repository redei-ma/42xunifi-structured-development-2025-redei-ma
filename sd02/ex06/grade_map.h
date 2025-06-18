#ifndef GRADE_MAP_H
# define GRADE_MAP_H

typedef	enum
{
	XI1,
	XI2,
	XI3
} GradeMapper;

void	map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades);

#endif