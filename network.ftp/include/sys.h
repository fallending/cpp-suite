#ifndef H_SYS
#define H_SYS

#include <string>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <sys/types.h>
#include <sstream>
#include <errno.h>
#include <sys/stat.h>

using namespace std;

namespace sys
{
	inline bool isRegularFile(string path)
	{
		struct stat s;
		if (stat(path.c_str(), &s)!=0) return false;
		return (bool) (s.st_mode & S_IFREG);
	}

	inline string pwd()
	{
		char cwd[1024];
		errno = 0;
		getcwd(cwd, sizeof(cwd));
		if(errno)	return string(strerror(errno));
		return string(cwd);	
	}
	
	inline bool cd(string dir)
	{
		return chdir(dir.c_str()) != -1;
	}
	
	inline bool setRootDir(string dir)
	{
		errno = 0;
		chroot(dir.c_str());
		if(errno)	false;
		return true;
	}
	
	inline string ls(string arg)
	{
		string cmd = "ls";
		if(arg != "")	cmd += " " + arg;
		
		cmd += " 2>&1\n";
		
		errno = 0;
		
		FILE* file = popen(cmd.c_str(), "r");
		
		if(errno)	return string(strerror(errno)); 
		
		char buffer[1024];
		stringstream fileList;
		int n;
		while((n=fread(buffer, 1, 1024, file))>0)
		{
			for (int i=0; i<n; i++)
			{
				if (buffer[i]=='\n') fileList<<'\r';
				fileList<<buffer[i];
			}
		}
		pclose(file);
		
		return fileList.str();
	}
	
	inline string syst()
	{
		return string("UNIX");
	}
	
}

#endif


