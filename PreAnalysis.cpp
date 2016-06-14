#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <dirent.h>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <regex> // regular expressions

using namespace std;

#include "MakeFileList.cpp"

int main() {
	const char* path = "/home/3928941380/Downloads/TV/"; 
		/* 「const char *」というデータ型は、書き換えできない(読み取り専用の)文字列に対して使います */

	/* ファイルリストの作成 */
	Temp_Path temp_path;
	int found_file_num=0;
	temp_path = getFileList(path, &found_file_num);
	FILE_LIST *File_List = new FILE_LIST[found_file_num]; // http://goo.gl/n1tTj4FILENUM_MAX
	filteredFileList(temp_path, &found_file_num, File_List);

  
	return 0;
}
