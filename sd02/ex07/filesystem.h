#ifndef FILESYSTEM_H
# define FILESYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef	enum
{
	e_FILE,
	e_FOLDER
}	FSNodeType;

typedef struct FSNode
{
	char			*name;		// Nome del file/cartella
	int				size;		// Dimensione (0 per le cartelle)
	FSNodeType		type;		// Tipo: FILE o FOLDER
	struct FSNode	*child;		// Puntatore al primo figlio
	struct FSNode	*sibling;	// Puntatore al fratello successivo
} FSNode;

FSNode	*create_file(const char *name, int size);
FSNode	*create_folder(const char *name);
void	add_child(FSNode *parent, FSNode *child);
FSNode	*get_children(const FSNode *parent);
FSNode	*get_sibling(const FSNode *node);

int		compute_total_size(FSNode *node);
void	print_structure(const FSNode *node, int indent);
void	free_filesystem(FSNode *node);

#endif