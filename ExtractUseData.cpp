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
} DATA_USE;


void extractData(string path, int *put_file_num, FILE_LIST *File_List, DATA_FULL *Data_Use_Full){

	regex program_match("(.*)(短歌)(.*)"); //Program Title to look for
	DATA_USE *Data_temp = new DATA_USE[1];
	string file_name;
	string full_path;

	for(int file_num=0; file_num< *put_file_num; ++file_num){ // analyze for each file
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
		
			int used_num=0;

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
						if(regex_match(temp, program_match)) flag=1;
						Data_Use_Full[file_num].use_line_index.push_back(row_index);
					}//close if

					++col_index;
				}//close while

				/* After reading each line */
				if(flag==1){ // program_title matches with the pattern
						Data[used_num].Datetime = Data_temp[0].Datetime;
						Data[used_num].Time = Data_temp[0].Time;
						Data[used_num].Text = Data_temp[0].Text;
						Data[used_num].Description = Data_temp[0].Description;
						Data[used_num].ProgramTitle = Data_temp[0].ProgramTitle;
						Data[used_num].Station = Data_temp[0].Station;
						Data[used_num].Subgenre = Data_temp[0].Subgenre;
						Data[used_num].Version = Data_temp[0].Version;
						flag = 0; ++used_num;
				}

				++row_index;
			}//close while (read all rows in the data)


	}//close for reading each file

		//return Data;

}//end function