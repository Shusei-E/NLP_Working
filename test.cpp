#include <iostream>
#include <mecab.h>

int main(int argc, char **argv) {

    char input[1024] = "１時間と1分昼寝すること";

    MeCab::Tagger *tagger = MeCab::createTagger("");
    const MeCab::Node* node = tagger->parseToNode(input);

    for (; node; node = node->next) {
        std::cout << "==========" << std::endl;
        std::cout << "id        : " << node->id        << std::endl;
        std::cout << "surface   : " << node->surface   << std::endl;
        std::cout << "feature   : " << node->feature   << std::endl;
        std::cout << "length    : " << node->length    << std::endl;
        std::cout << "rlength   : " << node->rlength   << std::endl;
        std::cout << "rcAttr    : " << node->rcAttr    << std::endl;
        std::cout << "lcAttr    : " << node->lcAttr    << std::endl;
        std::cout << "posid     : " << node->posid     << std::endl;
        std::cout << "char_type : " << (int)node->char_type << std::endl;
        std::cout << "stat      : " << (int)node->stat      << std::endl;
        std::cout << "isbest    : " << (int)node->isbest    << std::endl;
        std::cout << "alpha     : " << node->alpha     << std::endl;
        std::cout << "beta      : " << node->beta      << std::endl;
        std::cout << "prob      : " << node->prob      << std::endl;
        std::cout << "wcost     : " << node->wcost     << std::endl;
        std::cout << "cost      : " << node->cost      << std::endl;
    }

    delete tagger;
}
