#ifndef EXPENSE_TRACKER_H
# define EXPENSE_TRACKER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX_EXPENSES 10000

typedef struct s_date
{
	int		year;
	int		month;
	int		day;
}	t_date;

typedef struct s_transaction
{
	t_date	date;
	char	*category;
	double	amount;
	char	*description;
}	t_transaction;

typedef struct s_wallet
{
	t_transaction	*transactions;
	int				count;
	double			total_amount;
}	t_wallet;

t_wallet			*wallet_init(void);
int					wallet_load_from_file(t_wallet *wallet, const char *filename);
int					parse_transaction_line(const char *line, t_date *date, char **category, 
						double *amount, char **description);
int					parse_date(const char *date_str, t_date *date);
void				display_summary(t_wallet *wallet);
void				free_transaction(t_transaction *transaction);
void				wallet_free(t_wallet *wallet);

#endif