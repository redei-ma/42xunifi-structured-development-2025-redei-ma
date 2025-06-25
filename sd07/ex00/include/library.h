#ifndef LIBRARY_H
# define LIBRARY_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <ctype.h>
# include "../libft/include/libft.h"

# define MAX_BOOKS 1000
# define MAX_LINE_LENGTH 1024

typedef struct s_book
{
	int			id;
	char		*title;
	char		*author;
}	t_book;

typedef struct	s_result
{
	t_book			*book;
	struct s_result	*next;
}	t_result;

typedef struct s_catalog
{
	t_book		*books;
	int			count;
}	t_catalog;

void	display_results(const char *query, int search_type, t_result *results);

/* Process request function */
void		free_results(t_result *results);
int			add_to_results(t_result **head, t_book *book);
int			ft_strstr_ignore_case(const char *haystack, const char *needle);
t_result	*search_books(t_catalog catalog, const char *query, int search_type);

/* User input functions */
char	*get_search_query(void);
int		get_search_choice(void);
int		get_request(int *search_type, char **query);

/* Catalog management functions */
void	catalog_free(t_catalog *catalog);
int		add_book_to_catalog(t_catalog *catalog, int id, char *title_start, 
			char *author_start, int title_len);
int		parse_csv_line(const char *line, t_catalog *catalog);
int		catalog_load_from_file(t_catalog *catalog, const char *filename);
int		catalog_init(t_catalog *catalog);
int		load_catalog(t_catalog *catalog, char *CSV);

#endif