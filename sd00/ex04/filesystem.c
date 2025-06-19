#include "filesystem.h"

FSNode	*create_file(const char *name, int size)
{
	if (!name || size < 0)
		return (NULL);
	FSNode *file = malloc(sizeof(FSNode));
	if (!file)
		return (NULL);
	file->name = strdup(name);
	if (!file->name)
		return (NULL);
	file->size = size;
	file->type = e_FILE;
	file->child = NULL;
	file->sibling = NULL;
	return (file);
}

FSNode	*create_folder(const char *name)
{
	FSNode *folder = malloc(sizeof(FSNode));
	if (!folder)
		return (NULL);
	folder->name = strdup(name);
	if (!folder->name)
		return (NULL);
	folder->size = 0;
	folder->type = e_FOLDER;
	folder->child = NULL;
	folder->sibling = NULL;
	return (folder);
}

void	add_child(FSNode *parent, FSNode *child)
{
	if (!parent || parent->type != e_FOLDER || !child)
		return;
	if (!parent->child)
		parent->child = child;
	else
	{
		FSNode *tmp_sibling = parent->child;
		while (tmp_sibling->sibling)
			tmp_sibling = tmp_sibling->sibling;
		tmp_sibling->sibling = child;
	}
}

FSNode	*get_children(const FSNode *parent)
{
	if (!parent || parent->type != e_FOLDER)
		return (NULL);
	return (parent->child);
}

FSNode	*get_sibling(const FSNode *node)
{
	if (!node)
		return (NULL);
	return (node->sibling);
}
