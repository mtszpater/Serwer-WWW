#include "utils.h"

string extractPath(string header) {
    char *header2 = &header[0u];
    string path = "";
    for (int i = 4; header2[i] != ' '; ++i) {
        path += header2[i];
    }

    return path;
}

bool isForbiddenPath(string path) {
    return path.find("..") != std::string::npos;
}

string readFileFromPath(string path) {
    std::ifstream ifs(path, std::ifstream::binary);

    char c = ifs.get();
    string res = "";
    while (ifs.good()) {
        res += c;
        c = ifs.get();
    }
    ifs.close();

    return res;
}
