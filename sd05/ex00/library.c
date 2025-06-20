#include "library.h"

/* Initialize catalog by allocating memory */
t_catalog	*catalog_init(void)
{
	t_catalog	*catalog;

	catalog = malloc(sizeof(t_catalog));
	if (!catalog)
		return (NULL);
	catalog->books = ft_calloc(MAX_BOOKS, sizeof(t_book));
	if (!catalog->books)
	{
		free(catalog);
		return (NULL);
	}
	catalog->count = 0;
	return (catalog);
}

/* Free all catalog memory */
void	catalog_free(t_catalog *catalog)
{
	int	i;

	if (!catalog)
		return;
	i = 0;
	while (i < catalog->count)
	{
		if (catalog->books[i].title)
			free(catalog->books[i].title);
		if (catalog->books[i].author)
			free(catalog->books[i].author);
		i++;
	}
	free(catalog->books);
	free(catalog);
}

/* Load books from CSV file using get_next_line */
int	catalog_load_from_file(t_catalog *catalog, const char *filename)
{
	int		fd;
	char	*line;
	int		success;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	success = 1;
	line = get_next_line(fd);
	while (line && catalog->count < MAX_BOOKS && success)
	{
		if (ft_strlen(line) > 0)
			success = parse_csv_line(line, catalog);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (success);
}

/* Parse CSV line and extract fields */
int	parse_csv_line(const char *line, t_catalog *catalog)
{
	char	*first_comma;
	char	*second_comma;
	int		id;
	int		title_len;
	char	*id_str;

	if (!line || !*line)
		return (1);
	first_comma = ft_strchr(line, ',');
	if (!first_comma)
		return (1);
	second_comma = ft_strchr(first_comma + 1, ',');
	if (!second_comma)
		return (1);
	id_str = ft_substr(line, 0, first_comma - line);
	if (!id_str)
		return (0);
	id = ft_natoi(id_str);
	free(id_str);
	if (id <= 0)
		return (1);
	title_len = second_comma - first_comma - 1;
	return (add_book_to_catalog(catalog, id, first_comma + 1, 
		second_comma + 1, title_len));
}

/* Add book to catalog */
int	add_book_to_catalog(t_catalog *catalog, int id, char *title_start, 
	char *author_start, int title_len)
{
	t_book	*book;
	char	*temp_title;

	if (catalog->count >= MAX_BOOKS)
		return (0);
	book = &catalog->books[catalog->count];
	book->id = id;
	temp_title = ft_substr(title_start, 0, title_len);
	if (!temp_title)
		return (0);
	book->title = ft_strtrim(temp_title, " \t\n\r");
	free(temp_title);
	if (!book->title)
		return (0);
	book->author = ft_strtrim(author_start, " \t\n\r");
	if (!book->author)
	{
		free(book->title);
		return (0);
	}
	catalog->count++;
	return (1);
}

/* Get search choice from user */
int	get_search_choice(void)
{
	char	*line;
	char	*trimmed;
	int		choice;
	int		valid_choice;

	valid_choice = 0;
	choice = 0;
	while (!valid_choice)
	{
		ft_printfd(1, "Choose search type:\n");
		ft_printfd(1, "1. Search by title\n");
		ft_printfd(1, "2. Search by author\n");
		ft_printfd(1, "Enter your choice (1 or 2): ");
		line = get_next_line(0);
		if (line)
		{
			trimmed = ft_strtrim(line, " \t\n\r");
			if (trimmed)
			{
				choice = ft_natoi(trimmed);
				free(trimmed);
			}
			free(line);
			if (choice == 1 || choice == 2)
				valid_choice = 1;
			else
				ft_printfd(1, "Invalid choice. Please try again.\n");
		}
	}
	return (choice);
}

/* Get search query from user */
char	*get_search_query(void)
{
	char	*line;
	char	*trimmed;

	ft_printfd(1, "Enter search term: ");
	line = get_next_line(0);
	if (!line)
		return (NULL);
	trimmed = ft_strtrim(line, " \t\n\r");
	free(line);
	return (trimmed);
}

/* Search books in catalog */
int	search_books(t_catalog *catalog, const char *query, int search_type)
{
	int		i;
	int		found;
	char	*haystack;

	if (!catalog || !query || ft_strlen(query) == 0)
		return (0);
	found = 0;
	i = 0;
	while (i < catalog->count)
	{
		haystack = (search_type == 1) ? catalog->books[i].title : 
			catalog->books[i].author;
		if (ft_strstr_ignore_case(haystack, query))
		{
			catalog->books[i].id = -catalog->books[i].id;
			found++;
		}
		i++;
	}
	return (found);
}

/* Case insensitive substring search */
int	ft_strstr_ignore_case(const char *haystack, const char *needle)
{
	int	i;
	int	j;
	int	match_found;

	if (!haystack || !needle)
		return (0);
	if (*needle == '\0')
		return (1);
	i = 0;
	match_found = 0;
	while (haystack[i] && !match_found)
	{
		j = 0;
		while (haystack[i + j] && needle[j] && 
			ft_tolower(haystack[i + j]) == ft_tolower(needle[j]))
			j++;
		if (needle[j] == '\0')
			match_found = 1;
		else
			i++;
	}
	return (match_found);
}

/* Display search results */
void	display_results(t_catalog *catalog, const char *query, int search_type)
{
	int		i;
	int		found_count;
	char	*search_field;

	search_field = (search_type == 1) ? "title" : "author";
	ft_printfd(1, "\nSearch results for \"%s\" in %s:\n", query, search_field);
	ft_printfd(1, "=====================================\n");
	found_count = 0;
	i = 0;
	while (i < catalog->count)
	{
		if (catalog->books[i].id < 0)
		{
			ft_printfd(1, "ID: %d\n", -catalog->books[i].id);
			ft_printfd(1, "Title: %s\n", catalog->books[i].title);
			ft_printfd(1, "Author: %s\n\n", catalog->books[i].author);
			catalog->books[i].id = -catalog->books[i].id;
			found_count++;
		}
		i++;
	}
	if (found_count == 0)
		ft_printfd(1, "No books found.\n");
	else
		ft_printfd(1, "Found %d books.\n", found_count);
}

/* Main function */
int	main(int argc, char **argv)
{
	t_catalog	*catalog;
	int			search_type;
	char		*query;

	if (argc != 2)
	{
		ft_printfd(2, "Usage: %s <catalog_file>\n", argv[0]);
		return (1);
	}
	catalog = catalog_init();
	if (!catalog)
	{
		ft_printfd(2, "Error: unable to initialize catalog\n");
		return (1);
	}
	if (!catalog_load_from_file(catalog, argv[1]))
	{
		ft_printfd(2, "Error: unable to load file %s\n", argv[1]);
		catalog_free(catalog);
		return (1);
	}
	ft_printfd(1, "Catalog loaded successfully (%d books)\n\n", catalog->count);
	search_type = get_search_choice();
	query = get_search_query();
	if (!query)
	{
		ft_printfd(2, "Error reading search query\n");
		catalog_free(catalog);
		return (1);
	}
	search_books(catalog, query, search_type);
	display_results(catalog, query, search_type);
	free(query);
	catalog_free(catalog);
	return (0);
}
