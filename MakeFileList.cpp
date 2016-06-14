typedef struct{
	string filepath;
}FILE_LIST;

typedef std::vector<char*> Temp_Path;


bool has_suffix(const string& s, const string& suffix){ //Fileリストを取得するのに必要
    return (s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());    
}

vector<char*> getFileList(const char* path, int *found_file_num) {
	// Get File list: http://xr0038.hatenadiary.jp/entry/2015/02/26/154608sR
  
  DIR *dp;       // pointer to the directory
  dirent* entry; // readdir() で返されるエントリーポイント

  dp = opendir(path);
	Temp_Path temp_path;
  if (dp==NULL) exit(1);
  do {
    entry = readdir(dp);
    if (entry != NULL){
			if(has_suffix(entry->d_name, ".tsv"))
				temp_path.push_back(entry->d_name);
				++(*found_file_num);
		}
  } while (entry != NULL);
	

	return temp_path;
}

int filteredFileList(vector<char*> temp_path, int *found_file_num, FILE_LIST *File_List){
	if (0 < *found_file_num){
		Temp_Path::iterator iter;
		int put_file_num = 0;
		regex re("(.*)(CCText)(.*)"); // re  HERE, TYPE OF FILE USED IS DEFINED
		for (iter = temp_path.begin(); iter != temp_path.end(); ++iter) {
				if(regex_match(*iter, re)){	
      		  cout << *iter << endl; 
						File_List[put_file_num].filepath = *iter;
						++put_file_num;
				}
     }
	}

	return 0;
}

