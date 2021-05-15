#include "utilities.h"

void delete_symb(char str[], int i){
    while (str[i] != '\0'){
        str[i] = str[i+1];
        i++;
    }
}