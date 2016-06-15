#include <mecab.h>

void DoMeCab(DATA_USE *Data, int used_num){

	regex re_feature("(名詞)(.*)");
	regex re_skip1("(名詞),(.*),(.*),(.*),(.*),(.*),\\*");


	for(int file_num=0; file_num< 2; ++file_num){
    MeCab::Tagger *tagger = MeCab::createTagger("");
    const MeCab::Node* node = tagger->parseToNode(Data[file_num].Text.c_str());


    for (; node; node = node->next) {
			if(regex_match(node->feature, re_feature) & !regex_match(node->feature, re_skip1)){
				std::cout << "feature   : " << node->feature   << std::endl;
			}
				

   }//close for

    delete tagger;
	
	}

}//close function
