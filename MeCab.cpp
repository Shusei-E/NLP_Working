// Reference: http://d.hatena.ne.jp/syou6162/20090410/1239289505
#include <mecab.h>
#include <map>
#include <regex>

typedef map<string, int>::const_iterator map_freq_it; //下のみたいに毎回型を書いているのが面倒なときは、typedefで名前をつける
typedef std::vector<map_freq_it>::const_iterator vec_stu_citer_t;

// Defined in another place
//vector<string> split( string s, string c ){
//  vector<string> ret;
//  for( int i=0, n; i <= s.length(); i=n+1 ){
//	n = s.find_first_of( c, i );
//	if( n == string::npos ) n = s.length();
//	string tmp = s.substr( i, n-i );
//	ret.push_back(tmp);
//  }
//  return ret;
//}

bool compare( const map_freq_it& a, const map_freq_it& b ){ // ファンクタ
  return ( a->second > b->second );
}

void DoMeCab(DATA_USE *Data, int used_row_num, string path, string file_name){

	map<string, int> freq; // store_frequency
	map<string, int>::iterator find_it;
	map<string, int>::iterator output_it;
	
	file_name.erase(file_name.end()-9, file_name.end());
	string save_path = path + file_name + "Freq.txt";
	cout << "Save as: " << save_path << endl;	


  cout << "The number of rows used: " << used_row_num << endl;

	MeCab::Tagger *tagger = MeCab::createTagger("");
	for(int row_num=0; row_num< used_row_num; ++row_num){

    
    const MeCab::Node* node = tagger->parseToNode(Data[row_num].Text.c_str());


    for (; node; node = node->next) {

			vector<string> resvec = split( node->feature, "," );

			if(resvec[0]=="名詞" && resvec[6]!="*" ){

				/* When it is a noun */
				string noun = resvec[6];
				find_it = freq.find(noun);
				if(resvec[1]=="数"|resvec[1]=="非自立") continue;

				if (find_it != freq.end()){
					find_it->second += 1;
				}else{
					freq.insert(pair<string, int>(noun, 1));
				}

			}//close if for finding re_feature
				

   	}//close for node

	}//close for Data analyzing (analyze all rows)

		/* Make an output */
		vector<map_freq_it> sorted;
 		for(map_freq_it mfi = freq.begin(); mfi != freq.end(); ++mfi)
			sorted.push_back(mfi);

		sort(sorted.begin(), sorted.end(), compare);

		int output_number = 0;
		std::ofstream ofs(save_path, std::ios::out | std::ios::app );
 	 	for(vec_stu_citer_t output_it = sorted.begin(); output_it != sorted.end(); ++output_it){
			ofs << (*output_it)->first << "," <<  (*output_it)->second << endl;
 	 		
			//cout << (*output_it)->first << ",";
  		//cout << (*output_it)->second <<endl;
  	  
			if(output_number > 20) break;
			++output_number;
 		}

		delete tagger;
}//close function
