#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

const int MAX_SENTENCES = 3;

bool isSentenceEnd(char c)
{
    return c == '.' || c == '!' || c == '?';
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        std::cout << "Ошибка открытия файлов." << std::endl;
        return 1;
    }

    std::string sentences[MAX_SENTENCES];
    std::string sentence;

    int index = 0;
    int sentenceCount = 0;

    while (std::getline(inputFile, sentence) && sentenceCount < MAX_SENTENCES)
    {
        auto end = std::find_if(sentence.begin(), sentence.end(), isSentenceEnd);
        while (end != sentence.end() && sentenceCount < MAX_SENTENCES)
        {
            sentences[index] = sentence.substr(0, std::distance(sentence.begin(), end) + 1);
            ++index;
            sentence = sentence.substr(std::distance(sentence.begin(), end) + 1);
            end = std::find_if(sentence.begin(), sentence.end(), isSentenceEnd);
            ++sentenceCount;
        }
        if (!sentence.empty() && sentenceCount < MAX_SENTENCES)
        {
            sentences[index] = sentence;
            ++index;
            sentence.clear();
            ++sentenceCount;
        }
    }

    for (int i = index - 1; i >= 0; --i)
    {
        outputFile << sentences[i] << '\n';
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
