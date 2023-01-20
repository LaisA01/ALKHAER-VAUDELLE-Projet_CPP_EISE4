#include "outils.hh"

using std::cout, std::cin, std::ifstream, std::endl, std::string;
using std::vector;

//Load all the TFQ. Return 0 if something wrong happened, else 1.
int loadTFQ(vector<TrueFalse*> &TFTable)
{
	ifstream file("listQTF.txt");
	if (!file)
	{
		cout << "Error : Can't open listTFQ file" << endl;
		return 0;
	} 

	char sentence[256];
	int value;
	TrueFalse* pTFQuestion;
	while(file.getline(sentence, 256)) // Check if a question last and get it		
	{

		string question(sentence);
		file.getline(sentence, 256); // Get score
		string score(sentence); 	 // Used to cast from char to int, ugly I know
		file.getline(sentence, 256); // Get answer
		string answer(sentence);

		pTFQuestion = new TrueFalse(question, stoi(score), stoi(answer));
		TFTable.push_back(pTFQuestion);
	}

	return 1;
}

int loadMCQ(vector<MCQ*> & MCQTable)
{
	ifstream file("listMCQ.txt");
	if(!file)
	{
		cout << "Error :  Can't open listMCQ.txt" << endl;
		return 0;
	}

	char sentence[256];
	int value;
	MCQ* pMCQuestion;
	while(file.getline(sentence, 256))
	{

		string question(sentence);

		file.getline(sentence,256);
		string reponseA(sentence);
		file.getline(sentence,256);
		string reponseB(sentence);
		file.getline(sentence,256);
		string reponseC(sentence);
		file.getline(sentence,256);
		string reponseD(sentence);

		file.getline(sentence, 256);
		string score(sentence);
		file.getline(sentence, 256);
		string answer(sentence);

		pMCQuestion = new MCQ(question, stoi(score),
		 {reponseA, reponseB, reponseC, reponseD}, stoi(answer));
		MCQTable.push_back(pMCQuestion);
	}

	return 1;
}

template<T>
void randomize(vector<T> listQuestion)
{}
