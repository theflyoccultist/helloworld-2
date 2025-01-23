// Double spacing a file means to insert a blank line between each line of text.

# include <stdio.h>
# include <stdlib.h>

void print_file(FILE *fptr) {
    int c;
    rewind(fptr);
    while ((c = getc(fptr)) != EOF) {
        putc(c, stdout);
    }
}

void double_space(FILE *ifp, FILE *ofp) {
    int c;
    rewind(ifp);
    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
        if (c == '\n') {
            putc('\n', ofp);
        }
    }
}

int main (int argc, char *argv[]) {
    FILE *ifp, *ofp;

    if (argc != 3) {
        fprintf(stderr, "Usage: <input file> <output file>\n");
        exit(1);
    }

    ifp = fopen(argv[1], "r");
    ofp = fopen(argv[2], "w");

    if (ifp == NULL || ofp == NULL) {
        fprintf(stderr, "Error opening files\n");
        exit(1);
    }

    printf("My input file is: %s\n", argv[1]);
    print_file(ifp);
    printf("\n");

    double_space(ifp, ofp);

    printf("My output file is: %s\n", argv[2]);
    print_file(ofp);
    printf("\n");

    fclose(ifp);
    fclose(ofp);

    return 0;
}