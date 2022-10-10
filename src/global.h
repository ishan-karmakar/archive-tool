#pragma once
#include <limits.h>
#include <stdint.h>

void error(char*);

extern const uint32_t
	ENTRY_NAME_SIZE,
	BLOCK_SIZE,
	DIRECTORY_NAME_OFFSET,
	FILE_COUNT_SIZE,
	FILE_COUNT_OFFSET,
	HEADER_SIZE,
	FILENAME_OFFSET,
	FILE_LENGTH_SIZE,
	FILE_LENGTH_OFFSET,
	FILE_HEADER_SIZE,
	FILE_CONTENT_OFFSET;

typedef struct {
	char* filename;
	char absolute_path[PATH_MAX + 256];
	uint32_t file_length;
} File;
