#define TABLE_H
#include <stdio.h>
#include <stdbool.h>

typedef struct {

    char *name;
    char *location;
    char *value;

} Product;

void initializeArrays(char**, char**, char**);
void initTable(Product*, char**, char**, char**);
int getInfoIndex(Product*, char*);
