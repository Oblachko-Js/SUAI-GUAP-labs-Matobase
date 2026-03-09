#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAX_LENGTH = 100000;
const int MAX_SENTENCES = 4;

bool isSentenceEnd(char c)
{
    return c == '.' || c == '!' || c == '?';
}

int main()
{
    FILE* inputFile, * outputFile;
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    if (!inputFile || !outputFile)
    {
        printf("Ошибка открытия файлов.\n");
        return 1;
    }

    char sentences[MAX_SENTENCES][MAX_LENGTH];
    char sentence[MAX_LENGTH];

    int index = 0;
    int sentenceCount = 0;

    while (fgets(sentence, MAX_LENGTH, inputFile) && sentenceCount < MAX_SENTENCES)
    {
        char* end = std::find_if(sentence, sentence + strlen(sentence), isSentenceEnd);
        while (end != sentence + strlen(sentence) && sentenceCount < MAX_SENTENCES)
        {
            strncpy(sentences[index], sentence, end - sentence + 1);
            sentences[index][end - sentence + 1] = '\0';
            ++index;
            memmove(sentence, end + 1, strlen(end + 1) + 1);
            end = std::find_if(sentence, sentence + strlen(sentence), isSentenceEnd);
            ++sentenceCount;
        }
        if (strlen(sentence) > 0 && sentenceCount < MAX_SENTENCES)
        {
            strcpy(sentences[index], sentence);
            ++index;
            memset(sentence, 0, sizeof sentence);
            ++sentenceCount;
        }
    }

    for (int i = index - 1; i >= 0; --i)
    {
        fprintf(outputFile, "%s", sentences[i]);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
