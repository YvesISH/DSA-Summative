#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void longestCommonSubstring(char *text1, char *text2) {
    int m = strlen(text1);
    int n = strlen(text2);
    int dp[MAX_LEN][MAX_LEN] = {0};
    int maxLen = 0, endingIndex = m;

    // Fill the dp array
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i-1] == text2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                if (dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                    endingIndex = i;
                }
            }
        }
    }

    // Construct the longest common substring
    char lcs[MAX_LEN];
    int index = 0;
    while (maxLen > 0) {
        lcs[index++] = text1[endingIndex - 1];
        maxLen--;
        endingIndex--;
    }
    lcs[index] = '\0';

    // Print the longest common substring
    printf("Longest common substring: %s\n", lcs);
}

int main() {
    char text1[] = "Similar";
    char text2[] = "Small";
    longestCommonSubstring(text1, text2);
    return 0;
}