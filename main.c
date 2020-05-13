#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct data {
    float *float_array;
    int anz;
    char *filename;
};

FILE *open_file(char *filename, char *mode) {
    FILE *pfile = fopen(filename, mode);
    if (pfile == NULL) {
        perror("Failed to open file");
        return NULL;
    } else {
        printf("File '%s' opened successfully.\n", filename);
        return pfile;
    }
}

int close_file(FILE *pfile, char *filename) {
    if (!fclose(pfile)) {
        printf("File '%s' closed successfully.\n", filename);
        return 0;
    } else {
        perror("File was not closed successfully");
        return -1;
    }
}

struct data eingabe(int max, struct data eing) {

    float *werte = (float *) calloc((int) MAX, sizeof(float));
    float val = 0;
    unsigned i = 0;
    printf("Please enter floating point numbers:\n");
    while (i < MAX && scanf("%f", &val) == 1) {
        *(werte + i) = val;
        i++;
    }
    eing.anz = i;
    if(eing.anz > 0){
        printf("Captured floats are:\n");
        for (i = 0; i < eing.anz; i++) {
            printf("%d, %f\n", i + 1, *(werte + i));
        }
        eing.float_array = werte;
    }
    return eing;
}

int ausgabe(struct data eing) {
    if(eing.anz > 0){
        int err = 0;
        FILE *pfile = open_file(eing.filename, "wb");
        if (pfile != NULL) {
            long count = fwrite(eing.float_array, sizeof(float), eing.anz, pfile);
            if (!count) {
                printf("Writing to file %s was not successful.\n", eing.filename);

                err = 1;
            } else {
                err = 0;
                printf("Wrote %u floats to '%s'\n", count, eing.filename);
            }
        }
        if (!err) {
            close_file(pfile, eing.filename);
            return 0;
        } else {
            return -1;
        }
    }
    else{
        printf("Invalid data was entered or no data was captured. Exiting.\n");
        return -1;
    }
}

int main() {
    struct data eing;

    eing.filename = "messung.bin";

    if (!ausgabe(eingabe((int) MAX, eing))) {
        return 0;
    } else {
        return -1;
    }
}
