// string::find
#include <iostream>       // std::cout
#include <string>         // std::string

int main ()
{
  std::string str ("長いタイトルの中に、ニュースが入っているとします");
  std::string str2 ("ニュース");

  // different member versions of find in the same order as above:
  std::size_t found = str.find(str2);
  if (found!=std::string::npos)
    std::cout << "first 'needle' found at: " << found << '\n';

  //found=str.find("needles are small",found+1,6);
  //if (found!=std::string::npos)
  //  std::cout << "second 'needle' found at: " << found << '\n';

  //found=str.find("haystack");
  //if (found!=std::string::npos)
  //  std::cout << "'haystack' also found at: " << found << '\n';

  //found=str.find('.');
  //if (found!=std::string::npos)
  //  std::cout << "Period found at: " << found << '\n';

  //// let's replace the first needle:
  //str.replace(str.find(str2),str2.length(),"preposition");
  //std::cout << str << '\n';

  return 0;
}
