# Archiving tool in C
Made in October 2022 (7th grade)

## What is an archive?
An archive is a collection of files and metadata combined into one file.  

## Purpose
Many systems don't allow you to send directories, such as gmail. This tool was made so that you could turn directories into regular files and then convert it back into a directory on the other side.  
At the time, I was also interested in how compressors/archiving tools worked, so I decided to make a small implementation of one. This was the result.

## What is this?
This is like a stripped down version of tar. It is an archiving tool that takes in a directory of files and merges it into one file. This archiving tool also includes a tool to unarchive, which will take the archived file and split it into the directory and the separate files.

## How does it work?
### Archiver
The archiver works in the following steps:
- Write the directory name to the output file
- Iterate through each file in the directory
  - Write filename and file size to the output file
  - Write file data to output file
- Write number of files to output file

### Unarchiver
The unarchiver works in the following steps:
- Read the header from the input file
- Create the directory
- Read the number of files from the input file and iterate that many times
  - Read file header from the input file
  - Create output file
  - Read file data from the input file and write to output file
