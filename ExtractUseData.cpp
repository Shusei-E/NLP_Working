typedef struct{
	string Datetime; //col 0
	string Time; //col 1
	string Text; //col 2
	string Description; //col 3
	string Genre; //col 4
	string ProgramTitle; //col 5
	string Station; //col 6
	string Subgenre; //col 7
	string Version; //col 8
} DATA_USE;

#include "MeCab.cpp"

void extractData(string path, int *put_file_num, FILE_LIST *File_List){

	// regex program_match("(.*)(ニュース)(.*)"); //Keyword for Program Title --> SLOW
	string keyword ("ニュース");

	DATA_USE *Data_temp = new DATA_USE[1];
	string file_name;
	string full_path;

	for(int file_num=0; file_num< *put_file_num; ++file_num){ // analyze for each file
			/* Prepare Full Path */
			file_name = File_List[file_num].filepath;
			full_path = path + file_name;
			cout << "Reading: " << full_path << endl;

			/* Count Line Number */
			ifstream countfile(full_path);
			string line;
			int total_line_num = -1; // the first row is header
			while (std::getline(countfile, line)) ++total_line_num;
			cout << "Total Line: " << total_line_num << endl;

			/* Read File */
			DATA_USE *Data = new DATA_USE[total_line_num];
		
			int used_row_num=0;

			ifstream ifs(full_path);
			string str, temp;
   		if (ifs.fail())
   		{
   		    std::cerr << "Reading file failed" << std::endl;
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
						std::size_t found = temp.find(keyword);
						if (found!=std::string::npos) flag=1; /* Select Program!!! */
					}//close if

					++col_index;
				}//close while

				/* After reading each line */
				if(flag==1){ // program_title matches with the pattern
						Data[used_row_num].Datetime = Data_temp[0].Datetime;
						Data[used_row_num].Time = Data_temp[0].Time;
						Data[used_row_num].Text = Data_temp[0].Text;
						Data[used_row_num].Description = Data_temp[0].Description;
						Data[used_row_num].ProgramTitle = Data_temp[0].ProgramTitle;
						Data[used_row_num].Station = Data_temp[0].Station;
						Data[used_row_num].Subgenre = Data_temp[0].Subgenre;
						Data[used_row_num].Version = Data_temp[0].Version;
						flag = 0; ++used_row_num;
				}

				++row_index;
			}//close while (read all rows in the data)


			DoMeCab(Data, used_row_num, path, file_name);


	}//close for reading each file


}//end function
