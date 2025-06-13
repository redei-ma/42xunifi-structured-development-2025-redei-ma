#ifndef PLAYLIST_CREATOR_H
# define PLAYLIST_CREATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef enum {
    MOOD_HAPPY,
    MOOD_SAD,
    MOOD_ENERGETIC,
    MOOD_CALM,
    MOOD_ROMANTIC
} mood_type;

typedef enum {
    GENRE_POP,
    GENRE_ROCK,
    GENRE_JAZZ,
    GENRE_CLASSICAL,
    GENRE_ELECTRONIC
} genre_type;

typedef struct
{
	char		title[100];
	char		artist[100];
	int			duration; // Duration in seconds
	genre_type	genre; // Genre of the song
}	SongData;

typedef struct
{
	mood_type	mood; // User's mood
	int			energy_level; // 1 to 10 scale
	char		description[256]; // Additional notes about the mood
}	MoodSettings;

typedef struct
{
	char genre[50];
	int popularity; // 1 to 10 scale
}	FilterSettings;

typedef struct
{
	SongData *songs;
	int count;
}	Playlist;

struct MoodSettings		*analyze_user_mood(void);
struct FilterSettings	*default_filters(void);
int						get_mood_variations(struct MoodSettings *mood);
struct FilterSettings	*refine_filters(struct FilterSettings *current);
int						filters_require_popular_song(struct FilterSettings *filters);
struct SongData			*fetch_popular_song(void);
struct SongData			*fetch_niche_song(void);
struct Playlist			*combine_with_mood_playlist(struct SongData *song, struct MoodSettings *mood);
void					free_mood_settings(struct MoodSettings *mood);
void					free_filter_settings(struct FilterSettings *filters);
void					free_song_data(struct SongData *song);
void					free_playlist(struct Playlist *playlist);

struct Playlist			*create_playlist(void);

#endif