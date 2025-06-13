#ifndef PASSWORD_VALIDATOR_H
# define PASSWORD_VALIDATOR_H

#include <stdbool.h>
#include <string.h>

typedef enum
{
	VALID,
	INVALID_WEAK,
	INVALID_SIMILAR
} PwStatus;

typedef struct
{
	char	*history[3];	// Array of previous passwords
	int		last_index;	// Index of the last password
} PasswordHistory;



PwStatus	validate_password(const char *new_pw, PasswordHistory *history);

#endif