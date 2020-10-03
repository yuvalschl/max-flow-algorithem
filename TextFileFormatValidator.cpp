#include "TextFileFormatValidator.h"

bool TextFileFormatValidator::IsDigit(char Ch)
{
    return ((Ch >= '0' && Ch <= '9'));
}

bool TextFileFormatValidator::ValidateEdgeFormat(string edgeString)
{
    bool isCurrentCharDigit = IsDigit(edgeString[0]);
    int lengthOfString = edgeString.length(), counter = 0;

    for (int i = 1; i <= lengthOfString; i++)
    {
        if (isCurrentCharDigit == true && IsDigit(edgeString[i]) == false)
            counter++;
        isCurrentCharDigit = IsDigit(edgeString[i]);
    }
    
    return counter == 3;
}

void TextFileFormatValidator::ValidateFormat(const string textFileName)
{
    ifstream textFile;
    textFile.open(textFileName, ios::in);
    string numberOfVertexesStr, numberOfEgeds, vertexS, vertexT, currentEdge;
    int numberOfVertexes, numOfEdges, s, t;

    getline(textFile, numberOfVertexesStr);
    while (isEmptyString(numberOfVertexesStr))
    {
        getline(textFile, numberOfVertexesStr);
    }

    getline(textFile, numberOfEgeds);
    while (isEmptyString(numberOfEgeds))
    {
        getline(textFile, numberOfEgeds);
    }

    getline(textFile, vertexS);
    while (isEmptyString(vertexS))
    {
        getline(textFile, vertexS);
    }

    getline(textFile, vertexT);
    while (isEmptyString(vertexT))
    {
        getline(textFile, vertexT);
    }

    try
    {
        numberOfVertexes = stoi(numberOfVertexesStr);
        numOfEdges = stoi(numberOfEgeds);
        s = stoi(vertexS);
        t = stoi(vertexT);

        for (int i = 0; i < numOfEdges; i++)
        {
            
            getline(textFile, currentEdge);
            while (isEmptyString(currentEdge))
            {
                getline(textFile, currentEdge);
            }

            if (!ValidateEdgeFormat(currentEdge))
            {
                cout << "Invalid format" << endl;
                exit(1);
            }
        }
    }
    catch (...)
    {
        cout << "Invalid format" << endl;
        exit(1);
    }

    textFile.close();
}

bool TextFileFormatValidator::isEmptyString(const string str) {
    int i = 0;
    while (str[i] != '\0') {
        if (!isspace(str[i]))
            return false;
        i++;
    }
    return true;
}

