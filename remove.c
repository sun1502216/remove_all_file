#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>


/*
 * 函数功能：删除任意文件，包括非空文件夹和空文件夹
 * 函数参数：参数1：删除文件路径
 * 返回值：删除失败返回0，删除普通文件成功返回1，删除文件夹成功返回2
 *
 * 时间：2019年9月18日
 */
int Remove(const char* path)
{
	struct stat st;

	if(!stat(path, &st))
	{
		if(S_ISDIR(st.st_mode))
		{
			//文件夹
			DIR* dirp = opendir(path);
			struct dirent* dir = NULL;
			char d[256];

			getcwd(d, sizeof(d));
			chdir(path);
			while(dir = readdir(dirp))
			{
				if(strcmp(dir->d_name, ".") && strcmp(dir->d_name, ".."))
						Remove(dir->d_name);
			}
			chdir(d);
			if(!rmdir(path)) return 2;
		}
		else
		{
			//普通文件
			if(!unlink(path)) return 1;
		}
	}
	return 0;
}
