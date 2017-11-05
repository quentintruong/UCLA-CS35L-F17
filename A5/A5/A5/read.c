//
//  read.c
//  A5
//
//  Created by Quentin Truong on 11/3/17.
//  Copyright © 2017 QT. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// Enum for malloc
enum malloc_type {one, multiple};

// Tuple
struct tuple_words{
    char** words;
    unsigned long words_len;
    enum malloc_type malloc;
};

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
        free(tup.words[0]);
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
            word_start = file_pos + 1;
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
    printf("%c", prev[0]);
    if (prev[0] != ' '){
        file_buffer = realloc(file_buffer, (++file_len + 1) * sizeof(char));
        file_buffer[file_len] = ' ';
        words[words_len] = &file_buffer[word_start];
        ++words_len;
    }

    struct tuple_words tup = {words, words_len, one};
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
    
    struct tuple_words tup = {words, words_len, multiple};
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

int main(int argc, const char* argv[])
{
    struct tuple_words tup = read_input();
    
    display(tup);
    
    dealloc(tup);
}
