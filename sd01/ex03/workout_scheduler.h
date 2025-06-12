#ifndef WORKOUT_SCHEDULER_H
# define WORKOUT_SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct UserData {
	char	*username;
	int		age;
	int		fitness_level;	// 1-5 scale
	char	*goal;			// e.g., "weight loss", "muscle gain", "endurance"
} UserData;

typedef struct WorkoutPlan {
	char	**exercises;	// Array of exercise names
	char	**tips;			// Array of tips for the user
	int		days;			// Number of days in the plan
} WorkoutPlan;

struct UserData		*get_user_data(char *username);
struct WorkoutPlan	*build_base_plan(struct UserData *data);
struct WorkoutPlan	*refine_plan(struct WorkoutPlan *plan, struct UserData *data);
int					determine_duration(struct WorkoutPlan *plan);
void				assign_daily_exercises(struct WorkoutPlan *plan, int day);
void				assign_daily_tips(struct WorkoutPlan *plan, int day);
void				free_user_data(struct UserData *data);
void				free_workout_plan(struct WorkoutPlan *plan);

struct WorkoutPlan	*create_workout_schedule(char *username);

#endif
