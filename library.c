#include "library.h"

#define BUF_SIZE 1024

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  int cmpstr(const char *p1, const char *p2)
 *  Description: Compare S1 and S2, returning less than, equal to or greater than zero
 *               if S1 is lexicographically less than, equal to or greater than S2.
 * =====================================================================================
 */
int cmpstr(const char *p1, const char *p2) {
    register const unsigned char *s1 = (const unsigned char *) p1;
    register const unsigned char *s2 = (const unsigned char *) p2;
    unsigned char c1, c2;

    do {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c1 == '\0') {
#ifdef  DEBUG
				printf("\ncmpstr 1 Reached termination of first string: %s %s\n", p1, p2);
#endif

            break;
        }
    } while (c1 == c2);

    return c1 - c2;
}
/* -----  end of function int cmpstr(const char *p1, const char *p2)  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  int copy_file(const char *path_from, const char *path_to) {
 *  Description: File copy function
 * =====================================================================================
 */
int copy_file(const char *path_from, const char *path_to, int word_amount) {
    char buf[MAX_STRING_LENGTH * word_amount];
    char *words[word_amount];

    for (int i = 0; i < word_amount; i++) {
        words[i] = buf + i * MAX_STRING_LENGTH;
    }

    if (read_file(path_from, words, word_amount) != 0) return 1;
    if (write_file(path_to, words, NULL, word_amount) != 0) return 2;

    return 0;
}
/* -----  end of function copy_file  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  merge_sort()
 *  Description:  Performs sort step of merge sort algorith. Each half must have the
 *                same number of elements
 *  array1:  	  first half of elements
 *  array2:  	  second half of elements
 *  n:            number of Strings in each halve
 *
 *  returns:      list of Strings sorted, firstly into each of the two input list arrays
 *                and secondly lower half in input array1 and second half in input array2
 * =====================================================================================*/
void merge_sort(const char *array1[], const char *array2[], int n) {
    // working area
    char *w_area[2 * n];

    int index_result = 0;
    int index_array1 = 0;
    int index_array2 = 0;
    int true_index = 0;
    while ((index_array1 < n && array1[index_array1] != NULL) && (index_array2 < n && array2[index_array2] != NULL)) {
        true_index++;
#ifdef  DEBUG
			printf("MS 1 While %s %s\n", array1[index_array1], array2[index_array2]);
#endif

        if (cmpstr((array1)[index_array1], array2[index_array2]) < 0) {
#ifdef DEBUG
				printf("MS 2 While: if\n");
#endif
            w_area[index_result++] = (array1)[index_array1++];
        } else {
#ifdef  DEBUG
				printf("MS 3 While: else\n");
#endif
            w_area[index_result++] = array2[index_array2++];
        }
    }

    if (array1[index_array1] == NULL) {
#ifdef DEBUG
			printf("MS 4 array1 ended prematurely\n");
#endif
        // nothing more to merge in ==> set to n so the NULL is not added to the result
        index_array1 = n;
    }
    if (array2[index_array2] == NULL) {
#ifdef DEBUG
			printf("MS 5 array2 ended prematurely\n");
#endif
        // nothing more to merge in ==> set to n so the NULL is not added to the result
        index_array2 = n;
    }

    for (int i = index_array1; i < n; i++) {
#ifdef  DEBUG
			printf("MS 6 1st for %s\n", array1[i]);
#endif
        true_index++;
        w_area[index_result++] = array1[i];
    }

    for (int j = index_array2; j < n; j++) {
#ifdef  DEBUG
			printf("MS 7 2nd for %s\n", array2[j]);
#endif
        true_index++;
        w_area[index_result++] = array2[j];
    }

    for (; true_index < 2 * n; true_index++) {
#ifdef  DEBUG
			printf("MS 8 3rd for %d\n", true_index);
#endif
        // set unused that arised from assymetrical merge to NULL
        w_area[true_index] = NULL;
    }

    //printf("WAREA %s %s \n", w_area[0], w_area[1]);


    for (int i = 0; i < n; i++) {
        array1[i] = w_area[i];
    }
    for (int i = 0; i < n; i++) {
        array2[i] = w_area[n + i];
    }

    //printf("HALVES %s %s\n", array1[0], array1[0]);
    return;
}
/* -----  end of function merge_sort()  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  write_file
 *  Description:  Writes output from merge_sort step to file
 *  Return less than zero upon failure
 * =====================================================================================
/write */
int write_file(const char *path, const char *elements1[], const char *elements2[], int n) {
    FILE *fptr;

    // Create a file]
    fptr = fopen(path, "w");
    if (fptr == NULL) {
        printf("Catastrophic error: could not open file for writing %s %s\n", path, strerror(errno));
        return 1;
    }

    if (elements1 != NULL) {
        for (int i = 0; i < n; i++) {
            if (elements1[i] == NULL) break;
            fputs(elements1[i], fptr);
            fputs("\n", fptr);
        }
    }
    if (elements2 != NULL) {
        for (int i = 0; i < n; i++) {
            if (elements2[i] == NULL) break;

            fputs(elements2[i], fptr);
            fputs("\n", fptr);
        }
    }
    fclose(fptr);

    return 0;
}
/* -----  end of function write_file  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  get_n_files
 *  Description: Returns first n files found
 *
 *      Returns: 0 upon success, -1 upon failure
 * =====================================================================================
 */
