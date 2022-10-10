cmake_minimum_required(VERSION 3.0)
project(Compressor C)
add_executable(compressor
	src/compressor.c
	src/global.c
)
add_executable(decompressor
	src/decompressor.c
	src/global.c
)