#include "password_validator.h"

static int ft_min(int a, int b, int c)
{
	int min_val = a;
	if (b < min_val)
		min_val = b;
	if (c < min_val)
		min_val = c;
	return (min_val);
}

static int edit_distance(const char *s1, const char *s2)
{
	int len1 = ft_strlen(s1);
	int len2 = ft_strlen(s2);
	int dp[len1 + 1][len2 + 1];

	for (int i = 0; i <= len1; i++)
		dp[i][0] = i;
	for (int j = 0; j <= len2; j++)
		dp[0][j] = j;

	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			if (s1[i-1] == s2[j-1])
				dp[i][j] = dp[i-1][j-1];
			else
				dp[i][j] = 1 + ft_min(
					dp[i-1][j],
					dp[i][j-1],
					dp[i-1][j-1]
				);
		}
	}
	return dp[len1][len2];
}

static int ft_issimilar(const char *new_pw, PasswordHistory *history)
{
	for (int i = 0; i < 3; i++)
	{
		if (history->history[i] && history->history[i][0] != '\0')
		{
			if (edit_distance(new_pw, history->history[i]) <= 1)
				return (1);
		}
	}
	return (0);
}

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

	if (last_index >= 0 && !check_password(new_pw, history->history[last_index]))
		return (INVALID_WEAK);
	if (check_characters(new_pw) == 0)
		return (INVALID_WEAK);
	if (last_index >= 0 && ft_issimilar(new_pw, history))
		return (INVALID_SIMILAR);
	add_to_history(new_pw, history, last_index);
	return (VALID);
}
