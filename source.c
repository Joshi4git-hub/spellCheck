#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <ctype.h>  
  
#define LIMIT 1000  
#define LENGTH 50  
 
  
// Structure to store each word  
typedef struct Word {  
    char text[LENGTH];  
    struct Word *next;  
} Word;  
  
Word *dictTable[LIMIT] = {NULL};  
  
// Hash function (uses key * 31 + lowercase character)  
 
unsigned int generateKey(const char *text) {  
    unsigned int key = 0;  
    for (int i = 0; text[i]; i++) {  
        key = key * 31 + tolower(text[i]);  
    }  
    return key % LIMIT;  
}  
  
// Add a word to the dictionary hash table  
void storeWord(const char *text) {  
    unsigned int index = generateKey(text);  
    Word *entry = malloc(sizeof(Word));  
    strcpy(entry->text, text);  
    entry->next = dictTable[index];  
    dictTable[index] = entry;  
}  
  
// Check whether a word exists in the dictionary  
int verifyWord(const char *text) {  
    unsigned int index = generateKey(text);  
    Word *temp = dictTable[index];  
    while (temp) {  
        if (strcasecmp(temp->text, text) == 0)  
            return 1;  
        temp = temp->next;  
    }  
    return 0;  
}  
  
int main() {  
    FILE *file = fopen("dictionary.txt", "r");  
    if (!file) {  
        printf("Unable to open dictionary.txt file.\n");  
        return 1;    }  
  
    char buffer[LENGTH];  
    while (fgets(buffer, LENGTH, file)) {  
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline  
        storeWord(buffer);  
    }  
    fclose(file);  
  
    char input[LENGTH];  
    printf("Enter a word to verify: ");  
    scanf("%49s", input);  
    if (verifyWord(input))  
        printf("'%s' appears correctly spelled.\n", input);  
    else  
        printf("'%s' not found in dictionary records.\n",  
input);  
  
    return 0;}  
