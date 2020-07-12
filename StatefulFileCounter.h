#pragma once

#include <string>
#include <fstream>

class StatefulFileCounter 
{
public:
	StatefulFileCounter(const std::string ksFileName, const unsigned int kuiCounter = 0);
	~StatefulFileCounter();
	//TODO: Overload ==

	unsigned int uiGetCount() {
		return readNumberFromFile();
	}
	// conversion to uint operator overload (returns uint to lhs on assignment)
	operator unsigned int() { return uiGetCount(); };

	//assignment operator overload(uint on rhs)
	StatefulFileCounter& operator=(const unsigned int& rhs);

	//-- postfix and prefix overload
	unsigned int operator-- (int);
	unsigned int operator-- ();

	//++ postfix and prefix overload
	unsigned int operator++ (int);
	unsigned int operator++ ();

	//copy constructor delete. making it explicit, as fstream already deletes it.
	StatefulFileCounter& operator=(const StatefulFileCounter&) = delete;
	
private:
	inline bool bFileExist(const std::string& filename);
	inline void writeNumberToFile(const unsigned int kuiCounter);
	unsigned int readNumberFromFile();
	inline void subtractByOne();
	inline void addByOne();

	std::fstream mfsFile;
};

