//construct the output string on passing the input string in Melay Machine

#include <cmath>
#include <exception>
#include <fstream>	
#include <iostream>	
#include <sstream>	
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

class Element{
protected:
	char* row;
	char* output;
	std::string column;
public:
	Element();
	Element(char _row, char _output, std::string _column);
	
	void setRow(char _row);
	void setOutput(char _output);
	void setColumn(std::string _column);

	char getRow() const;
	char getOutput() const;
	std::string getColumn() const;

	~Element();
};

class Row {
protected:
	char* rowId;
	std::vector<Element *> elements;
public:
	Row();
	Row(char _rowId);

	void setRowId(char _rowId);

	unsigned getSize() const;
	char getRowId() const;

	Element* operator[](unsigned idx);
	
	~Row();
};	

class Mealy {
private:
	std::vector<Row *> rows;
	char output;
	char prevState;
public:
	Mealy();
	Mealy(std::string filename);

	void execute(std::string inFilename, std::string outFilename);

	~Mealy();
};

Element::Element() {
	row = nullptr;
	output = nullptr;
	column = "";
}
	
Element::Element(char _row, char _output, string _column) {
	row = new char;
	*row = _row;
	output = new char;
	*output = _output;
	column = _column;
}

void Element::setRow(char _row) {
	if ('A' <= _row && _row <= 'Z' || _row == '-') {
		row = new char;
		*row = _row;
	}
}

void Element::setOutput(char _output) {
	output = new char;
	*output = _output;
}

void Element::setColumn(string _column) {
	column = _column;
}

char Element::getRow() const { 
	return *row;
}
	
char Element::getOutput() const { 
	return *output;
}

string Element::getColumn() const {
	return column;
}
	
Element::~Element() {
	delete row;
	delete output;
}	

Row::Row() {
	rowId = nullptr;
}

Row::Row(char _rowId) {
	rowId = new char;
	*rowId = _rowId; 
}

void Row::setRowId(char _rowId) {
	rowId = new char;
	*rowId = _rowId;
}

char Row::getRowId() const { 
	return *rowId;
}

unsigned Row::getSize() const { 
	return elements.size();
}


Element* Row::operator[](unsigned idx) {
	if (idx >= elements.size()) {
		for (unsigned i = elements.size(); i <= idx; i++) {
			elements.push_back(new Element());
		}
	}
	return elements[idx];
}

Row::~Row() {
	elements.erase(elements.begin(), elements.end());
}

Mealy::Mealy() {
	rows = vector<Row*>();
	output = '2';
	prevState = 'A';
}

Mealy::Mealy(string filename) {
	output = '2';
	prevState = 'A';
	
	string temp;
	
	ifstream startFile;
	startFile.open(filename);

	unsigned numOfCols = 0;
	while (startFile.peek() != '\n' && startFile >> temp)
		numOfCols++;

	startFile.seekg(0, startFile.beg);

	char currentChar;
	startFile.get(currentChar);
	
	
	rows.push_back(new Row(currentChar));
	Row* currentRow = rows[rows.size() - 1];

	startFile.get(currentChar);
	
	string binaryNum;

	while (currentChar != '\n') {
		startFile.get(currentChar);

		if (currentChar == '0' || currentChar == '1') {
			binaryNum += currentChar;
			if (startFile.peek() != '\t' && startFile.peek() != '\n' && startFile.peek() != ' ') {
				while (pow(2, static_cast<int>(binaryNum.size())) != numOfCols - 1) {
					startFile.get(currentChar);
					
					binaryNum += currentChar;
				}
			}
		}
		
		startFile.get(currentChar);
		if (currentChar == '\t' || currentChar == '\n' || currentChar == ' ') {
			(*currentRow)[(currentRow->getSize())]->setColumn(binaryNum);
			binaryNum.clear();
		}
		
	}

	startFile.get(currentChar);

	rows.push_back(new Row(currentChar));
	currentRow = rows[rows.size() - 1];

	while (!startFile.eof()) {
		startFile.get(currentChar);
		
		if ('A' <= currentChar && currentChar <= 'Z') {
			char tmp;
			tmp = currentChar;
			startFile.get(currentChar);
			startFile.get(currentChar);
			(*currentRow)[(currentRow->getSize())]->setRow(tmp);
			(*currentRow)[(currentRow->getSize()) - 1]->setOutput(currentChar);
		}
		else if ('-' == currentChar && !startFile.eof()) {
			char tmp;
			tmp = currentChar;
			(*currentRow)[(currentRow->getSize())]->setRow(tmp);
			(*currentRow)[(currentRow->getSize()) - 1]->setOutput(currentChar);
		}
		else if (currentChar == '\n') {
			startFile.get(currentChar);
			if ('A' <= currentChar && currentChar <= 'Z') {
				rows.push_back(new Row(currentChar));
				currentRow = rows[rows.size() - 1];
			}
			
			
		}
		
	}

	for (unsigned i = 1; i < rows.size(); i++) {
		
		for (unsigned j = 0; j < (*rows[i]).getSize(); j++) {
			(*rows[i])[j]->setColumn((*rows[0])[j]->getColumn());
		}
	}

	startFile.close();
}

