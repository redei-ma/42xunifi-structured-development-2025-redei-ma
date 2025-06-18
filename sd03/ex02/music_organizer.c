#include "music_organizer.h"

/*
*
* Creates and returns a new music library. Returns NULL on fail
* struct MusicLibrary *create_music_library();
*
* Scans a directory for music files. Returns a NULL terminated array of filenames.
* const char **scan_directory(const char *directory_path);
*
* Processes a single music file. Returns a data structure representing the processed file.
* struct MusicFile *process_music_file(const char *directory_path, const char *filename);
*
* Updates the music library with the processed music file information.
* void update_music_library(struct MusicLibrary *library, struct MusicFile *song);
*
*/

struct MusicLibrary	*organize_music_library(const char *directory_path)
{
	struct MusicLibrary	*library;
	const char			**filenames;
	struct MusicFile	*song;

	library = create_music_library();
	if (!library)
	{
		printf("Failed to create music library.\n");
		return (NULL);
	}

	filenames = scan_directory(directory_path);
	if (!filenames)
	{
		printf("Failed to scan directory: %s\n", directory_path);
		free(library);
		return (NULL);
	}

	for (int i = 0; filenames[i] != NULL; i++)
	{
		song = process_music_file(directory_path, filenames[i]);
		if (!song)
		{
			printf("Failed to process file: %s\n", filenames[i]);
			continue ;
		}
		update_music_library(library, song);
	}

	free(filenames);

	if (library->count == 0)
	{
		printf("No music files found in the directory.\n");
		free(library);
		return (NULL);
	}

	return (library);
}
