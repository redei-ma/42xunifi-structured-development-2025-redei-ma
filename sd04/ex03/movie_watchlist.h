#ifndef MOVIE_WATCHLIST_H
# define MOVIE_WATCHLIST_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# define MAX_MOVIES 10000
# define MAX_LINE_LENGTH 1024

# define MOVIE_NOT_WATCHED 0
# define MOVIE_WATCHED 1

typedef struct s_movie
{
	int		id;
	char	*title;
	char	*genre;
	int		year;
	float	rating;
	int		watched;
}	t_movie;

typedef struct s_watchlist
{
	t_movie	*movies;
	int		count;
	int		max_id;
	char	*filename;
}	t_watchlist;

t_watchlist		*watchlist_init(const char *filename);
void			watchlist_free(t_watchlist *watchlist);
void			free_movie(t_movie *movie);
int				watchlist_load_from_file(t_watchlist *watchlist);
int				watchlist_save_to_file(t_watchlist *watchlist);
int				parse_movie_line(const char *line, int *id, char **title, char **genre,
					int *year, float *rating, int *watched);
int				validate_movie(int id, const char *title, const char *genre,
					int year, float rating, int watched);
int				show_menu(void);
void			handle_menu_choice(t_watchlist *watchlist, int choice);

#endif