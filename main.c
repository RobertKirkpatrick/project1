#include <check.h>
#include "dictionary.h"
#include <stdlib.h>

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_worlist.txt"

int main(int argc, char **argv) {
    hashmap_t hashtable[HASH_SIZE];
    char *misspelled[MAX_MISSPELLED];
    int i;
    char *filetest = argv[1];
    char *wordlist =argv[2];
    FILE* fp = fopen(filetest, "r");

    //int num_misspelled = check_words(text_file, hashtable, misspelled);
    load_dictionary(wordlist, hashtable);
    //printf("%d\n", success);
    //char *word2 = "semicolons";
    //bool test = check_word(word2, hashtable);
    //printf("%d\n", test);



    int miss = check_words(fp, hashtable, misspelled);
    printf("%d\n", miss);
    //FILE* fp2 = fopen("/home/rob/appsecurity/project1/a_tale_of_two_cities.txt", "r");
    //int miss = check_words(fp2, hashtable, misspelled);
    //printf("%d\n", miss);

    //check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[])
    //fclose(fp2);
    fclose(fp);
    for(i = 0; i< MAX_MISSPELLED; i++){
        if(misspelled[i] !=NULL){
            free(misspelled[i]);
        }
    }
    return 0;
}