#include "workout_scheduler.h"

/*
*
* Returns a new UserData (mocked). Returns NULL on failure.
* struct UserData *get_user_data(char *username);
*
* Build a base WorkoutPlan from raw user data. Returns NULL on failure.
* struct WorkoutPlan *build_base_plan(struct UserData *data);
*
* Optionally refine an existing plan. Returns the same pointer (or a new one) or NULL on failure.
* struct WorkoutPlan *refine_plan(struct WorkoutPlan *plan, struct UserData *data);
*
* Determine how many days the workout schedule should span. Returns positive int, or <=0 on failure.
* int determine_duration(struct WorkoutPlan *plan);
*
* Assign daily exercises for the next day into the plan.
* void assign_daily_exercises(struct WorkoutPlan *plan, int day);
*
* Assign daily tips for the next day into the plan.
* void assign_daily_tips(struct WorkoutPlan *plan, int day);
*
* Free functions for cleanup.
* void free_user_data(struct UserData *data);
*
* void free_workout_plan(struct WorkoutPlan *plan);
*
*/

struct WorkoutPlan	*create_workout_schedule(char *username)
{
	struct UserData		*data;
	struct WorkoutPlan	*plan;
	int					duration;
	int					day;

	// Step 1: Get user data
	data = get_user_data(username);
	if (!data)
		return (NULL);

	// Step 2: Build base plan
	plan = build_base_plan(data);
	if (!plan)
	{
		free_user_data(data);
		return (NULL);
	}

	// Step 3: Refine plan (optional)
	plan = refine_plan(plan, data);
	if (!plan)
	{
		free_user_data(data);
		return (NULL);
	}

	// Step 4: Determine duration
	duration = determine_duration(plan);
	if (duration <= 0)
	{
		free_workout_plan(plan);
		free_user_data(data);
		return (NULL);
	}

	// Step 5: Assign daily content for each day
	day = 0;
	while (day < duration)
	{
		assign_daily_exercises(plan, day);
		assign_daily_tips(plan, day);
		day++;
	}

	// Step 6: Cleanup user data (no longer needed)
	free_user_data(data);
	
	return (plan);
}
