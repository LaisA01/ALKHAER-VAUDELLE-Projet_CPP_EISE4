#include <fstream>
#include <iostream>

using std::cout, std::cin, std::ifstream, std::endl;

//Load all the TFQ. Return 0 if something wrong happened, else 1.
int loadTFQ()
{
	ifstream file("listQTF.txt");
	if (!file) 
	{
		cout << "Error : Can't open listTFQ file" << endl;
		return 0;
	}


}
