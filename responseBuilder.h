#ifndef SERWER_WWWW_RESPONSEBUILDER_H
#define SERWER_WWWW_RESPONSEBUILDER_H
#include <string>
using namespace std;

string const NOT_FOUND_MESSAGE = "Not found, sorry :(";
string const NOT_FOUND_STATUS = "404 Not Found";
string const FORBIDDEN_MESSAGE = "NOT FOR YOU; FORBIDDEN";
string const FORBIDDEN_STATUS = "403 Forbidden";
string const NOT_IMPLEMENTED_STATUS = "501 Not Implemented";
string const NOT_IMPLEMENTED_MESSAGE = "Not implemented, yet... :)";
string const OK_STATUS = "200 OK";
string const MOVED_PERMANENTLY_STATUS = "301 Moved Permanently";

string createContentType(string header);
string buildResponse(string status, string contentType, int contentLength, string data);
string buildForbiddenResponse();
string buildNotFoundResponse();
string buildNotImplementedResponse();
string buildSuccessResponse(string file, string header);
string buildMovedPermanentlyResponse(string file, string header);

#endif
