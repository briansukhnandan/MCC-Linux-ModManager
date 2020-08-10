#include <stdio.h>

bool FileExists(const std::string& s) {

    if (FILE *file = fopen(s.c_str(), "r")) {
        fclose(file);
        return true;
    }
    
    else {
        return false;
    }

}


bool PathExists(const std::string &s) {

    struct stat buffer;
    return (stat (s.c_str(), &buffer) == 0);
    
}