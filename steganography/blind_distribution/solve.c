#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <arpa/inet.h> 

// Fonction de comparaison pour qsort 
int compare_offsets(const void *a, const void *b);

int main(int argc, char ** argv) {
    srand(time(NULL));

    if(argc != 2) {
        printf("Usage : %s file\n", argv[0]);
        return -1;
    }
    
    FILE * file = fopen(argv[1], "rb+"); 
    if(file == NULL) {
        fprintf(stderr, "Erreur d'ouverture\n");
        return -1;
    }

    while(1) {
        unsigned char header[8];
        if (fread(header, 1, 8, file) != 8) break;

        size_t size = (header[0] << 24) | (header[1] << 16) | (header[2] << 8) | header[3];
        char *type = (char*)&header[4];

        // Route pour atteindre stco directement : b.goeswhere.com/ISO_IEC_14496-12_2015.pdf (brand isom)
        if (strncmp(type, "moov", 4) == 0) continue; 
        if (strncmp(type, "trak", 4) == 0) continue; 
        if (strncmp(type, "mdia", 4) == 0) continue; 
        if (strncmp(type, "minf", 4) == 0) continue; 
        if (strncmp(type, "stbl", 4) == 0) continue; 
        
        if (strncmp(type, "stco", 4) == 0) {
            unsigned char meta[8];
            fread(meta, 1, 8, file);
        
            uint32_t raw_count;
            memcpy(&raw_count, &meta[4], 4);
            size_t count = ntohl(raw_count); 
            // liste de tout les offset
            uint32_t *offsets = malloc(count * sizeof(uint32_t));
            fread(offsets, sizeof(uint32_t), count, file);

            // trie de la liste d'offset melanger 
            qsort(offsets, count, sizeof(uint32_t), compare_offsets);
        
            fseek(file, -(long)(count * sizeof(uint32_t)), SEEK_CUR);
            fwrite(offsets, sizeof(uint32_t), count, file);
            
            free(offsets);
            break; 
        }
        fseek(file, size - 8, SEEK_CUR);
    }
    fclose(file);
    return 0;
}

int compare_offsets(const void *a, const void *b) {
    unsigned int val_a = ntohl( *(unsigned int*)a );
    unsigned int val_b = ntohl( *(unsigned int*)b );
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}