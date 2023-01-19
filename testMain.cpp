#include <fstream>
#include <iostream>
#include "outils.hh"

using std::cout, std::endl;

int main()
{
	vector<TrueFalse*> TFTable;
	loadTFQ(TFTable);

	for(auto i = TFTable.begin(); i < TFTable.end(); i++)
	{
		cout << (*i)->get_text() << endl;
		cout << (*i)->get_text() << endl;
		cout << (*i)->get_text() << endl;
	}
	return EXIT_SUCCESS;
}