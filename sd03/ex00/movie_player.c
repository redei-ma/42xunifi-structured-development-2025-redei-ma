#include "movie_player.h"

/* 
*	Returns user preferences. Returns NULL on failure.
*	struct Preferences *get_user_preferences(void);
*
*	Returns a list of movies matching the given preferences. Returns NULL on failure.
*	struct MovieList *find_movies(struct Preferences *prefs);
*
*	Returns a movie night plan from the given list. Returns NULL on failure.
*	struct Plan *build_plan(struct MovieList *list);
*/

struct Plan	*create_movie_night_plan(void)
{
	struct Preferences	*prefs;
	struct MovieList	*list;
	struct Plan			*plan;

	prefs = get_user_preferences();
	if (!prefs)
	{
		printf("Failed to get user preferences.\n");
		return (NULL);
	}
	list = find_movies(prefs);
	if (!list)
	{
		printf("Failed to find movies based on preferences.\n");
		return (NULL);
	}
	plan = build_plan(list);
	if (!plan)
	{
		printf("Failed to build movie night plan.\n");
		return (NULL);
	}
	return (plan);
}
