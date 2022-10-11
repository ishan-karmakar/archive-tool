#include <fcntl.h> // O_RDONLY...
#include <stdlib.h> // NULL
#include <dirent.h> // DIR
#include <stdio.h> // printf
#include <string.h> // memcpy
#include <libgen.h> // basename
#include <unistd.h> // fseek
#include <errno.h>
#include "global.h"

const char* help = "\
compressor <directory name>\
";

void serialize_header(File* source, char* destination) {
	memcpy(destination + FILENAME_OFFSET, source->filename, strlen(source->filename) + 1);
	memcpy(destination + FILE_LENGTH_OFFSET, &(source->file_length), FILE_LENGTH_SIZE);
}
void serialize_file(int out_fd, uint32_t* offset, File* file) {
	printf("Adding file %s\n", file->absolute_path);
	int fd = open(file->absolute_path, O_RDONLY);
	if (fd == -1)
		error("Error opening file");
	uint32_t file_length = lseek(fd, 0, SEEK_END);
	printf("File length: %d\n", file_length);
	file->file_length = file_length;
	char* serialized_header = calloc(FILE_HEADER_SIZE, sizeof(char));
	serialize_header(file, serialized_header);
	lseek(out_fd, *offset, SEEK_SET);
	if (write(out_fd, serialized_header, FILE_HEADER_SIZE) == -1)
		error("Error writing to file");
	free(serialized_header);
	serialized_header = NULL;
	*offset += FILE_CONTENT_OFFSET;
	uint32_t blocks = file_length / BLOCK_SIZE;
	char* block = calloc(BLOCK_SIZE, sizeof(char));
	lseek(fd, 0, SEEK_SET);
	lseek(out_fd, *offset, SEEK_SET);
	for (uint32_t i = 0; i < blocks; i++) {
		if (read(fd, block, BLOCK_SIZE) == -1)
			error("Error reading file");
		printf("Block: %s\n", block);
		if (write(out_fd, block, BLOCK_SIZE) == -1)
			error("Error writing to file");
	}
	uint32_t additional_bytes = file_length % BLOCK_SIZE;
	if (additional_bytes > 0) {
		if (read(fd, block, additional_bytes) == -1)
			error("Error reading file");
		printf("Additional bytes (%d): %s\n", additional_bytes, block);
		if (write(out_fd, block, additional_bytes) == -1)
			error("Error writing to file");
	}
	free(block);
	block = NULL;
	if (close(fd) == -1)
		error("Error closing file");
}

int main(int argc, char* argv[]) {
	if (argc != 2)
		error("Not enough arguments");
	char* directory = argv[1];
	if (!strcmp(directory, "--help")) {
		printf("%s\n", help);
		exit(EXIT_SUCCESS);
	}
	DIR* d;
	struct dirent* dir;
	d = opendir(directory);
	if (ENOENT == errno)
		error("Directory does not exist");
	char* base_dir = calloc(ENTRY_NAME_SIZE, sizeof(char));
	char* base = basename(directory);
	memcpy(base_dir, base, strlen(base) + 1);
	char filename[strlen(base_dir) + 5];
	sprintf(filename, "%s.out", base_dir);
	int fd = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP);
	if (fd == -1)
		error("Error opening file");
	lseek(fd, DIRECTORY_NAME_OFFSET, SEEK_SET);
	if (write(fd, base_dir, ENTRY_NAME_SIZE) == -1)
		error("Error writing to file");
	free(base_dir);
	base_dir = NULL;
	uint32_t offset = HEADER_SIZE;
	uint32_t num_files = 0;
	while ((dir = readdir(d)) != NULL) {
		if (dir->d_type != DT_REG) continue;
		File file;
		file.filename = dir->d_name;
		sprintf(file.absolute_path, "%s/%s", directory, dir->d_name);
		serialize_file(fd, &offset, &file);
		offset += file.file_length;
		num_files++;
	}
	closedir(d);
	lseek(fd, FILE_COUNT_OFFSET, SEEK_SET);
	if (write(fd, &num_files, FILE_COUNT_SIZE) == -1)
		error("Error writing to file");
	if (close(fd) == -1)
		error("Error closing file");
	printf("Saved to %s\n", filename);
}
