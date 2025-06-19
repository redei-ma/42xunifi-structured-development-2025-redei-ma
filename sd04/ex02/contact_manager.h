#ifndef CONTACT_MANAGER_H
# define CONTACT_MANAGER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# define MAX_CONTACTS 10000
# define MAX_LINE_LENGTH 1024

typedef struct s_contact
{
	int		id;
	char	*name;
	char	*phone;
	char	*email;
	char	*city;
	char	*address;
}	t_contact;

typedef struct s_contact_manager
{
	t_contact	*contacts;
	int			count;
	int			max_id;
	char		*filename;
}	t_contact_manager;

t_contact_manager	*manager_init(const char *filename);
void				manager_free(t_contact_manager *manager);
void				free_contact(t_contact *contact);
int					manager_load_from_file(t_contact_manager *manager);
int					manager_save_to_file(t_contact_manager *manager);
int					parse_contact_line(const char *line, int *id, char **name, char **phone, 
						char **email, char **city, char **address);
int					validate_contact(int id, const char *name, const char *phone, 
						const char *email, const char *city);
int					show_menu(void);
void				handle_menu_choice(t_contact_manager *manager, int choice);

#endif