#include "password_validator.h"

static int	ft_issimilar(const char *new_pw, struct PasswordHistory *history)
{}

static void	add_to_history(const char *new_pw, PasswordHistory *history, int last_index)
{
	if (last_index == 2)
	{
		strncpy(history->history[0], new_pw, ft_strlen(new_pw) + 1);
		history->last_index = 0;
	}
	else
	{
		strncpy(history->history[last_index + 1], new_pw, ft_strlen(new_pw) + 1);
		history->last_index++;
	}
}

PwStatus	validate_password(const char *new_pw, PasswordHistory *history)
{
	bool	has_upper = false;
	bool	has_lower = false;
	bool	has_digit = false;
	bool	has_special = false;
	bool	is_similar = false;
	int		last_index = history->last_index;

	if (ft_strlen(new_pw) < 8)
		return (INVALID_WEAK);
	for (int i = 0; new_pw[i] != '\0'; i++)
	{
		if (ft_isupper(new_pw[i]))
			has_upper = true;
		else if (ft_islower(new_pw[i]))
			has_lower = true;
		else if (ft_isdigit(new_pw[i]))
			has_digit = true;
		else if (ft_isspecial(new_pw[i]))
			has_special = true;
	}
	if (!has_upper || !has_lower || !has_digit || !has_special)
		return (INVALID_WEAK);
	if (last_index < 0)
	{
		add_to_history(new_pw, history, -1);
		return (VALID);
	}
	if (history->history[last_index] && ft_strcmp(new_pw, history->history[last_index]) == 0)
		return (INVALID_WEAK);
	if (ft_issimilar(new_pw, history))
		return (INVALID_SIMILAR);
	add_to_history(new_pw, history, last_index);
	return (VALID);
}
