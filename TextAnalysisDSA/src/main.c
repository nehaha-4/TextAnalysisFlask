#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT 1000
#define MAX_WORDS 200
#define WORD_LEN 50

char text[MAX_TEXT];
char words[MAX_WORDS][WORD_LEN];
int freq[MAX_WORDS];
int wordCount = 0;

/* Clear input buffer */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Convert text to lowercase and remove punctuation */
void preprocess() {
    int i, j = 0;
    char clean[MAX_TEXT];

    for (i = 0; text[i]; i++) {
        if (isalnum((unsigned char)text[i]) || text[i] == ' ')
            clean[j++] = tolower(text[i]);
    }
    clean[j] = '\0';
    strcpy(text, clean);
}

/* Count frequency */
void countFrequency() {
    char temp[MAX_TEXT];
    strcpy(temp, text);

    char *tok = strtok(temp, " ");
    while (tok) {
        int found = 0;
        for (int i = 0; i < wordCount; i++) {
            if (strcmp(words[i], tok) == 0) {
                freq[i]++;
                found = 1;
                break;
            }
        }
        if (!found && wordCount < MAX_WORDS) {
            strcpy(words[wordCount], tok);
            freq[wordCount++] = 1;
        }
        tok = strtok(NULL, " ");
    }
}

/* Sort by frequency */
void sortByFrequency() {
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = i + 1; j < wordCount; j++) {
            if (freq[i] < freq[j]) {
                int tf = freq[i];
                freq[i] = freq[j];
                freq[j] = tf;

                char tw[WORD_LEN];
                strcpy(tw, words[i]);
                strcpy(words[i], words[j]);
                strcpy(words[j], tw);
            }
        }
    }
}

/* Show Top-K */
void showTopK() {
    int k;
    printf("Enter K value: ");

    if (scanf("%d", &k) != 1) {
        printf("Invalid input! Enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (k <= 0) return;
    if (k > wordCount) k = wordCount;

    printf("\nTop %d Frequent Words:\n", k);
    for (int i = 0; i < k; i++)
        printf("%s : %d\n", words[i], freq[i]);
}

/* Keyword search */
void keywordSearch() {
    char key[WORD_LEN];
    printf("Enter keyword to search: ");
    scanf("%s", key);
    clearInputBuffer();

    for (int i = 0; i < wordCount; i++) {
        if (strcmp(words[i], key) == 0) {
            printf("Keyword '%s' found %d times.\n", key, freq[i]);
            return;
        }
    }
    printf("Keyword '%s' not found.\n", key);
}

/* Read from file */
void readFromFile() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        printf("Could not open input.txt\n");
        return;
    }

    wordCount = 0;
    memset(freq, 0, sizeof(freq));

    fread(text, 1, MAX_TEXT - 1, fp);
    text[MAX_TEXT - 1] = '\0';
    fclose(fp);

    preprocess();
    countFrequency();
    sortByFrequency();

    printf("Text read from file successfully.\n");
}

int main() {
    int choice;

    do {
        printf("\n---- MENU ----\n");
        printf("1. Enter text manually\n");
        printf("2. Read text from file\n");
        printf("3. Show all word frequencies\n");
        printf("4. Show Top-K frequent words\n");
        printf("5. Search keyword\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                wordCount = 0;
                memset(freq, 0, sizeof(freq));
                printf("Enter text:\n");
                fgets(text, MAX_TEXT, stdin);
                preprocess();
                countFrequency();
                sortByFrequency();
                break;

            case 2:
                readFromFile();
                break;

            case 3:
                for (int i = 0; i < wordCount; i++)
                    printf("%s : %d\n", words[i], freq[i]);
                break;

            case 4:
                showTopK();
                break;

            case 5:
                keywordSearch();
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid option!\n");
        }
    } while (choice != 0);

    return 0;
}
