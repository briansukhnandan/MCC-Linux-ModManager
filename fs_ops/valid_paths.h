#include <stdio.h>

/* 
 *
 * Checks if given file path exists by checking the status of fopen().
 * If we successfully open/close the file, then the file exists, else return false.
 *
 */
bool FileExists(const std::string& s) {
    if (FILE *file = fopen(s.c_str(), "r")) {
        fclose(file);
        return true;
    }
    
    return false;
}

/* 
 *
 * Check if the specified string path exists by using stat syscall.
 *
 */
bool PathExists(const std::string &path) {
    struct stat buffer;
    return (stat (path.c_str(), &buffer) == 0);    
}