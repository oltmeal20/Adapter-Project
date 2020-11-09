#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class FileReader {
public:
	virtual void read(string file_type, string file_name) = 0;
	virtual ~FileReader() {}
};

class AdvancedFileReader {
public:
	AdvancedFileReader() {}
	virtual void readTXT(string file_name) = 0;
	virtual void readDAT(string file_name) = 0;

	virtual ~AdvancedFileReader() {}
};

class TXTReader : public AdvancedFileReader {
public:
	void readTXT(string file_name) {
		ifstream example_file;
		example_file.open(file_name);
		cout << "\nReading .txt File " << file_name << ":\n";
		if (example_file.is_open()) {
			string line;
			while (getline(example_file, line)) {
				cout << line << '\n';
			}
			example_file.close();
		}
		else {
			cerr << "Unable to open INPUT file";
		}
	}

	void readDAT(string file_name) {
		// must implement because pure virtual base class
		// should never be called
	}

	~TXTReader() {}
};

class DATReader : public AdvancedFileReader {
public:
	void readDAT(string file_name) {
		ifstream example_file;
		example_file.open(file_name);
		cout << "\nReading .dat File " << file_name << ":\n";
		if (example_file.is_open()) {
			string line;
			while (getline(example_file, line)) {
				cout << line << '\n';
			}
			example_file.close();
		}
		else {
			cerr << "Unable to open INPUT file\n";
		}
	}

	void readTXT(string file_name) {
		// must implement because pure virtual base class
		// should never be called
	}

	~DATReader() {}
};

class FileAdapter : public FileReader {
	AdvancedFileReader* advancedFileReader;

public:
	FileAdapter(string file_type) {
		if (file_type.compare("txt") == 0) {
			advancedFileReader = new TXTReader;
		}
		else if (file_type.compare("dat") == 0) {
			advancedFileReader = new DATReader;
		}
	}

	void read(string file_type, string file_name) {
		if (file_type.compare("txt") == 0) {
			advancedFileReader->readTXT(file_name);
		}
		else if (file_type.compare("dat") == 0) {
			advancedFileReader->readDAT(file_name);
		}
	}

	~FileAdapter() {
		delete advancedFileReader;
	}
};

class TextReader : public FileReader {
	FileAdapter* fileAdapter;

public:
	void read(string file_type, string file_name) {
		if (file_type.compare("txt") == 0 || file_type.compare("dat") == 0) {
			fileAdapter = new FileAdapter(file_type);
			fileAdapter->read(file_type, file_name);
			delete fileAdapter;
		}
		else {
			cout << "\nInvalid File. " << file_type;
			cout << " format not supported";
			cout << "\n";
		}
	}
};

int main() {
	TextReader textReader;

	//My added files
	srand(time(NULL));
	string example_text_file_one = "./record_one.txt";
	string example_text_file_two = "./record_two.doc";
	string example_text_file_three = "./record_three.dat";

	textReader.read("txt", example_text_file_one);
	textReader.read("dat", example_text_file_three);
	textReader.read("doc", example_text_file_two);
}