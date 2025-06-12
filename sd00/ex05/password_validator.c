#include "password_validator.h"

static int	ft_strlen(const char *str)
{
	int len = 0;

	while (str[len] != '\0')
		len++;
	return (len);
}
static int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

static int	ft_islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

static int	ft_isspecial(int c)
{
	if (c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

PwStatus	validate_password(const char *new_pw, const char *curr_pw)
{
	bool	has_upper = false;
	bool	has_lower = false;
	bool	has_digit = false;
	bool	has_special = false;

	if (ft_strlen(new_pw) < 8)
		return (INVALID);
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
		return (INVALID);
	if (ft_strcmp(new_pw, curr_pw) == 0)
		return (INVALID);
	return (VALID);
}
