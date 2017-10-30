/*
 Name: Quentin Truong
 Assignment 4. C programming and debugging
 
 ---
 
 Homework: Sorting encrypted text
 
 */

#include <stdio.h>
#include <stdlib.h>

// Tuple
struct tuple_words{
    char** words;
    unsigned long words_len;
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

// Wrapper for frobcmp b/c qsort needs const void *param
int cmp(const void *a, const void *b){
    return frobcmp(*((const char**) a), *((const char**) b));
}

// Exit if IO error
void check_io_err(FILE* ptr){
    if (ferror(ptr)){
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

// Read data from stdin
struct tuple_words read_stdin(){
    char* word = malloc(sizeof(char)); // array of chars (cstring)
    check_mem_err(word);
    char** words = malloc(sizeof(char*)); // aray of cstrings
    check_mem_err(words);
    
    unsigned long word_len = 0; // length of cstring
    unsigned long words_len = 0; // length of array of cstrings
    char curr = getchar();
    check_io_err(stdin);
    char prev = ' ';
    
    while (!feof(stdin)){ // keep going until file has ended
        if (curr == ' ' && prev == ' '){
            curr = getchar();
            check_io_err(stdin);
            continue;
        }
        else{
            word[word_len] = curr;
            word = realloc(word, (++word_len + 1) * sizeof(char) );
            check_mem_err(word);
            
            if (curr == ' '){
                words[words_len] = word;
                words = realloc(words, (++words_len + 1) * sizeof(char*));
                check_mem_err(words);
                
                word = malloc(sizeof(char));
                check_mem_err(word);
                word_len = 0;
            }
            
            char tmp = curr;
            curr = getchar();
            check_io_err(stdin);
            if (curr != EOF)
                prev = tmp;
        }
    }
    
    if (prev != ' '){
        word[word_len] = ' ';
        words[words_len] = word;
        ++words_len;
    }
    else{
        free(word);
    }
    
    struct tuple_words tup = {words, words_len};
    return tup;
}

// Output the words in unfrob'd order
void display(struct tuple_words tup){
    int words_pos = 0;
    for (; words_pos < tup.words_len; words_pos++){
        int word_pos = 0;
        while (tup.words[words_pos][word_pos] != ' '){
            printf("%c", tup.words[words_pos][word_pos]);
            word_pos++;
        }
        printf(" ");
    }
}

// Free all allocated memory
void dealloc(struct tuple_words tup){
    int i = 0;
    for (; i < tup.words_len; i++){
        free(tup.words[i]);
    }
    free(tup.words);
}

// Sort frob words from stdin; print frob words in their unfrob'd order to stdout
void sfrob(){
    struct tuple_words tup = read_stdin();
    
    qsort(tup.words, tup.words_len, sizeof(char*), cmp);
    
    display(tup);
    
    dealloc(tup);
}

int main(void)
{
    sfrob();
    exit(0);
}

