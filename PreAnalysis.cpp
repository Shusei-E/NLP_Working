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

vector<string> split( string s, string c ){
  vector<string> ret;
  for( int i=0, n; i <= s.length(); i=n+1 ){
	n = s.find_first_of( c, i );
	if( n == string::npos ) n = s.length();
	string tmp = s.substr( i, n-i );
	ret.push_back(tmp);
  }
  return ret;
}



#include "MakeFileList.cpp"
#include "ExtractUseData.cpp"


int main() {
	const char* path = "/home/3928941380/Downloads/TV/NHK_toAnalyze/";
		/* 「const char *」というデータ型は、書き換えできない(読み取り専用の)文字列に対して */

	/* ファイルリストの作成 */
	Temp_Path temp_path;
	int found_file_num=0;
	temp_path = getFileList(path, &found_file_num);
	FILE_LIST *File_List = new FILE_LIST[found_file_num]; // Files to Use http://goo.gl/n1tTj4FILENUM_MAX
	int put_file_num = 0;  
	filteredFileList(temp_path, &found_file_num, File_List, &put_file_num); // read specific source of file

	/* 使用データの抽出 */
	extractData(path, &put_file_num, File_List);	

	return 0;
}