int get_n_files(const char *const folder_path, const char *file_ids[], int *n) {
    struct dirent *de; // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(folder_path);

    if (dr == NULL) // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory: %s\n", strerror(errno));
        return 1;
    }

    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    int index = 0;
    while ((de = readdir(dr)) != NULL) {
#ifdef DEBUG
        printf("GNF1 %s \n", de->d_name );
#endif
        if (strcmp(".", de->d_name) == 0 || strcmp("..", de->d_name) == 0 || strstr(de->d_name, "lock") != NULL)
            continue;

        strcpy(file_ids[index++], de->d_name);
        if (index == *n) break;
    }
    *n = index;

    closedir(dr);
    return 0;
}
/* -----  end of function get_n_files  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  get_lock
 *  Description: Attempts to mark a folder as locked for edit
 *
 *      Returns: 0 upon success, anything else upon failure
 * =====================================================================================
 */
int get_lock(char file_or_folder[40]) {

    struct stat stat_buf;
    char lock_file[MAX_FILE_LENGTH];
    concat_with_delim(file_or_folder, "lock", lock_file, "/");
    if (stat(lock_file, &stat_buf) == -1) {
        // not claimed ==> make dir and write lock file to claim it
        mkdir(file_or_folder, 0777);
        write_file(lock_file, NULL, NULL, 0);
        return 0;
    }

    time_t seconds = time(NULL);
    if (seconds - stat_buf.st_mtime > 1) {
        // pod working on this lock crashed ==> lock and finish it
        if (utime(lock_file, NULL) != 0) {
            // touch it so it locks again
            printf("Could not touch lock file %s\n", strerror(errno));
        }
        return 0;
    }
    return 1;
}
/* -----  end of function get_lock))  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  lock
 *  Description: Attempts to mark a folder for specified job_nr, round, lock base and folder
 *               The lock base is the first numeric file id of first file inside the lock.
 *               A lock is bordered by its base and the size (amount of files) of the lock
 *               added to the base.
 *
 *      Returns: 0 upon success, anything else upon failure
 * =====================================================================================
 */
