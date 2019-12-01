#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"
#include <stdbool.h>
#include <string.h>


typedef node* hashmap_t;
// Hash table is an array of linked lists.
/*
 * Run istructions: ./spell_check a_tale_of_two_cities.txt wordlist.txt
 *
 * Your program should contain at least three functions, a function to load the list of words into the hash map (called load_dictionary), a function to check if a word is correctly spelled (called check_word), and a function called check_words to tie them all together. The parameter to check_words will be a file pointer containing lines of words separated by spaces, punctuation, etc. The function prototypes are as follows1:
 * 	int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[]);
 *	 bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]);
 * 	bool check_word(const char* word, hashmap_t hashtable[]);
*/

/**
 * Array misspelled is populated with words that are misspelled. Returns the length of misspelled.
 */
/**
 * Inputs:
 *  fp:         A file pointer to the document to check for spelling errors.
 *  hashtable:  The hash table used to determine spelling
 *  misspelled: An empty char* array to be populated with misspelled words.
 *              This array will never be greater than 1000 words long.
 *
 * Returns:
 *  int:        The number of words in the misspelled arary.
 *
 * Modifies:
 *  misspelled: This array will be filled with misspelled words.
 *
 * Example:
 *  int num_misspelled = check_words(text_file, hashtable, misspelled);
 **/

int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[])
{
    //Set int num_misspelled to 0.
    int num_misspelled = 0;
    char* word = calloc(LENGTH+ 1,sizeof(char));
    char* word_c = calloc(LENGTH+ 1,sizeof(char));
    char* word_lower = calloc(LENGTH+ 1,sizeof(char));
    char buffer[10];
    sprintf(buffer, "%%%is", LENGTH);

    if (fp == NULL) {
        printf("No file found");
        exit(0);
    }

    fscanf(fp,buffer,word);



    do{
        //While line in fp is not EOF (end of file):

        int i=0;
        int j=0;
        int a = strlen(word);
        /*if(word[a-1] =='\n'){
            word[a-1]='\0';

        }*/
        //clean up the word
        for(i=0; i<a+1; i++){
            if (isalpha(word[i])){
                word_c[j] = word[i];
                word_lower[j] = word[i];
                word_c[j+1]='\0';
                word_lower[j+1] ='\0';
;                j++;
            }
            else if ((ispunct(word[i])) && ( i < 1 || i == a-1)) { //skip character
                j++;
                //printf("punction is %c, word is %s \n", word[i], word);
            }
            else{
                word_c[j] = word[i];
                word_lower[j] = word[i];
                word_c[j+1]='\0';
                word_lower[j+1] ='\0';
                j++;
            }

            if (isupper(word[i]) && i==0) {
                word_lower[i] = tolower(word_lower[i]);
            }
            //printf("lowered word is %s \n", word_lower);
        }


        //Read the line.

        //printf("%s\n", word_c);

        //printf("lowered word is %s \n", word_lower);
        //printf("clean word is %s \n", word_c);
        //If not check_word(word):
        //append word to misspelled.
        //Increment num_misspelled.
        if(!check_word(word_c, hashtable)) {
            if(!check_word(word_lower, hashtable))
            {

                //printf("number misspelled is %i\n", num_misspelled);
                //printf("word is %s \n",word_lower);
                misspelled[num_misspelled] = calloc(LENGTH+ 1,sizeof(char));
                strcpy(misspelled[num_misspelled], word_lower);
                num_misspelled++;
                //printf("%i \n", num_misspelled);

            }
    }



    //fclose(fpr);
    /*for (i=0; i <num_misspelled;i++){
        printf("Misspelled[%i] is: %s", i, misspelled[i]);
    }*/

    }while(num_misspelled <MAX_MISSPELLED && fscanf(fp,buffer,word)==1);

    free(word);
    free(word_c);
    free(word_lower);
    return num_misspelled;
}

//function to check if a word is correctly spelled
bool check_word(const char* word, hashmap_t hashtable[])
{

    int a = strlen(word);
    //cleanup line read, make all characters 0 at the newline
    if(a > LENGTH){
        return false;
    }

    //Set int bucket to the output of hash_function(word).
    int bucket = hash_function(word);

    //Set hashmap_t cursor equal to hashmap[bucket]
    hashmap_t cursor = (node*) malloc(sizeof(node));
    cursor = hashtable[bucket];

    //While cursor is not NULL:
    if (cursor == NULL){
        return false;

    }else{
        //If word equals cursor->word:
        while(cursor != NULL ){

            if( (strcmp( cursor ->word, word)==0) ){
                //printf("cleaned word hit: %s \n", word_c);
                if(strcmp(cursor->word, word)==0){
                    //printf("lowered word hit: %s \n", word_lower);
                    return true;

                }

            }

            //Set cursor to cursor->next.*/
            cursor = cursor -> next;

        }
    }
    free(cursor);
    return false;


}

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {
    int bucket = 0;
    //Initialize all values in hash table to NULL.

    for (int i=0; i < HASH_SIZE;i++){
        hashtable[i] = NULL;

    }
    FILE* fp = fopen(dictionary_file, "r");

    if (fp == NULL) {
        printf("No file found");
        exit(0);
    }

    //Start reading in lines
    //initial character for line read
    //char *line = (char*) malloc(sizeof(char) * LENGTH);
    char* line = calloc(LENGTH+ 1,sizeof(char));

    while(fgets(line,LENGTH, fp) != NULL){
        // For each line, get the word
        //initialize char for cleaned up word
        //malloc new node
        hashmap_t new_node = (node*) malloc(sizeof(node));
        int len = strlen(line);
        //remove the new line character from using fgets//
        if(line[len-1] =='\n'){
            line[len-1]='\0';

        }

        new_node -> next = NULL;
        strncpy(new_node -> word, line, LENGTH);
        //printf("%s \n", new_node -> word );
        bucket = hash_function(line);

        if (hashtable[bucket] == NULL) //if there isn't a word, then add it and point to null
        {
            //new_node is assigned the word, and pointer next

            hashtable[bucket]= new_node;


        }else
        {

            //Add node to front of list
            new_node->next = hashtable[bucket];
            hashtable[bucket] = new_node;

            //hashtable[bucket]=curr;
            //printf("%s\n", hashtable[bucket]->word);
        }

    }

    free(line);
    fclose(fp);

    return true;
}