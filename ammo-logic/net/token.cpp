#include "token.hpp"

#include <fstream>

std::string Token::token;

void Token::LoadFromFile(const char* file)
{
    std::ifstream stream(file);

    std::getline(stream, token);
}
