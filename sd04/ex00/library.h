#ifndef LIBRARY_H
# define LIBRARY_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <ctype.h>

# define MAX_BOOKS 1000
# define MAX_LINE_LENGTH 1024

typedef struct s_book
{
	int			id;
	char		*title;
	char		*author;
}	t_book;

typedef struct s_catalog
{
	t_book		*books;
	int			count;
}	t_catalog;

t_catalog	*catalog_init(void);
void		catalog_free(t_catalog *catalog);
int			catalog_load_from_file(t_catalog *catalog, const char *filename);
int			parse_csv_line(const char *line, int *id, char **title, char **author);
int			search_books(t_catalog *catalog, const char *query, int search_type);
int			get_search_choice(void);
char		*get_search_query(void);
void		display_results(t_catalog *catalog, const char *query, int search_type);

#endif