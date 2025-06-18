#ifndef RECIPE_GENERATOR_H
# define RECIPE_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct
{
	char 	name[50];
	int		quantity; // in grams
}	Ingredients;

typedef struct
{
	char	flavor[50];
	int		intensity;
}	TasteProfile;

typedef struct
{
	char			title[100];
	char			description[256];
}	Recipe;

struct Ingredients	*get_current_ingredients(void);
struct TasteProfile	*get_user_taste_profile(void);
struct Recipe		*create_recipe(struct Ingredients *ingredients, struct TasteProfile *taste);
int					get_user_approval(struct Recipe *recipe);
void				free_ingredients(struct Ingredients *ing);
void				free_taste_profile(struct TasteProfile *tp);
void				free_recipe(struct Recipe *recipe);

struct Recipe		*create_custom_recipe(void);

#endif