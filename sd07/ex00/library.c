#include "library.h"

/* Display results usando la lista */
void	display_results(const char *query, int search_type, 
	t_result *results)
{
	char	*search_field;
	int		count;

	search_field = (search_type == 1) ? "title" : "author";
	ft_printfd(1, "\nSearch results for \"%s\" in %s:\n", query, search_field);
	ft_printfd(1, "=====================================\n");
	if (!results)
	{
		ft_printfd(1, "No books found.\n");
		return ;
	}
	count = 0;
	while (results)
	{
		ft_printfd(1, "ID: %d\n", results->book->id);
		ft_printfd(1, "Title: %s\n", results->book->title);
		ft_printfd(1, "Author: %s\n\n", results->book->author);
		results = results->next;
		count++;
	}
	ft_printfd(1, "Found %d books.\n", count);
}





/* Liberare memoria della lista risultati */
void free_results(t_result *results)
{
	t_result	*current;
	t_result	*next;
	
	current = results;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

/* Aggiungere un libro alla lista dei risultati */
int add_to_results(t_result **head, t_book *book)
{
	t_result	*new_node;
	
	new_node = malloc(sizeof(t_result));
	if (!new_node)
		return (0);
	
	new_node->book = book;
	new_node->next = *head;
	*head = new_node;
	return (1);
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

/* Search books e crea lista dei risultati */
t_result	*search_books(t_catalog catalog, const char *query, int search_type)
{
	int			i;
	t_result	*results;
	char		*haystack;

	results = NULL;
	i = 0;
	while (i < catalog.count)
	{
		haystack = (search_type == 1) ? catalog.books[i].title : 
			catalog.books[i].author;
		if (ft_strstr_ignore_case(haystack, query))
		{
			if (!add_to_results(&results, &catalog.books[i]))
			{
				free_results(results);
				return (NULL);
			}
		}
		i++;
	}
	return (results);
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
	if (!trimmed || ft_strlen(trimmed) == 0)
	{
		free(line);
		ft_printfd(1, "Error: empty search term\n");
		return (NULL);
	}
	free(line);
	return (trimmed);
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

int	get_request(int *search_type, char **query)
{
	*search_type = get_search_choice();
	*query = get_search_query();
	if (!*query)
	{
		ft_printfd(2, "Error: unable to read search query\n");
		return (0);
	}
	return (1);
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

/* Initialize catalog by allocating memory */
int	catalog_init(t_catalog *catalog)
{
	catalog->books = ft_calloc(MAX_BOOKS, sizeof(t_book));
	if (!catalog->books)
		return (0);
	catalog->count = 0;
	return (1);
}

int	load_catalog(t_catalog *catalog, char *CSV)
{
	if (!catalog_init(catalog))
	{
		ft_printfd(2, "Error: unable to initialize catalog\n");
		return (0);
	}
	if (!catalog_load_from_file(catalog, CSV))
	{
		ft_printfd(2, "Error: unable to load file %s\n", CSV);
		catalog_free(catalog);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_catalog	catalog;
	int			search_type;
	char		*query;
	t_result	*results;

	if (ac != 2)
	{
		ft_printfd(2, "Usage: %s <catalog_file>\n", av[0]);
		return (1);
	}
	if (!load_catalog(&catalog, av[1]))
	{
		ft_printfd(2, "Error: unable to load catalog\n");
		return (1);
	}
	if (!get_request(&search_type, &query))
	{
		ft_printfd(2, "Error: unable to read search query\n");
		catalog_free(&catalog);
		return (1);
	}
	results = search_books(catalog, query, search_type);
	display_results(query, search_type, results);
	free(query);
	free_results(results);
	catalog_free(&catalog);
	return (0);
}
