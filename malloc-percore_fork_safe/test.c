#include "malloc.h"
#include <string.h>
#include <stdio.h>

int main() {
        char *a;
        char b[] = "hello peepz";
        printf("String of size %ld:\n",strlen(b));
        
        a = malloc(sizeof(char)*strlen(b));
        strncpy(a, b, strlen(b));

        printf("%s\n", a);
        printf("%s\n", b);

        free(a);

        char *c;
        char d[] = "iz thiz workingz?";
        printf("String of size %ld:\n",strlen(b));
        c = malloc(sizeof(char)*strlen(d));
        strncpy(c, d, strlen(d));

        printf("%s\n", c);
        printf("%s\n", d);

        char e[] = "10 Home\n20 Sweet\n30 GOTO 10";
        printf("String of size %ld:\n",strlen(e));
        c = realloc(c, sizeof(char)*strlen(e));
        strncpy(c, e, strlen(e));
        c = realloc(c, sizeof(char)*strlen(e)-5);


        printf("%s\n", c);
        printf("%s\n", e);

        // Free everything
        free(c);


	return 0;
}
