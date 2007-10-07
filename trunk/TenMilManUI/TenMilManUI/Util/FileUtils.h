#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

#define PATH_SEPERATOR "/"

using std::string;
using std::vector;

class FileUtils {
public:	
	static int getDirFiles (const string &dir, vector<string> &files){
	    DIR *dp;
	    struct dirent *dirp;
	    
	    if((dp  = opendir(dir.c_str())) == NULL) {
	        return 1;
	    }
	    
	    while ((dirp = readdir(dp)) != NULL) {
	        files.push_back(string(dirp->d_name));
	    }
	    closedir(dp);
	    return 0;
	}
	
private:
	FileUtils();
	virtual ~FileUtils();
};

#endif /*FILEUTILS_H_*/
