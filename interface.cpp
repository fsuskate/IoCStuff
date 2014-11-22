#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class IWriter
{
public:
	virtual void Write(string str) = 0;
};

class ConsoleWriter: public IWriter
{
public:
	ConsoleWriter() {}

	virtual void Write(string str)
	{
		cout << str << endl;
	}
};

class FileWriter: public IWriter
{	
public:
	FileWriter() {}

	virtual void Write(string str)
	{
		ofstream file;
		file.open ("output.txt");
		file << str << "\n";
		file.close();
	}
};

class ConsoleFileWriter: public IWriter
{
public:
	ConsoleFileWriter() {}

	virtual void Write(string str)
	{
		(new FileWriter())->Write(str);
		(new ConsoleWriter())->Write(str);
	}
};

class OutPutter
{
private:
	IWriter* _pWriter;

public:
	OutPutter(IWriter* pWriter)
	{
		_pWriter = pWriter;
	}

	void DoOutPut(string str)
	{
		_pWriter->Write(str);
	}
};

int main()
{
	OutPutter* pOutPutter = new OutPutter(new ConsoleWriter());
	pOutPutter->DoOutPut("Written to the console.");

	OutPutter* pOutPutter2 = new OutPutter(new FileWriter());
	pOutPutter2->DoOutPut("Written to a file.");

	OutPutter* pOutPutter3 = new OutPutter(new ConsoleFileWriter());
	pOutPutter3->DoOutPut("Written to a file and to the console.");	

	return 1;
}