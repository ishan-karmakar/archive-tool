#include "global.h"
#include <stdio.h>
#include <stdlib.h>

// Convenience function that prints error message and exits
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

// Directory name size
const uint32_t ENTRY_NAME_SIZE = 64;
// Block size
const uint32_t BLOCK_SIZE = 64;
// Directory name offset
const uint32_t DIRECTORY_NAME_OFFSET = 0;
// Number of files
const uint32_t FILE_COUNT_SIZE = sizeof(uint32_t);
// Number of files offset
const uint32_t FILE_COUNT_OFFSET = DIRECTORY_NAME_OFFSET + ENTRY_NAME_SIZE;
// Size of the entire header
const uint32_t HEADER_SIZE = ENTRY_NAME_SIZE + FILE_COUNT_SIZE;

// Filename offset
const uint32_t FILENAME_OFFSET = 0;
// Size of the file
const uint32_t FILE_LENGTH_SIZE = sizeof(uint32_t);
// Size of the file offset
const uint32_t FILE_LENGTH_OFFSET = FILENAME_OFFSET + ENTRY_NAME_SIZE;
// Size of the file header
const uint32_t FILE_HEADER_SIZE = ENTRY_NAME_SIZE + FILE_LENGTH_SIZE;
// Offset of file data
const uint32_t FILE_CONTENT_OFFSET = FILE_HEADER_SIZE;
