#include <check.h>
#include "dictionary.h"
#include <stdlib.h>

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_worlist.txt"
#define EMPTY "empty.txt"
#define NOFILE "thisisnotafile.txt"
#define TALE "a_tale_of_two_cities.txt"
#define LONG "test3.txt"

START_TEST(test_dictionary_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(load_dictionary(TESTDICT, hashtable));
    // Here we can test if certain words ended up in certain buckets
    // to ensure that our load_dictionary works as intended. I leave
    // this as an exercise.
    char* expected[4];
    expected[0] = "first";
    expected[1] = "second";
    expected[2] = "third";
    expected[3] = "test";
    ck_assert_msg(strcmp(hashtable[0]->word, expected[0]) == 0);
    ck_assert_msg(strcmp(hashtable[1]->word, expected[1]) == 0);
    ck_assert_msg(strcmp(hashtable[2]->word, expected[2]) == 0);
    ck_assert_msg(strcmp(hashtable[3]->word, expected[3]) == 0);
    //free(hashtable);
}
END_TEST

START_TEST(test_check_word_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "Justice";
    const char* punctuation_word_2 = "pl.ace";
    const char* questionmark1 ="?Justice";
    const char* questionmark2 ="?Justice?";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(punctuation_word_2, hashtable));
    // Test here: What if a word begins and ends with "?
    ck_assert(!check_word(questionmark1, hashtable));
    ck_assert(!check_word(questionmark2, hashtable));

}
END_TEST

START_TEST(test_dictionary_empty)
    {
        hashmap_t hashtable[HASH_SIZE];
        ck_assert(load_dictionary(TESTDICT, hashtable));


    }
END_TEST

START_TEST(test_dictionary_nofile)
    {
        hashmap_t hashtable[HASH_SIZE];
        ck_assert(load_dictionary(NOFILE, hashtable));


    }
END_TEST

START_TEST(test_check_words_maxmisspelled)
    {
        hashmap_t hashtable[HASH_SIZE];
        load_dictionary(DICTIONARY, hashtable);
        char *misspelled[MAX_MISSPELLED];
        FILE *fp = fopen("a_tale_of_two_cities.txt", "r");
        int num_misspelled = check_words(fp, hashtable, misspelled);

        ck_assert(num_misspelled == MAX_MISSPELLED);

    }
END_TEST

START_TEST(test_check_words_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char* expected[3];
    expected[0] = "sogn";
    expected[1] = "skyn";
    expected[2] = "betta";
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("test1.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 3);
    bool test = strlen(misspelled[0]) == strlen(expected[0]);
    int len1 = strlen(misspelled[0]);
    int len2 = strlen(expected[0]);
    printf("test of length %d!=%d", len1, len2);
    ck_assert_msg(test, "%d!=%d", len1, len2);
    ck_assert_msg(strcmp(misspelled[0], expected[0]) == 0);
    ck_assert_msg(strcmp(misspelled[1], expected[1]) == 0);
    ck_assert_msg(strcmp(misspelled[2], expected[2]) == 0);
}
END_TEST

START_TEST(test_check_words_BO)
    {
        hashmap_t hashtable[HASH_SIZE];
        load_dictionary(TALE, hashtable);

        char *misspelled[MAX_MISSPELLED];
        FILE *fp = fopen("test2.txt", "r");
        int num_misspelled = check_words(fp, hashtable, misspelled);
        ck_assert(num_misspelled == 1);

    }
END_TEST

START_TEST(test_check_words_long)
    {
        hashmap_t hashtable[HASH_SIZE];
        load_dictionary(LONG, hashtable);

        char *misspelled[MAX_MISSPELLED];
        FILE *fp = fopen("test3.txt", "r");
        int num_misspelled = check_words(fp, hashtable, misspelled);
        ck_assert(num_misspelled == 0);

    }
END_TEST

Suite *
check_word_suite(void)
{
    Suite * suite;
    TCase * check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    tcase_add_test(check_word_case, test_check_word_normal);
    tcase_add_test(check_word_case, test_check_words_normal);
    tcase_add_test(check_word_case, test_dictionary_empty);
    tcase_add_test(check_word_case, test_dictionary_nofile);
    tcase_add_test(check_word_case, test_check_words_maxmisspelled);
    tcase_add_test(check_word_case, test_check_words_BO);
    tcase_add_test(check_word_case, test_check_words_long);
    suite_add_tcase(suite, check_word_case);

    return suite;
}

int
main(void)
{
    int failed;
    Suite *suite;
    SRunner *runner;
    
    suite = check_word_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

