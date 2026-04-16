#ifndef _TOKEN_HPP
#define _TOKEN_HPP 1

#include <string>

#define TOKEN Token::token

struct Token
{
    static std::string token;
    static std::string account;

    static void LoadFromFile(const char* file);
};

#endif  // _TOKEN_HPP
