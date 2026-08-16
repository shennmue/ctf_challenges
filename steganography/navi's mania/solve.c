#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 


#define BUFFSIZE 1024

void unhide(FILE * file);


int main(int argc, char ** argv) {
    if(argc != 2) {
        printf("Usage : %s file\n", argv[0]);
        return -1;
    }
    
    FILE * file = fopen(argv[1], "rb+"); 
    if(file == NULL) {
        fprintf(stderr, "Erreur d'ouverture\n");
        return -1;
    }

    unhide(file);
    fclose(file);
    return 0;
}

void unhide(FILE * file){
    int free_cnt = 0;
    while(1) {
        unsigned char header[8];
        long current_pos = ftell(file); 

        if (fread(header, 1, 8, file) != 8) break; 
        size_t size = (header[0] << 24) | (header[1] << 16) | (header[2] << 8) | header[3];
        
        if (strncmp((char*)&header[4], "moov", 4) == 0) {
            continue; 
        }
        if(strncmp((char*)&header[4], "free", 4) == 0) {
            free_cnt++;
            if (free_cnt == 2) {
                unsigned char *buffer = malloc(size - 8);
                fseek(file, -(long)size, SEEK_END);
                fseek(file, 8, SEEK_CUR);

                fread(buffer, 1, size - 8, file);
                ftruncate(fileno(file), ftell(file) - size);

                fseek(file, current_pos, SEEK_SET);

                memcpy(&header[4], "trak", 4);
                fwrite(header, 1, 8, file);
                fwrite(buffer, 1, size - 8, file);
                
                free(buffer);
                break;
            }
            fseek(file, -(long)(size - 8), SEEK_CUR); 
        }
        fseek(file, size - 8, SEEK_CUR);
    }
}
