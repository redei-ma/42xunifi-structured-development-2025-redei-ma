#ifndef MOVIE_PLAYER_H
# define MOVIE_PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef enum
{
	COMEDY,
	ACTION,
	DRAMA,
	HORROR,
	SCI_FI,
	ANIMATION
} Genre;

typedef struct Movie
{
	char	*title;			// Title of the movie
	Genre	genre;			// Genre of the movie
	int		duration;		// Duration of the movie in minutes
	char	*description;	// Description of the movie
}	Movie;

typedef struct Preferences
{
	char				*username;			// Username of the user
	Movie				**suggested_movie;	// Suggested movie based on preferences
	struct Preferences	*next;				// Pointer to the next preferences in the list
} Preferences;

typedef struct MovieList
{
	Movie	**movies;	// Array of pointers to movies
	int		*votes;		// Array of votes for each movie
} MovieList;

typedef struct Plan
{
	Movie	selected_movie;	// Movie selected for the night
	int		number_guests;	// Number of guests invited
}	Plan;

struct Preferences	*get_user_preferences(void);
struct MovieList	*find_movies(struct Preferences *prefs);
struct Plan			*build_plan(struct MovieList *list);

struct Plan			*create_movie_night_plan(void);

#endif