void Mealy::execute(string inFilename, string outFilename) {
	string temp;

	ifstream inputFile;
	inputFile.open(inFilename);
	
	ofstream outputFile;
	outputFile.open(outFilename);
	
	inputFile.seekg(0, inputFile.end);
	int size = inputFile.tellg();
	inputFile.clear();
	inputFile.seekg(0, inputFile.beg);

	outputFile << "Solution: " << endl;
	cout << "Solution: " << endl;

	char currentInput;
	string binaryNum;
	bool success = false;

	while (!inputFile.eof()) {
		inputFile.get(currentInput);

		if (currentInput == '0' || currentInput == '1') {
			binaryNum += currentInput;
		}

		if (currentInput != '0' && currentInput != '1' && currentInput != '\t' && currentInput != '\n' && currentInput != ' ') {
			outputFile << "Incorrect character in " << inFilename << " it should only contain 0s and 1s";
			
		}

		if (currentInput == ' ' || currentInput == '\t' || currentInput == '\n' || size == static_cast<int>(inputFile.tellg())) {

			if (prevState == '-') {
				outputFile << "The previous state was neutral, we can't go anywhere!";
				
			}

			for (unsigned i = 1; i < rows.size(); i++) {
				if (rows[i]->getRowId() == prevState) {
					for (unsigned j = 0; j < (*rows[i]).getSize(); j++) {
						if (binaryNum == (*rows[i])[j]->getColumn()) {
							prevState = (*rows[i])[j]->getRow();
							output = (*rows[i])[j]->getOutput();
							cout << binaryNum << " ";
							outputFile << binaryNum << " ";
							j = (*rows[i]).getSize();
							success = true;
						}
					}
					i = rows.size();
				}
			}
	
			if (!success) {
				outputFile << "Incorrect input in " << inFilename << " it contains inputs that aren't in the header of the state table";
				
			}
			binaryNum.clear();
		}

		if (currentInput == '\n') {
			
			outputFile << right << setw(10) << prevState << "/" << output << endl;
			cout << right << setw(10) << prevState << "/" << output << endl;
		}
	}

	outputFile << right << setw(10) << prevState << "/" << output << " ";
	cout << right << setw(10) << prevState << "/" << output << " ";

	outputFile.close();
	inputFile.close();
}

Mealy::~Mealy() {
	rows.erase(rows.begin(), rows.end());
}

int main(void) {
	string startFilename;
	string inputFilename;
	string outputFilename;

	cout << "Please provide the name of the file where you would like to read the state table from (without extension): "; //inp
	getline(cin, startFilename);
	cout << "Please provide the name of the file where you would like to read the inputs from (without extension): "; //inp1
	getline(cin, inputFilename);
	cout << "Please provide the name of the file where you would like to write the solution to (without extension): "; //out
	getline(cin, outputFilename);

	try {
		Mealy system(startFilename + ".txt");
		system.execute(inputFilename + ".txt", outputFilename + ".txt");
	}
	catch (const exception& msg) {
		cout << msg.what() << endl;
	}

	return 0;
}
