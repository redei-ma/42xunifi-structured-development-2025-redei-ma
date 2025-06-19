#ifndef PASSWORD_VALIDATOR_H
# define PASSWORD_VALIDATOR_H

# include <stdbool.h>
# include <string.h>

typedef enum
{
	VALID,
	INVALID_WEAK,
	INVALID_SIMILAR
} PwStatus;

typedef struct
{
	char	*history[3];	// Array of previous passwords
	int		last_index;		// Index of the last password in history (-1 if empty)
} PasswordHistory;


int			ft_strlen(const char *str);
int			ft_isupper(int c);
int			ft_islower(int c);
int			ft_isspecial(int c);
int			ft_isdigit(int c);
int			ft_strcmp(const char *s1, const char *s2);

PwStatus	validate_password(const char *new_pw, PasswordHistory *history);

#endif