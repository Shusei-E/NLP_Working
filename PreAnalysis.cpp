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
#include <sstream>

using namespace std;

typedef struct{
	vector<int> use_line_index; // Keep row_index of files we are going to analyze
} DATA_FULL;

#include "MakeFileList.cpp"
#include "ExtractUseData.cpp"


int main() {
	const char* path = "";
		/* 「const char *」というデータ型は、書き換えできない(読み取り専用の)文字列に対して */

	/* ファイルリストの作成 */
	Temp_Path temp_path;
	int found_file_num=0;
	temp_path = getFileList(path, &found_file_num);
	FILE_LIST *File_List = new FILE_LIST[found_file_num]; // Files to Use http://goo.gl/n1tTj4FILENUM_MAX
	int put_file_num = 0;  
	filteredFileList(temp_path, &found_file_num, File_List, &put_file_num); // read specific source of file

	/* 使用データの抽出 */
	DATA_FULL *Data_Use_Full = new DATA_FULL[put_file_num];
	extractData(path, &put_file_num, File_List, Data_Use_Full);	
  cout << Data_Use_Full[0].use_line_index[2] << endl; 

	return 0;
}
