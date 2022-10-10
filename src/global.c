#include "global.h"
#include <stdio.h>
#include <stdlib.h>

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

const uint32_t ENTRY_NAME_SIZE = 64;
const uint32_t BLOCK_SIZE = 64;
const uint32_t DIRECTORY_NAME_OFFSET = 0;
const uint32_t FILE_COUNT_SIZE = sizeof(uint32_t);
const uint32_t FILE_COUNT_OFFSET = DIRECTORY_NAME_OFFSET + ENTRY_NAME_SIZE;
const uint32_t HEADER_SIZE = ENTRY_NAME_SIZE + FILE_COUNT_SIZE;

const uint32_t FILENAME_OFFSET = 0;
const uint32_t FILE_LENGTH_SIZE = sizeof(uint32_t);
const uint32_t FILE_LENGTH_OFFSET = FILENAME_OFFSET + ENTRY_NAME_SIZE;
const uint32_t FILE_HEADER_SIZE = ENTRY_NAME_SIZE + FILE_LENGTH_SIZE;
const uint32_t FILE_CONTENT_OFFSET = FILE_HEADER_SIZE;
