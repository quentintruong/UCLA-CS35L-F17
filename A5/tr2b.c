/*
 Name: Quentin Truong
 Assignment 5. System call programming and debugging
 
 ---
 
 Laboratory: Buffered versus unbuffered I/O
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_dup(const char* from){
    unsigned long pos_a = 0;
    unsigned long pos_b = 1;
    unsigned long len = strlen(from);
    
    for (; pos_a < len; pos_a++){
        for (pos_b = pos_a + 1; pos_b < len; pos_b++){
            if (from[pos_a] == from[pos_b]){
                return 1;
            }
        }
    }
    return 0;
}

void validate(int argc, const char* argv[]){
    if (argc != 3){
        fprintf(stderr, "Incorrect number of arguments\n");
        exit(1);
    }
    if (strlen(argv[1]) != strlen(argv[2])){
        fprintf(stderr, "Args 'from' and 'to' are different lengths\n");
        exit(1);
    }
    if (find_dup(argv[1])){
        fprintf(stderr, "Duplicate characters in arg 'from'\n");
        exit(1);
    }
}

char sad_map(const char* from, const char* to, char letter){
    unsigned long pos = 0;
    unsigned long len = strlen(from);
    for (; pos < len; pos++){
        if (from[pos] == letter){
            return to[pos];
        }
    }
    return letter;
}

void check_io_err(FILE* p){
    if (ferror(p)){
        fprintf(stderr, "IO Error");
        exit(1);
    }
}

void transliterate(const char* from, const char* to){
    char curr = getchar();
    check_io_err(stdin);
    while (curr != EOF){
        putchar(sad_map(from, to, curr));
        check_io_err(stdout);
        
        curr = getchar();
        check_io_err(stdin);
    }
}


int main(int argc, const char* argv[]) {
    validate(argc, argv);
    transliterate(argv[1], argv[2]);
    
    exit(0);
}