int lock(const char *const job_nr, const char *round, const char *const lock_base, const char *folder) {
    struct stat stat_buf;
    char file_or_folder[MAX_FILE_LENGTH];

    concat_with_delim(folder, job_nr, file_or_folder, "/");

    if (stat(file_or_folder, &stat_buf) == -1) {
        if (mkdir(file_or_folder, 0777) == -1) {
            printf("Catastrophic error: could not create dir %s %s\n", file_or_folder, strerror(errno));
            return 1;
        };
    }

    concat_with_delim(file_or_folder, round, file_or_folder, "/");
    if (stat(file_or_folder, &stat_buf) == -1) {
        if (mkdir(file_or_folder, 0777) == -1) {
            printf("Catastrophic error: could not create dir %s %s\n", file_or_folder, strerror(errno));
            return 1;
        }
    }

    concat_with_delim(file_or_folder, lock_base, file_or_folder, "/");

    return get_lock(file_or_folder);
}
/* -----  end of function lock()  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  concat_with_delim
 *  Description: Concatenates two strings
 *
 *     string1
 *     string2
 *     destination
 *     delim
 *
 * =====================================================================================
 */
void concat_with_delim(const char *string1, const char *string2, char (*destination)[50], char *delim) {
    // char*  elements[words_to_read];
    char *index = *destination;
    strcpy(index, string1);
    index += strlen(*destination);
    strcpy(index, delim);
    index += 1;
    strcpy(index, string2);
}
/* -----  end of function concat_with_delim  ----- */

/*
 * /===  FUNCTION  ======================================================================
 *         Name:  read_file
 *  Description:  Reads input strings to sort
 * =====================================================================================
 */
int read_file(const char *path, const char *elements[], int record_amount) {
    char c;
    FILE *fptr = fopen(path, "r");
    // int fd = open(path, O_RDONLY);
    if (fptr == NULL) {
        printf("Catastrophic error: could not open file for reading %s %s\n", path, strerror(errno));
        return 1;
    }
    for (int i = 0; i < record_amount; i++) {
        if (fgets(elements[i], MAX_STRING_LENGTH, fptr) == NULL) break;
        elements[i] = strtok(elements[i], "\n");
        if (strlen(elements[i]) == 0) break;
    }

#ifdef DEBUG
    printf("RF Finished reading file\n");
#endif
    fclose(fptr);

    return 0;
}
/* -----  end of function read_file()  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  log2
 *  Description:  Calculates log2 of n
 * =====================================================================================
 */
int log2(int n) {
    int result = 0;
    while (n >>= 1) result++; // log2 is index in result array for the round
    return result;
}
/* -----  end of function log2  ----- */
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  replace_round
 *  Description:  Replaces round in file name, e.g. 3_2_3 -> 3_4_2 with parameter round = 2
 * =====================================================================================
 */
int replace_round(const char *file_name, const char *const new_round) {
#ifdef DEBUG
    printf("RR1 %s %s\n", file_name, new_round);
#endif
    int buf_size = 10;
    char job_nr[buf_size];
    char file_id[buf_size];

    char *index = strrchr(file_name, '/') + 1;

    strcpy(job_nr, strtok(index, "_"));
    strtok(NULL, "_");
    strcpy(file_id, strtok(NULL, "_"));

    concat_with_delim(job_nr, new_round, index, "_");
    concat_with_delim(index, file_id, index, "_");

#ifdef DEBUG
    printf("RR2 %s\n", file_name);
#endif
    return 0;
}
/* -----  end of function replace_round  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  extract_round
 *  Description:  Extracts round from file_name
 * =====================================================================================
 */
int extract_round(const char* file_name, char *p_round) {
#ifdef DEBUG
    printf("ER1 %s %s\n", file_name, p_round);
#endif
    char temp[strlen(file_name)];
    strcpy(temp, file_name);
    char* index = temp;
    if (strchr(index, '/') != NULL) {
        index = strrchr(temp, '/') + 1;
    }
    strtok(index, "_");
    strcpy(p_round, strtok(NULL, "_"));

#ifdef DEBUG
    printf("ER2 %s\n", p_round);
#endif
    return 0;
}
/* -----  end of function extract_round  ----- */
