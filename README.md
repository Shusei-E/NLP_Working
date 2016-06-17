# Working_Code
Codes I'm working on

## Future Consideration
* `regex_search` is slow
	* `regex_match` is even faster
	* But the fastest one is splitting in to a vector, which is used in `MeCab.cpp`.
	* For simple use, `std::string::find` is enough.
* Visualizing the results
	* ~~Count data --> pandas --> line graph for top words?~~ Done in `MeCab.cpp`
