#include "responseBuilder.h"

string createContentType(string header) {
    if (header.find(".html") != std::string::npos) {
        return "text/html";
    }

    if (header.find(".txt") != std::string::npos) {
        return "text/plain";
    }

    if (header.find(".png") != std::string::npos) {
        return "image/png";
    }

    if (header.find(".jpg") != std::string::npos) {
        return "image/jpg";
    }

    if (header.find(".jpeg") != std::string::npos) {
        return "image/jpeg";
    }

    if (header.find(".css") != std::string::npos) {
        return "application/x-pointplus";
    }

    if (header.find(".pdf") != std::string::npos) {
        return "application/pdf";
    }

    return "application/octet-stream";
}

string buildResponse(string status, string contentType, int contentLength, string data) {
    return "HTTP/1.1 " + status + " \r\n Content-Type: " + contentType + " \r\n Content-Length: " +
           to_string(contentLength) +
           " \r\n\r\n " + data;
}

string buildForbiddenResponse() {
    return buildResponse(FORBIDDEN_STATUS, "text/plain", FORBIDDEN_MESSAGE.length(), FORBIDDEN_MESSAGE);
}

string buildNotFoundResponse() {
    return buildResponse(NOT_FOUND_STATUS, "text/plain", NOT_FOUND_MESSAGE.length(), NOT_FOUND_MESSAGE);
}

string buildNotImplementedResponse() {
    return buildResponse(NOT_IMPLEMENTED_STATUS, "text/plain", NOT_IMPLEMENTED_MESSAGE.length(),
                         NOT_IMPLEMENTED_MESSAGE);
}

string buildSuccessResponse(string file, string header) {
    return buildResponse(OK_STATUS, createContentType(header), file.length(), file);
}
string buildMovedPermanentlyResponse(string file, string header){
    return buildResponse(MOVED_PERMANENTLY_STATUS, createContentType(header), file.length(), file);
}