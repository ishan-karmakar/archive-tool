cmake_minimum_required(VERSION 3.0)
project(ArchivingTool C)
add_executable(archiver
	src/archiver.c
	src/global.c
)
add_executable(unarchiver
	src/unarchiver.c
	src/global.c
)