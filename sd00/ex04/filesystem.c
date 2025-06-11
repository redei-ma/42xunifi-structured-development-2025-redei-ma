#include "filesystem.h"

FSNode	*create_file(const char *name, int size)
{
	if (!name || size < 0)
		return NULL;
	FSNode *file = malloc(sizeof(FSNode));
	if (!file)
		return NULL;
	file->name = strdup(name);
	if (!file->name) {
		// free(file);
		return NULL;
	}
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
		return NULL;
	folder->name = strdup(name);
	if (!folder->name)
	{
		// free(folder);
		return NULL;
	}
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
		return NULL;
	return parent->child;
}

FSNode	*get_sibling(const FSNode *node)
{
	if (!node)
		return NULL;
	return (node->sibling);
}


/* void print_tree(FSNode *node, int level) {
    if (!node) return;
    
    // Stampa indentazione
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    
    // Stampa nome e info
    if (node->type == e_FOLDER) {
        printf("📁 %s/\n", node->name);
        // Stampa tutti i figli
        print_tree(node->child, level + 1);
    } else {
        printf("📄 %s (%d bytes)\n", node->name, node->size);
    }
    
    // Stampa i fratelli allo stesso livello
    print_tree(node->sibling, level);
}

// Funzione helper per liberare memoria
void free_tree(FSNode *node) {
    if (!node) return;
    
    // Libera ricorsivamente figli e fratelli
    free_tree(node->child);
    free_tree(node->sibling);
    
    // Libera il nodo corrente
    free(node->name);
    free(node);
}

int main() {
    printf("=== Test File System ===\n\n");
    
    // Creo la cartella root
    FSNode *root = create_folder("home");
    
    // Creo alcune cartelle principali
    FSNode *documents = create_folder("Documents");
    FSNode *downloads = create_folder("Downloads");
    FSNode *pictures = create_folder("Pictures");
    
    // Aggiungo le cartelle alla root
    add_child(root, documents);
    add_child(root, downloads);
    add_child(root, pictures);
    
    // === DOCUMENTS ===
    // Creo file in Documents
    FSNode *readme = create_file("README.txt", 1024);
    FSNode *report = create_file("report.pdf", 2048000);
    
    // Creo sottocartella Projects
    FSNode *projects = create_folder("Projects");
    add_child(documents, readme);
    add_child(documents, report);
    add_child(documents, projects);
    
    // File e cartelle in Projects
    FSNode *project1 = create_folder("FileSystem");
    FSNode *project2 = create_folder("Calculator");
    add_child(projects, project1);
    add_child(projects, project2);
    
    // File nel progetto FileSystem
    FSNode *filesystem_c = create_file("filesystem.c", 4096);
    FSNode *filesystem_h = create_file("filesystem.h", 1024);
    FSNode *main_c = create_file("main.c", 2048);
    add_child(project1, filesystem_c);
    add_child(project1, filesystem_h);
    add_child(project1, main_c);
    
    // File nel progetto Calculator
    FSNode *calc_c = create_file("calculator.c", 3072);
    FSNode *makefile = create_file("Makefile", 512);
    add_child(project2, calc_c);
    add_child(project2, makefile);
    
    // === DOWNLOADS ===
    FSNode *movie = create_file("movie.mp4", 1073741824); // 1GB
    FSNode *music = create_file("song.mp3", 5242880);     // 5MB
    FSNode *installer = create_file("setup.exe", 52428800); // 50MB
    add_child(downloads, movie);
    add_child(downloads, music);
    add_child(downloads, installer);
    
    // === PICTURES ===
    FSNode *vacation = create_folder("Vacation");
    FSNode *family = create_folder("Family");
    add_child(pictures, vacation);
    add_child(pictures, family);
    
    // Foto nelle cartelle
    FSNode *beach1 = create_file("beach1.jpg", 2097152); // 2MB
    FSNode *beach2 = create_file("beach2.jpg", 1572864); // 1.5MB
    add_child(vacation, beach1);
    add_child(vacation, beach2);
    
    FSNode *family_pic = create_file("family.jpg", 3145728); // 3MB
    add_child(family, family_pic);
    
    // Stampo l'albero completo
    printf("Struttura del File System:\n");
    printf("==========================\n");
    print_tree(root, 0);
    
    // Test delle funzioni
    printf("\n=== Test Funzioni ===\n");
    
    // Test get_children
    printf("\nFigli di Documents:\n");
    FSNode *child = get_children(documents);
    while (child) {
        printf("- %s", child->name);
        if (child->type == e_FILE) {
            printf(" (%d bytes)", child->size);
        }
        printf("\n");
        child = get_sibling(child);
    }
    
    // Test navigazione specifica
    printf("\nFile nel progetto FileSystem:\n");
    FSNode *fs_project = get_children(projects); // FileSystem è il primo figlio
    FSNode *fs_file = get_children(fs_project);
    while (fs_file) {
        printf("- %s (%d bytes)\n", fs_file->name, fs_file->size);
        fs_file = get_sibling(fs_file);
    }
    
    // Libero tutta la memoria
    free_tree(root);
    
    printf("\n✅ Test completato con successo!\n");
    return 0;
} */
