#ifndef SERWER_WWWW_UTILS_H
#define SERWER_WWWW_UTILS_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <streambuf>
using namespace std;

string extractPath(string header);
bool isForbiddenPath(string path);
string readFileFromPath(string path);

#endif
