#include <iostream>
#include <fstream>
#include<string>

int main()
{
    std::cout << "Hello World!\n";
    
    std::ifstream inputFile("games.csv");
    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << line << "\n";
    }

    inputFile.close();

    return 0;
}