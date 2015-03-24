#ifndef MISC_FUNCTIONS__H
#define MISC_FUNCTIONS__H
#include <string>

using namespace std;

int32_t strtoint32(const string& str);
int64_t strtoint64(const string& str);
string inttostr(int i);
string hex_decode(const string &in);
string bintohex(const string &in);

#endif
