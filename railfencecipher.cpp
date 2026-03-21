#include <stdio.h>
#include <string.h>

#define MAX 100

void createRailFence(char *text, int rails, char rail[][MAX]) {
    int len = strlen(text);
    int row = 0, dir_down = 0;

    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = ' ';

    for (int i = 0; i < len; i++) {
        rail[row][i] = text[i];

        if (row == 0)
            dir_down = 1;
        else if (row == rails - 1)
            dir_down = 0;

        row += dir_down ? 1 : -1;
    }
}

void printRailFence(char rail[][MAX], int rails, int len) {
    printf("\n========== Rail Fence Cipher ==========\n");

    for (int j = 0; j < len; j++)
        printf("*---");
    printf("+\n");

    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            printf("| %c ", rail[i][j]);
        }
        printf("|\n");

        for (int j = 0; j < len; j++)
            printf("*---");
        printf("*\n");
    }
}

void encrypt(char *text, int rails) {
    char rail[rails][MAX];
    int len = strlen(text);

    createRailFence(text, rails, rail);
    printRailFence(rail, rails, len);

    printf("\n Encrypted Message: ");
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] != ' ')
                printf("%c", rail[i][j]);
    printf("\n");
}

void decrypt(char *cipher, int rails) {
    int len = strlen(cipher);
    char rail[rails][MAX];
    int row = 0, dir_down, index = 0;

    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = ' ';

    for (int i = 0; i < len; i++) {
        if (row == 0)
            dir_down = 1;
        if (row == rails - 1)
            dir_down = 0;

        rail[row][i] = '*';
        row += dir_down ? 1 : -1;
    }

    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] == '*' && index < len)
                rail[i][j] = cipher[index++];

    printRailFence(rail, rails, len);

    printf("\n Decrypted Message: ");
    row = 0;
    for (int i = 0; i < len; i++) {
        if (row == 0)
            dir_down = 1;
        if (row == rails - 1)
            dir_down = 0;

        if (rail[row][i] != ' ')
            printf("%c", rail[row][i]);

        row += dir_down ? 1 : -1;
    }
    printf("\n");
}

int main() {
    char text[MAX], cipher[MAX];
    int rails;

    printf("\t****SANDEEP SHRESTHA****\n");
    printf("\t***Rail-Fence Cipher***\n\n");

    printf(" Enter the message : ");
    scanf("%s", text);

    printf(" Enter the number of rails: ");
    scanf("%d", &rails);

    encrypt(text, rails);

    printf("\n Enter the cipher text for decryption: ");
    scanf("%s", cipher);

    decrypt(cipher, rails);

    return 0;
}
