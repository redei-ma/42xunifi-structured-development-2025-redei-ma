#include "filesystem.h"

int	compute_total_size(FSNode *node)
{
	int total_size = 0;

	if (!node)
		return (0);
	for (FSNode *tmp_node = node->child; tmp_node; tmp_node = tmp_node->sibling)
	{
		if (tmp_node->type == e_FILE)
			total_size += tmp_node->size;
		else if (tmp_node->type == e_FOLDER)
			total_size += compute_total_size(tmp_node);
	}
	return (total_size);
}

void	print_structure(const FSNode *node, int indent)
{
	if (!node)
		return ;
	for (int i = 0; i < indent; i++)
		printf("	");
	if (node->type == e_FILE)
		printf("📄 %s (%d bytes)\n", node->name, node->size);
	else
	{
		printf("📁 %s/\n", node->name);
		for (FSNode *tmp_node = node->child; tmp_node; tmp_node = tmp_node->sibling)
			print_structure(tmp_node, indent + 1);
	}
}

void	free_filesystem(FSNode *node)
{
	if (!node)
		return ;
	free(node->name);
	free_filesystem(node->child);
	free_filesystem(node->sibling);
	free(node);
}
