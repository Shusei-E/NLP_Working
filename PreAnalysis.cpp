#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <dirent.h>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <regex> // regular expressions
#include <mecab.h>
#include <fstream>
#include <string>

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
	int put_file_num = 0;  
	filteredFileList(temp_path, &found_file_num, File_List, &put_file_num); // read specific source of file

	string path_str = path;
	string file_name;
	string full_path;
	for(int file_num=0; file_num<put_file_num; ++file_num){ // analyze for each file
			/* Prepare Full Path */
			file_name = File_List[file_num].filepath;
			full_path = path + file_name;
			cout << full_path << endl;

			/* Read File */
			ifstream ifs(full_path);
   		string str;
   		if (ifs.fail())
   		{
   		    std::cerr << "Reading file failed" << std::endl;
   		    return -1;
   		}
   		while (getline(ifs, str))
   		{
   		    std::cout << "[" << str << "]" << std::endl;
   		}
	}
  

	return 0;
}
