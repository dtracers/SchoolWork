#ifndef UTILITY_H
#define UTILITY_H
#include<string>
#include<vector>

void stringtok(std::vector<std::string> &v, std::string const &in,
               const char * const delim,
               bool includeDelim);

#endif
