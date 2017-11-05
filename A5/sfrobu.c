/*
 Name: Quentin Truong
 Assignment 5. System call programming and debugging
 
 ---
 
 Homework: Sorting encrypted text
 
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Enum for malloc
enum malloc_type {one, multiple};

// Tuple
struct tuple_words{
    char** words;
    unsigned long words_len;
    enum malloc_type malloc;
    char* file_buffer;
};

// Decode/encode frob
char decode(char const *a){
    return (*a) ^ 42;
}

// Compare frob c strings
int frobcmp(char const *a, char const *b)
{
    while (1){
        if (*a == ' ' && *b == ' ')
            return 0;
        else if (*a == ' ' || (decode(a) < decode(b)))
            return -1;
        else if (*b == ' ' || (decode(a) > decode(b)))
            return 1;
        a++;
        b++;
    }
}

// Compare frob c strings
int frobcmp_insensitive(char const *a, char const *b)
{
    while (1){
        if (*a == ' ' && *b == ' ')
            return 0;
        else if (*a == ' ' || (toupper(decode(a)) < toupper(decode(b))))
            return -1;
        else if (*b == ' ' || (toupper(decode(a)) > toupper(decode(b))))
            return 1;
        a++;
        b++;
    }
}

// Wrapper for frobcmp b/c qsort needs const void *param
int cmp(const void *a, const void *b){
    return frobcmp(*((const char**) a), *((const char**) b));
}

// Wrapper for frobcmp b/c qsort needs const void *param
int cmp_insensitive(const void *a, const void *b){
    return frobcmp_insensitive(*((const char**) a), *((const char**) b));
}

// Exit if IO error
void check_io_err(ssize_t state){
    if (state < 0){
        fprintf(stderr, "IO Error");
        exit(1);
    }
}

// Exit if memory error
void check_mem_err(void* ptr)
{
    if (ptr == NULL){
        fprintf(stderr, "Memory Error");
        exit(1);
    }
}

// Output the words in unfrob'd order
void display(struct tuple_words tup){
    int words_pos = 0;
    for (; words_pos < tup.words_len; words_pos++){
        int word_pos = 0;
        while (tup.words[words_pos][word_pos] != ' '){
            write(1, &tup.words[words_pos][word_pos], 1);
            word_pos++;
        }
        char space[1];
        space[0] = ' ';
        write(1, space, 1);
    }
}

// Free all allocated memory
void dealloc(struct tuple_words tup){
    if (tup.malloc == one){
        free(tup.file_buffer);
    }
    else{
        int pos = 0;
        for (; pos < tup.words_len; pos++){
            free(tup.words[pos]);
        }
    }
    free(tup.words);
}

// Read from a regular file, so try to figure out the size and allocate all the memory at once
struct tuple_words read_reg_file(unsigned long size){
    char* file_buffer = malloc(sizeof(char) * size);
    check_mem_err(file_buffer);
    char** words = malloc(sizeof(char*)); // array of cstrings
    check_mem_err(words);
    
    unsigned long file_len = 0;
    unsigned long words_len = 0; // length of array of cstrings
    
    char curr[1];
    ssize_t state = read(0, curr, 1);
    check_io_err(state);
    while (state > 0){ // keep going until file has ended
        file_buffer[file_len] = curr[0];
        file_len++;
        
        if (file_len + 1 >= (size * sizeof(char))){
            file_buffer = realloc(file_buffer, (file_len + 2) * sizeof(char) );
        }
        state = read(0, curr, 1);
        check_io_err(state);
    }
    
    curr[0] = file_buffer[0];
    char prev[1] = {' '};
    int file_pos = 1;
    int word_start = 0;
    for (; file_pos < file_len; file_pos++){
        if (curr[0] == ' ' && prev[0] == ' '){
            curr[0] = file_buffer[file_pos];
            word_start = file_pos;
            continue;
        }
        else{
            if (curr[0] == ' '){
                words[words_len] = &file_buffer[word_start];
                words = realloc(words, (++words_len + 1) * sizeof(char*));
                
                word_start = file_pos;
            }
            
            char tmp[1];
            tmp[0] = curr[0];
            curr[0] = file_buffer[file_pos];
            if (file_pos != file_len){
                prev[0] = tmp[0];
            }
            
        }
    }
    if (prev[0] != ' '){
        file_buffer[file_len] = ' ';
        words[words_len] = &file_buffer[word_start];
        ++words_len;
    }
    
    struct tuple_words tup = {words, words_len, one, file_buffer};
    return tup;
}

// Read data from stdin
struct tuple_words read_stdin(){
    char* word = malloc(sizeof(char)); // array of chars (cstring)
    check_mem_err(word);
    char** words = malloc(sizeof(char*)); // aray of cstrings
    check_mem_err(words);
    
    unsigned long word_len = 0; // length of cstring
    unsigned long words_len = 0; // length of array of cstrings
    
    char curr[1];
    ssize_t state = read(0, curr, 1);
    check_io_err(state);
    char prev[1] = {' '};
    
    while (state > 0){ // keep going until file has ended
        if (curr[0] == ' ' && prev[0] == ' '){
            state = read(0, curr, 1);
            check_io_err(state);
            continue;
        }
        else{
            word[word_len] = curr[0];
            word = realloc(word, (++word_len + 1) * sizeof(char) );
            check_mem_err(word);
            
            if (curr[0] == ' '){
                words[words_len] = word;
                words = realloc(words, (++words_len + 1) * sizeof(char*));
                check_mem_err(words);
                
                word = malloc(sizeof(char));
                check_mem_err(word);
                word_len = 0;
            }
            
            char tmp[1];
            tmp[0] = curr[0];
            state = read(0, curr, 1);
            check_io_err(state);
            if (state > 0)
                prev[0] = tmp[0];
        }
    }
    if (prev[0] != ' '){
        word[word_len] = ' ';
        words[words_len] = word;
        ++words_len;
    }
    else{
        free(word);
    }
    
    struct tuple_words tup = {words, words_len, multiple, NULL};
    return tup;
}

struct tuple_words read_input(){
    struct tuple_words tup;
    struct stat file_stat;
    
    if (fstat(0, &file_stat) == 0 && S_ISREG(file_stat.st_mode)){
        tup = read_reg_file(file_stat.st_size);
    }
    else{
        tup = read_stdin();
    }
    return tup;
}

// Sort frob words from stdin; print frob words in their unfrob'd order to stdout
void sfrob(int flag){
    
    struct tuple_words tup = read_input();
    
    if (flag){
        qsort(tup.words, tup.words_len, sizeof(char*), cmp_insensitive);
    }
    else{
        qsort(tup.words, tup.words_len, sizeof(char*), cmp);
    }
    display(tup);
    
    dealloc(tup);
}

int read_args(int argc, const char* argv[]){
    if (argc >= 2 && strncmp(argv[1], "-f", 2) == 0){
        return 1;
    }
    return 0;
}

int main(int argc, const char* argv[])
{
    int flag = read_args(argc, argv);
    sfrob(flag);
    exit(0);
}

