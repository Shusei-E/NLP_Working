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

#include "MakeFileList.cpp"

typedef struct{
	string Datetime; //row 0
	string Time; //row 1
	string Text; //row 2
	string Description; //row 3
	string Genre; //row 4
	string ProgramTitle; //row 5
	string Station; //row 6
	string Subgenre; //row 7
	string Version; //row 8
}DATA_USE;

int main() {
	//const char* path = "/home/3928941380/Downloads/TV/"; 
		/* 「const char *」というデータ型は、書き換えできない(読み取り専用の)文字列に対して使います */

	/* ファイルリストの作成 */
	Temp_Path temp_path;
	int found_file_num=0;
	temp_path = getFileList(path, &found_file_num);
	FILE_LIST *File_List = new FILE_LIST[found_file_num]; // http://goo.gl/n1tTj4FILENUM_MAX
	int put_file_num = 0;  
	filteredFileList(temp_path, &found_file_num, File_List, &put_file_num); // read specific source of file

	/* 使用データの抽出 */
	string path_str = path;
	string file_name;
	string full_path;
	regex program_match("(.*)(短歌)(.*)"); //Program Title to look for
	DATA_USE *Data_temp = new DATA_USE[1];

	for(int file_num=0; file_num<put_file_num; ++file_num){ // analyze for each file
			/* Prepare Full Path */
			file_name = File_List[file_num].filepath;
			full_path = path + file_name;
			cout << full_path << endl;

			/* Count Line Number */
			ifstream countfile(full_path);
			string line;
			int total_line_num = -1; // the first row is header
			while (std::getline(countfile, line)) ++total_line_num;
			cout << total_line_num << endl;

			/* Read File */
			DATA_USE *Data = new DATA_USE[total_line_num];

			ifstream ifs(full_path);
			string str, temp;
   		if (ifs.fail())
   		{
   		    std::cerr << "Reading file failed" << std::endl;
   		    return -1;
   		}

			int col_index = 0;
			int row_index = 0;
   		while (getline(ifs, str)){ // read file line by line
				istringstream stream(str);

				col_index = 0; //reset col index each time you read line
				int flag = 0;
				while(getline(stream,temp,'\t')){ // analyze each line

				switch(col_index){
						case 0: Data_temp[0].Datetime = temp;
						case 1: Data_temp[0].Time = temp;
						case 2: Data_temp[0].Text = temp;
						case 3: Data_temp[0].Description = temp;
						case 4: Data_temp[0].Genre = temp;
						case 5: Data_temp[0].ProgramTitle = temp;
						case 6: Data_temp[0].Station = temp;
						case 7: Data_temp[0].Subgenre = temp;
						case 8: Data_temp[0].Version = temp;
					}

					if(col_index==5 & row_index!=0){
						if(regex_match(temp, program_match)) flag=1;
					}//close if

					++col_index;
				}//close while

				/* After reading each line */
				if(flag==1){ // program_title matches with the pattern
						cout<< Data_temp[0].Subgenre << endl;
						flag = 0;
				}

				++row_index;
   		}//close while

			
	}//close for reading each file
  
	/*
	http://www.c-lang.net/general43/index.htmlの方法に従って、まずはファイルの長さにあった構造体を作り、正規表現で該当するプログラム名のものだけをその構造体に入れて、最後にサイズを調整するようにする。
	*/

	return 0;
}
