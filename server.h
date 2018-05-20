#ifndef SERWER_WWWW_SERVER_H
#define SERWER_WWWW_SERVER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include "responseBuilder.h"
#include "utils.h"
#include "sockwrap.h"

bool isGetMethod(string header);
int main(int argc, char *argv[]);


#endif //SERWER_WWWW_SERVER_H
