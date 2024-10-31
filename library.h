#ifndef MSFUNC_LIBRARY_H
#define MSFUNC_LIBRARY_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <utime.h>

// Maximum length of input words/elements
#define MAX_STRING_LENGTH 50

#if (defined(_WIN32) || defined(__WIN32__))
#define mkdir(A, B) mkdir(A)
#endif

// TODO following should go into config map
// Maximum length of files with merge steps
#define MAX_FILE_LENGTH 40

#define MAX_ROUND 10

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  read_file
 *  Description:  Reads input strings to sort
 * =====================================================================================
 */
int read_file(const char *path, const char *elements[], int record_amount);

void concat_with_delim(const char *folder_path, const char *file_name, char (*path)[50], char *delim);

int lock(const char *job_nr, const char* round, const char* lock_base, const char *folder);

int write_file (const char* path, const char *elements1[], const char *elements2[], int n);

int get_n_files (const char* const folder_path, const char* file_ids[], int *n);

int cmpstr(const char *p1, const char *p2);

void merge_sort(const char *array1[], const char *array2[], int n);

int copy_file(const char *path_from, const char *path_to, int word_amount);

int log2 (int n);

int replace_round (const char* file_name, const char* const new_round);

int extract_round(const char* file_name, char *p_round);

int get_lock(char file_or_folder[40]);

#endif //MSFUNC_LIBRARY_H
